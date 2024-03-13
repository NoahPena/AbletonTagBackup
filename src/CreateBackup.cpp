
#include "CreateBackup.h"

#include <wx/stdpaths.h>

#include <filesystem>

namespace fs = std::filesystem;

std::string createBackupFolder(std::string user_library_path)
{
    wxPlatformInfo* platform_info = new wxPlatformInfo();
    wxOperatingSystemId os_type = platform_info->GetOperatingSystemId();

    // std::string username_path = wxStandardPaths::Get().GetUserDir();



    // Convert to paths
    fs::path backup_folder_location;
    fs::path user_keywords_path;
    fs::path library_config_path;

    if (os_type == wxOS_MAC)
    {
        backup_folder_location = MACOS_TMP_FOLDER_PATH + BACKUP_FOLDER_CREATION_NAME;
        user_keywords_path = user_library_path + BASE_DEFAULT_RELATIVE_MACOS_ABLETON_USER_KEYWORDS_FILE_PATH;
        // library_config_path = BASE_DEFAULT_MACOS_ABLETON_PREFERENCES_FOLDER.replace(BASE_DEFAULT_MACOS_ABLETON_PREFERENCES_FOLDER.find("%s"), sizeof("%s") - 1, "Bob");
    }
    else if (os_type == wxOS_WINDOWS)
    {

    }
    else
    {
        // Unsupported OS
        return "";
    }
}

std::string createBackupZipFile(std::string zip_file_location)
{

}