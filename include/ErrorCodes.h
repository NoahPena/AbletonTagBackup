
#pragma once

#include <string>

typedef enum
{
    SUCCESS,
    CANT_CREATE_BACKUP_FOLDER,
    UNSUPPORTED_OS_DETECTED,
    CANT_CREATE_MANIFEST_FILE,
    CANT_DELETE_BACKUP_FOLDER,
    CANT_CREATE_BACKUP_FOLDER_SUBFOLDER,
    CANT_COPY_OVER_FILE_FROM_USER_LIBRARY
} ERROR_CODE;

std::string inline convertErrorCodeToErrorMessage(ERROR_CODE error_code)
{
    return "";
}