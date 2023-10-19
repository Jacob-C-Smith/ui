cmake_minimum_required (VERSION 3.8)

project ("ui")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/extern/)

IF(WIN32)
    find_package(SDL2_image REQUIRED CONFIG REQUIRED COMPONENTS SDL2_image)
ELSEIF(LINUX)
    set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
    find_package(SDL2_image REQUIRED)
ELSEIF(APPLE)

ENDIF(WIN32)

find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)
find_package(SDL2 REQUIRED CONFIG COMPONENTS SDL2main)

# Find the array module
if ( NOT "${HAS_ARRAY}")
    
    # Log
    message("[ui] Adding array project")
    
    # Add the array directory
    add_subdirectory(${CMAKE_SOURCE_DIR}/extern/array ${CMAKE_SOURCE_DIR}/build/array)

    # Let any parent project know that this project has array
    set(HAS_ARRAY true PARENT_SCOPE)
endif()

# Find the dict module
if ( NOT "${HAS_DICT}")
    
    # Log
    message("[ui] Adding dict project")
    
    # Add the dict directory
    add_subdirectory(${CMAKE_SOURCE_DIR}/extern/dict ${CMAKE_SOURCE_DIR}/build/dict)

    # Let any parent project know that this project has dict
    set(HAS_DICT true PARENT_SCOPE)
endif()

# Find the sync module
if ( NOT "${HAS_SYNC}")

    # Log
    message("[ui] Adding sync project")

    # Add the sync directory
    add_subdirectory(${CMAKE_SOURCE_DIR}/extern/sync ${CMAKE_SOURCE_DIR}/build/sync)

    # Let any parent project know that this project has sync
    set(HAS_SYNC true PARENT_SCOPE)
endif()

# Find the json module
if ( NOT "${HAS_JSON}")

    # Log
    message("[ui] Adding json project")

    # Add the json directory
    add_subdirectory(${CMAKE_SOURCE_DIR}/extern/json ${CMAKE_SOURCE_DIR}/build/json)

    # Let any parent project know that this project has json
    set(HAS_JSON true PARENT_SCOPE)
endif()

if ( NOT "${HAS_UI}")
    set(HAS_UI true PARENT_SCOPE)
endif()

find_library(dict  NAMES dict  HINTS ${CMAKE_SOURCE_DIR}/extern/dict/build/Debug/*)
find_library(array NAMES array HINTS ${CMAKE_SOURCE_DIR}/extern/array/build/Debug/*)
find_library(json  NAMES json  HINTS ${CMAKE_SOURCE_DIR}/extern/json/build/Debug/*)

# Add source to this project's executable.
add_executable (ui_example "main.c")
add_dependencies(ui_example json array dict)
target_include_directories(ui_example PUBLIC include ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/extern/json/include/ ${CMAKE_SOURCE_DIR}/extern/array/include/ ${CMAKE_SOURCE_DIR}/extern/dict/include/) 
IF(WIN32)
    target_link_libraries(ui_example PUBLIC ui json array dict PRIVATE SDL2_image::SDL2_image ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
ELSEIF(LINUX)
    target_link_libraries(ui_example PUBLIC ui json array dict ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
ELSEIF(APPLE)

ENDIF(WIN32)


# Add source to this project's library
add_library (ui SHARED "ui.c" "fileselector.c" "window.c" "button.c" "image.c" "checkbox.c" "dropdown.c" "element.c" "radiobutton.c" "label.c" "slider.c" "textinput.c" "table.c") #      
add_dependencies(ui json array dict )
target_include_directories(ui PUBLIC include ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/extern/json/include/ ${CMAKE_SOURCE_DIR}/extern/array/include/ ${CMAKE_SOURCE_DIR}/extern/dict/include/) 
IF(WIN32)
    target_link_libraries(ui PUBLIC json array dict PRIVATE SDL2_image::SDL2_image ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
ELSEIF(LINUX)
    target_link_libraries(ui PUBLIC json array dict ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
ELSEIF(APPLE)

ENDIF(WIN32)

