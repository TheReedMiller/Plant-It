cmake_minimum_required(VERSION 3.30)
project(Plant-It)
set(APPLICATION_LIBRARY GameLib)

set(CMAKE_CXX_STANDARD 17)

# Request the required wxWidgets libs
# Turn off wxWidgets own precompiled header system
set(wxBUILD_PRECOMP OFF)
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)

# Include the wxWidgets use file to initialize various settings
include(${wxWidgets_USE_FILE})

add_subdirectory(${APPLICATION_LIBRARY})
include_directories(${APPLICATION_LIBRARY})

# Define a variable containing a list of source files for the project
set(SOURCE_FILES main.cpp
        GameApp.cpp
        GameApp.h
        pch.h)

add_executable(Plant-It WIN32 MACOSX_BUNDLE ${SOURCE_FILES})

# Link required libraries to the executable
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES} ${APPLICATION_LIBRARY})
target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)

file(COPY resources/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

# Path to the source Levels/ directory
set(LEVELS_SRC "${CMAKE_CURRENT_SOURCE_DIR}/resources/Levels")

# Destination in the .app bundle
set(LEVELS_DST "${CMAKE_CURRENT_BINARY_DIR}/Plant-It.app/Contents/Resources/Levels")

# Copy Levels/ into the app bundle after build
add_custom_command(TARGET Plant-It POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory "${LEVELS_DST}"
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${LEVELS_SRC}" "${LEVELS_DST}"
)

if(APPLE)
    set(MACOSX_BUNDLE_ICON_FILE Plant-It)

    set_source_files_properties(resources/Images/Plant-It.icns PROPERTIES
            MACOSX_PACKAGE_LOCATION "Resources")

    set_source_files_properties(${CMAKE_CURRENT_SOURCE_DIR}/Info.plist PROPERTIES
            MACOSX_PACKAGE_LOCATION "Contents")

    set_target_properties(Plant-It PROPERTIES
            MACOSX_BUNDLE TRUE
            MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/Info.plist"
    )

    target_sources(Plant-It PRIVATE
            resources/Images/Plant-It.icns
            ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist
    )

    set_target_properties(Plant-It PROPERTIES
            MACOSX_BUNDLE_ICON_FILE "Plant-It.icns"  # Include .icns extension here
    )
endif()

