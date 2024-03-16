
#include "CreateBackup.h"

#include <wx/stdpaths.h>
#include <wx/zipstrm.h>
#include <wx/stream.h>
#include <wx/wfstream.h>

#include <filesystem>
#include <regex>
#include <iostream>
#include <fstream>

namespace fs = std::filesystem;

ERROR_CODE createBackupFolderAndPopulate(std::filesystem::path user_library_path)
{
    wxPlatformInfo* platform_info = new wxPlatformInfo();
    
    std::string os_type = std::string(platform_info->GetOperatingSystemFamilyName());


    // username_path = username_path.substr(0, username_path.find("/"));

    // std::cout << username_path << std::endl;



    // Convert to paths
    fs::path backup_folder_location;
    fs::path user_keywords_path;
    fs::path library_config_path;

    std::cout << os_type << std::endl;

    if (os_type == "Macintosh")
    {
        std::string username_path = std::string(wxStandardPaths::Get().GetUserDataDir());
        username_path = username_path.substr(sizeof("/Users/") - 1, username_path.length());
        username_path = username_path.substr(0, username_path.find("/"));

        backup_folder_location = MACOS_TMP_FOLDER_PATH / BACKUP_FOLDER_CREATION_NAME;
        user_keywords_path = user_library_path / BASE_DEFAULT_RELATIVE_MACOS_ABLETON_USER_KEYWORDS_FILE_PATH;
        library_config_path = std::regex_replace(BASE_DEFAULT_MACOS_ABLETON_PREFERENCES_FOLDER.generic_string(), std::regex("%s"), username_path);

        std::cout << library_config_path << std::endl;
        // library_config_path = BASE_DEFAULT_MACOS_ABLETON_PREFERENCES_FOLDER.replace(BASE_DEFAULT_MACOS_ABLETON_PREFERENCES_FOLDER.find("%s"), 2, username_path);
        // library_config_path = BASE_DEFAULT_MACOS_ABLETON_PREFERENCES_FOLDER.replace(BASE_DEFAULT_MACOS_ABLETON_PREFERENCES_FOLDER.find("%s"), sizeof("%s") - 1, "Bob");

        return gatherTagFiles(user_library_path, backup_folder_location, user_keywords_path, library_config_path);
    }
    else if (os_type == "Windows")
    {

    }
    else
    {
        // Unsupported OS
        return UNSUPPORTED_OS_DETECTED;
    }

    return SUCCESS;
}

ERROR_CODE gatherTagFiles(std::filesystem::path user_library_path, std::filesystem::path backup_folder_path, std::filesystem::path user_keywords_file_path, std::filesystem::path library_config_file_path)
{
    // Check if the backup folder already exists
    // If it does, we might have crashed along the way
    // so we'll delete it so we have a fresh start
    if (fs::is_directory(backup_folder_path))
    {
        if (!fs::remove_all(backup_folder_path))
        {
            return ERROR_CODE::CANT_DELETE_BACKUP_FOLDER;
        }
    }

    // Try to create the backup folder
    if (!fs::create_directory(backup_folder_path))
    {
        return ERROR_CODE::CANT_CREATE_BACKUP_FOLDER;
    }

    // Try to Create Manifest File
    fs::path manifest_file_path = backup_folder_path / BACKUP_FOLDER_MANIFEST_FILE_NAME;
    std::ofstream manifest_file_stream(manifest_file_path);

    if (!manifest_file_stream)
    {
        return ERROR_CODE::CANT_CREATE_MANIFEST_FILE;
    }

    // Write the Manifest File Header
    manifest_file_stream << MANIFEST_FILE_HEADER << std::endl;

    // Next is to copy over the UserKeywords file
    // The strategy is to recreate the directory structure
    // in the backup folder and the copy over the files
    
    // We don't error out if we can't find the keywords file
    // since it is entirely possible the user tagged
    // their entire library with just the provided Ableton
    // Default Tags. That and if the user hasn't bothered
    // tagging their library, but they use collections
    if (fs::exists(user_library_path / user_keywords_file_path))
    {
        // Convert the full path to a relative path
        // by getting rid of the user_library_path
        std::string temp_string = user_keywords_file_path.string();
        temp_string = temp_string.substr(user_library_path.string().size() + 1, temp_string.length());
        fs::path relative_user_keywords_path(temp_string);

        std::cout << backup_folder_path / relative_user_keywords_path << std::endl;

        // Create the directory in the backup folder
        if (!fs::create_directories(backup_folder_path / relative_user_keywords_path.parent_path()))
        {
            return ERROR_CODE::CANT_CREATE_BACKUP_FOLDER_SUBFOLDER;
        }

        // Copy over the file
        if (!fs::copy_file(user_library_path / relative_user_keywords_path, backup_folder_path / relative_user_keywords_path))
        {
            return ERROR_CODE::CANT_COPY_OVER_FILE_FROM_USER_LIBRARY;
        }
    }

    // Look for all of the .xmp files in User Library
    // And copy them over to our backup folder.
    // We also recreate the directory structure so that
    // we remember where the files should go when restoring
    // from backup or if the user wants to manually add
    // files
    for (auto &p : fs::recursive_directory_iterator(user_library_path))
    {
        if (p.path().extension() == ABLETON_TAG_FILE_EXT)
        {
            std::cout << p.path().filename().string() << '\n';

            // We need to get the relative path of the file
            // so that we can reconstruct the directory structure
            // in the backup folder
            std::string temp_string = p.path();
            temp_string = temp_string.substr(user_library_path.string().size() + 1, temp_string.length());
            fs::path relative_file_path(temp_string);

            // Create the directory if we don't already have it in the backup folder
            if (!fs::is_directory(backup_folder_path / relative_file_path.parent_path()))
            {
                // Create the directory in the backup folder
                if (!fs::create_directories(backup_folder_path / relative_file_path.parent_path()))
                {
                    return ERROR_CODE::CANT_CREATE_BACKUP_FOLDER_SUBFOLDER;
                }
            }

            // Copy over the file
            if (!fs::copy_file(p.path(), backup_folder_path / relative_file_path))
            {
                return ERROR_CODE::CANT_COPY_OVER_FILE_FROM_USER_LIBRARY;
            }
        }
    }

    // Next is to copy over the Ableton LibraryConfig file
    // The strategy for this is to look for the latest
    // Ableton Version in Preferences and then grab the
    // Config file from there. We'll just copy the file
    // and worry about parsing it when we restore from
    // a backup
    uint8_t live_version = 0;
    uint8_t major_version = 0;
    uint8_t minor_version = 0;
    std::string name = "";
    for (auto &p : fs::directory_iterator(library_config_file_path))
    {
        if (p.is_directory())
        {
            std::string current_name = p.path().filename();

            // The begining of the directory should
            // start with "Live". If it doesn't then
            // it's not a directory we're interested in
            if (current_name.substr(0, 4) != std::string("Live"))
            {
                continue;
            }

            // Alright it's probably a Live Preferences
            // directory so let's try to extract the
            // versions
            current_name = current_name.substr(5, current_name.length());

            // Split the version to get the sperate parts
            std::vector<std::string> versions = split(current_name, '.');

            // Check to make sure the folder has versions
            if (versions.empty())
            {
                continue;
            }

            // Folders can have the version look like
            // 12.0 or 12.0.1 so we should add 0s to the vector
            // if it's the former
            for (auto i = 0; i < (3 - versions.size()); i++)
            {
                versions.push_back("0");
            }

            if (versions[1].find('b') != std::string::npos)
            {
                // handle beta version
                continue;
            }

            uint8_t current_live_version = std::stoi(versions[0]);
            uint8_t current_major_version = std::stoi(versions[1]);
            uint8_t current_minor_version = std::stoi(versions[2]);

            if (current_live_version > live_version)
            {
                live_version = current_live_version;
                major_version = current_major_version;
                minor_version = current_minor_version;
            }
            else if(current_live_version < live_version)
            {
                continue;
            }
            else
            {
                if (current_major_version > major_version)
                {
                    major_version = current_major_version;
                    minor_version = current_minor_version;
                }
                else if (current_major_version < major_version)
                {
                    continue;
                }
                else
                {
                    if (current_minor_version > minor_version)
                    {
                        minor_version = current_minor_version;
                    }
                    else
                    {
                        continue;
                    }
                }
            }

            name = p.path().filename();
        }
    }

    // Now we should end up with the latest Ableton Folder Version
    // So we can grab the Library.cfg file
    fs::path absolute_library_config_file_path = library_config_file_path / name / DEFAULT_ABLETON_LIBRARY_CONFIG_FILE_NAME;

    // Make sure it exists before copying it
    if (!fs::exists(absolute_library_config_file_path))
    {
        // wtf
        return CANT_FIND_LIBRARY_CONFIG_FILE;
    }

    // Copy it over
    // We just copy it to the root backup folder directory since we know
    // it's a special file
    if (!fs::copy_file(absolute_library_config_file_path, backup_folder_path / DEFAULT_ABLETON_LIBRARY_CONFIG_FILE_NAME))
    {
        return CANT_COPY_OVER_LIBRARY_CONFIG_FILE;
    }

    // All Done! Hooray!
    return ERROR_CODE::SUCCESS;
}

ERROR_CODE createBackupZipFile(std::filesystem::path zip_file_location)
{
    // wxFFileOutputStream out;

    // wxFileName zipFile(zip_file_location.string());

    wxFileOutputStream output(wxString(zip_file_location.string()));

    wxZipOutputStream zip(output);

    if (!zip.IsOk())
    {
        return CANT_SAVE_ZIP_FILE;
    }

    wxPlatformInfo* platform_info = new wxPlatformInfo();
    
    std::string os_type = std::string(platform_info->GetOperatingSystemFamilyName());

    fs::path backup_folder_location;
    fs::path temp_folder;

    if (os_type == "Macintosh")
    {
        backup_folder_location = MACOS_TMP_FOLDER_PATH / BACKUP_FOLDER_CREATION_NAME;
        temp_folder = MACOS_TMP_FOLDER_PATH;
    }
    else if (os_type == "Windows")
    {

    }
    else
    {
        // Unsupported OS
        return UNSUPPORTED_OS_DETECTED;
    }

    for (auto &p : fs::recursive_directory_iterator(backup_folder_location))
    {
        if (p.is_directory())
        {
            continue;
        }
        // We need to remove the tmp from path
        std::string relative_path = p.path().string();

        relative_path = relative_path.substr(temp_folder.string().size(), relative_path.length());

        wxFileInputStream input(p.path().string());

        if (!input.IsOk())
        {
            continue;
        }

        // if (p.is_directory())
        // {
        //     zip.PutNextDirEntry(relative_path);
        // }
        // else
        // {
            zip.PutNextEntry(relative_path);
        // }

        zip.Write(input);
    }

    // wxFileInputStream input(backup_folder_location.string());

    // zip.PutNextDirEntry(backup_folder_location.string());
    // zip.Write(input);

    if (!zip.Close())
    {
        return CANT_SAVE_ZIP_FILE;
    }

    output.Close();

    // Lastly delete our working directory in tmp
    if (fs::is_directory(backup_folder_location))
    {
        if (!fs::remove_all(backup_folder_location))
        {
            return ERROR_CODE::CANT_DELETE_BACKUP_FOLDER;
        }
    }

    return ERROR_CODE::SUCCESS;
}

// bool bRet;
//   wxString wsT1;
//   wxString wsTZip = _T("d:\\buptest\\test.zip");
//   wxFileName wfnZipFile( wsTZip);

//   wsT1 = wfnZipFile.GetFullPath();
//   wxFFileOutputStream out( wsT1 );
//   bRet = out.IsOk();

//   wxZipOutputStream zip( out );
//   bRet = zip.IsOk();

//   wxFileName wfnSource( _T("c:\\wbin\\agrep.exe") );
//   wsT1 = wfnSource.GetFullPath();
//   wxFileInputStream in( wfnSource.GetFullPath());
//   bRet = in.IsOk();
 
//   wsT1 = wfnSource.GetFullPath();
//   bRet = zip.PutNextEntry( wfnSource.GetFullPath() );
//   out.Write( in ) ;
//   bRet = zip.Close();