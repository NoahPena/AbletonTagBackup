
#pragma once

#include <string>

#include <wx/platinfo.h>


const std::string ABLETON_TAG_FILE_EXT = ".xmp";

const std::string BACKUP_FOLDER_CREATION_NAME = "ableton_tagging_folder";

const std::string DEFAULT_ABLETON_LIBRARY_CONFIG_FILE_NAME = "Library.cfg";
const std::string DEFAULT_ABLETON_USER_KEYWORDS_FILE_NAME = "UserKeywords.txt";

const std::string MACOS_TMP_FOLDER_PATH = "/tmp/";
const std::string WINDOWS_TMP_FOLDER_PATH = "%TEMP%";

const std::string BASE_DEFAULT_RELATIVE_MACOS_ABLETON_USER_KEYWORDS_FILE_PATH = "/Ableton Folder Info/" + DEFAULT_ABLETON_USER_KEYWORDS_FILE_NAME;
const std::string BASE_DEFAULT_MACOS_ABLETON_PREFERENCES_FOLDER = "/Users/%s/Library/Preferences/Ableton/";
const std::string BASE_DEFAULT_MACOS_ABLETON_DATABASE_FOLDER = "/Users/%s/Library/Application Support/Ableton/";

const std::string BASE_DEFAULT_RELATIVE_WINDOWS_USER_KEYWORDS_FILE_PATH = "" + DEFAULT_ABLETON_USER_KEYWORDS_FILE_NAME;
const std::string BASE_DEFAULT_WINDOWS_ABLETON_PREFERENCES_FOLDER = "";
const std::string BASE_DEFAULT_WINDOWS_ABLETON_DATABASE_FOLDER = "";
