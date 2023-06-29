cmake_minimum_required (VERSION 3.8)

project ("ui")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/extern/)

find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)
find_package(SDL2 REQUIRED CONFIG COMPONENTS SDL2main)
find_package(SDL2_image REQUIRED CONFIG REQUIRED COMPONENTS SDL2_image)

if ( NOT ("${HAS_JSON}"))
	message("[G10] adding json project")
    add_subdirectory(${CMAKE_SOURCE_DIR}/extern/json ${CMAKE_SOURCE_DIR}/build/json)
endif()

if ( NOT ("${HAS_ARRAY}"))
	message("[G10] adding array project")
    add_subdirectory(${CMAKE_SOURCE_DIR}/extern/array ${CMAKE_SOURCE_DIR}/build/array)
endif()

if ( NOT ("${HAS_DICT}"))
	message("[G10] adding dict project")
    add_subdirectory(${CMAKE_SOURCE_DIR}/extern/dict ${CMAKE_SOURCE_DIR}/build/dict)
endif()

if ( NOT "${HAS_UI}")
    set(HAS_UI true PARENT_SCOPE)
endif()

find_library(dict  NAMES dict  HINTS ${CMAKE_SOURCE_DIR}/extern/dict/build/Debug/*)
find_library(array NAMES array HINTS ${CMAKE_SOURCE_DIR}/extern/array/build/Debug/*)
find_library(json  NAMES json  HINTS ${CMAKE_SOURCE_DIR}/extern/json/build/Debug/*)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

# Add source to this project's executable.
add_executable (ui_example "UI.c" "UIFileSelector.c" "UIWindow.c" "UIButton.c" "UIImage.c" "UICheckbox.c" "UIDropdown.c" "UIElement.c" "UIRadioButton.c" "UILabel.c" "UISlider.c" "UITextInput.c" "UITable.c" "main.c") #     
add_dependencies(ui_example json array dict)
target_include_directories(ui_example PUBLIC include ${CMAKE_SOURCE_DIR}/extern/json/include/ ${CMAKE_SOURCE_DIR}/extern/array/include/ ${CMAKE_SOURCE_DIR}/extern/dict/include/) 
target_link_libraries(ui_example PUBLIC json array dict ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} )

# Add source to this project's library
add_library (ui SHARED "UI.c" "UIFileSelector.c" "UIWindow.c" "UIButton.c" "UIImage.c" "UICheckbox.c" "UIDropdown.c" "UIElement.c" "UIRadioButton.c" "UILabel.c" "UISlider.c" "UITextInput.c" "UITable.c") #      
add_dependencies(ui json array dict )
target_include_directories(ui PUBLIC include ${CMAKE_SOURCE_DIR}/extern/json/include/ ${CMAKE_SOURCE_DIR}/extern/array/include/ ${CMAKE_SOURCE_DIR}/extern/dict/include/) 
target_link_libraries(ui PUBLIC json array dict ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} )
