cmake_minimum_required(VERSION 3.15)

project(ThePankeyEngine_Library_File_Windows)

if(NOT TARGET ThePankeyEngine_Library_File_Windows)

    add_library(ThePankeyEngine_Library_File_Windows INTERFACE)

    target_include_directories(
        ThePankeyEngine_Library_File_Windows
          INTERFACE
            ${CMAKE_CURRENT_SOURCE_DIR}
    )

endif()
