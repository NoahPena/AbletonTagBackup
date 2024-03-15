
#pragma once

#include "Common.h"
#include "ErrorCodes.h"

ERROR_CODE createBackupFolderAndPopulate(std::filesystem::path user_library_path);

ERROR_CODE gatherTagFiles(std::filesystem::path user_library_path, std::filesystem::path backup_folder_path, std::filesystem::path user_keywords_file_path, std::filesystem::path library_config_file_path);

ERROR_CODE createBackupZipFile(std::filesystem::path zip_file_location);