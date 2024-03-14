
#include "CreateBackup.h"

#include <wx/stdpaths.h>

#include <filesystem>
#include <regex>
#include <iostream>

namespace fs = std::filesystem;

std::string createBackupFolder(std::string user_library_path)
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

        backup_folder_location = MACOS_TMP_FOLDER_PATH + BACKUP_FOLDER_CREATION_NAME;
        user_keywords_path = user_library_path + BASE_DEFAULT_RELATIVE_MACOS_ABLETON_USER_KEYWORDS_FILE_PATH;
        library_config_path = std::regex_replace(BASE_DEFAULT_MACOS_ABLETON_PREFERENCES_FOLDER, std::regex("%s"), username_path);

        std::cout << library_config_path << std::endl;
        // library_config_path = BASE_DEFAULT_MACOS_ABLETON_PREFERENCES_FOLDER.replace(BASE_DEFAULT_MACOS_ABLETON_PREFERENCES_FOLDER.find("%s"), 2, username_path);
        // library_config_path = BASE_DEFAULT_MACOS_ABLETON_PREFERENCES_FOLDER.replace(BASE_DEFAULT_MACOS_ABLETON_PREFERENCES_FOLDER.find("%s"), sizeof("%s") - 1, "Bob");
    }
    else if (os_type == "Windows")
    {

    }
    else
    {
        // Unsupported OS
        return "";
    }

    return "";
}

std::string createBackupZipFile(std::string zip_file_location)
{

}