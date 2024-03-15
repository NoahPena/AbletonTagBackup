
#include "CreateBackup.h"

#include <wx/stdpaths.h>

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
        std::cout << "A" << std::endl;
        if (!fs::remove_all(backup_folder_path))
        {
            std::cout << "B" << std::endl;
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
    std::cout << "Bob" << user_library_path << "\nJessica" << user_keywords_file_path << std::endl;
    fs::path temp = user_library_path / user_keywords_file_path;
    std::cout << temp.string() << std::endl;
    if (fs::is_regular_file(user_library_path / user_keywords_file_path))
    {
        std::cout << "yo" << std::endl;
        // Convert the full path to a relative path
        // by getting rid of the user_library_path
        std::string temp_string = user_keywords_file_path.string();
        temp_string = temp_string.substr(sizeof(user_library_path) - 1, temp_string.length());
        fs::path relative_user_keywords_path(temp_string);

        std::cout << backup_folder_path / relative_user_keywords_path << std::endl;

        // Create the directory in the backup folder
        if (!fs::create_directories(backup_folder_path / user_keywords_file_path))
        {
            return ERROR_CODE::CANT_CREATE_BACKUP_FOLDER_SUBFOLDER;
        }

        // Copy over the file
        if (!fs::copy_file(user_library_path / user_keywords_file_path / DEFAULT_ABLETON_USER_KEYWORDS_FILE_NAME, backup_folder_path / user_keywords_file_path))
        {
            return ERROR_CODE::CANT_COPY_OVER_FILE_FROM_USER_LIBRARY;
        }
    }

    // Next is to copy over the Ableton LibraryConfig file


    return ERROR_CODE::SUCCESS;
}

ERROR_CODE createBackupZipFile(std::filesystem::path zip_file_location)
{
    return ERROR_CODE::SUCCESS;
}