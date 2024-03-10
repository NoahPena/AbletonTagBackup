cmake_minimum_required(VERSION 3.8)
project(ableton-tag-backup)

# add_subdirectory(division)
set(SOURCE_FILES main.cpp)

# add_executable(ableton-tag-backup-src ${SOURCE_FILES})
# target_link_libraries(divider division)


if(APPLE)
    # create bundle on apple compiles
    add_executable(ableton-tag-backup MACOSX_BUNDLE ${SOURCE_FILES})

    # Set a custom plist file for the app bundle - needed for Mac OS Retina display
    set_target_properties(ableton-tag-backup PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/Info.plist)
else()
    # the WIN32 is needed for Windows in order for it to look for WinMain
    # instead of the main function. This is ignored on other systems,
    # so it works on all platforms
    add_executable(ableton-tag-backup WIN32 ${SOURCE_FILES} ${CMAKE_SOURCE_DIR}/main.exe.manifest)
endif()

target_link_libraries(ableton-tag-backup PRIVATE wxcore wxnet)

install(TARGETS ableton-tag-backup DESTINATION bin/)

