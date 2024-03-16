
#pragma once

#include <string>
#include <filesystem>
#include <vector>
#include <iostream>
#include <sstream>

#include <wx/platinfo.h>


const std::string ABLETON_TAG_FILE_EXT = ".xmp";

const std::filesystem::path BACKUP_FOLDER_CREATION_NAME = "ableton_tagging_folder";
const std::filesystem::path BACKUP_FOLDER_MANIFEST_FILE_NAME = "Manifest.txt";

const std::filesystem::path DEFAULT_ABLETON_LIBRARY_CONFIG_FILE_NAME = "Library.cfg";
const std::filesystem::path DEFAULT_ABLETON_USER_KEYWORDS_FILE_NAME = "UserKeywords.txt";

const std::filesystem::path MACOS_TMP_FOLDER_PATH = "/tmp/";
const std::filesystem::path WINDOWS_TMP_FOLDER_PATH = "%TEMP%";

const std::filesystem::path BASE_DEFAULT_RELATIVE_MACOS_ABLETON_USER_KEYWORDS_FILE_PATH = "Ableton Folder Info/" / DEFAULT_ABLETON_USER_KEYWORDS_FILE_NAME;
const std::filesystem::path BASE_DEFAULT_MACOS_ABLETON_PREFERENCES_FOLDER = "/Users/%s/Library/Preferences/Ableton/";
const std::filesystem::path BASE_DEFAULT_MACOS_ABLETON_DATABASE_FOLDER = "/Users/%s/Library/Application Support/Ableton/";

const std::filesystem::path BASE_DEFAULT_RELATIVE_WINDOWS_USER_KEYWORDS_FILE_PATH = "" / DEFAULT_ABLETON_USER_KEYWORDS_FILE_NAME;
const std::filesystem::path BASE_DEFAULT_WINDOWS_ABLETON_PREFERENCES_FOLDER = "";
const std::filesystem::path BASE_DEFAULT_WINDOWS_ABLETON_DATABASE_FOLDER = "";

const std::string MANIFEST_FILE_HEADER = "////////////////////////////////////////////////////////\n"
                                         "// Go to https://github.com/NoahPena/AbletonTagBackup //\n"
                                         "// For More Details on How to Use This Backup         //\n"
                                         "////////////////////////////////////////////////////////\n";



std::vector<std::string> split (const std::string &s, char delim);