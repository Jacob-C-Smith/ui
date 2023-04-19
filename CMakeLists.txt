cmake_minimum_required (VERSION 3.8)

project ("ui")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/extern/)

find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)
find_package(SDL2 REQUIRED CONFIG COMPONENTS SDL2main)
find_package(SDL2_image REQUIRED CONFIG REQUIRED COMPONENTS SDL2_image)

add_subdirectory(${PROJECT_SOURCE_DIR}/json)
find_library(dict NAMES dict HINTS ${PROJECT_SOURCE_DIR}/dict/build/Debug/*)
find_library(array NAMES array HINTS ${PROJECT_SOURCE_DIR}/array/build/Debug/*)
find_library(json NAMES json HINTS ${PROJECT_SOURCE_DIR}/json/build/Debug/*)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

# Add source to this project's executable.
add_executable (ui_example "UI.c" "UIFileSelector.c" "UIWindow.c" "UIButton.c" "UIImage.c" "UICheckbox.c" "UIDropdown.c" "UIElement.c" "UIRadioButton.c" "UILabel.c" "UISlider.c" "UITable.c" "UITextInput.c" "main.c") #     

# Add source to this project's library
add_library    (ui SHARED "UI.c" "UIFileSelector.c" "UIWindow.c" "UIButton.c" "UIImage.c" "UICheckbox.c" "UIDropdown.c" "UIElement.c" "UIRadioButton.c" "UILabel.c" "UISlider.c" "UITextInput.c" "UITable.c") #      

target_link_libraries(ui_example PUBLIC json array dict ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
target_link_libraries(ui PUBLIC json array dict ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
target_link_libraries(ui_example PRIVATE SDL2_image::SDL2_image)
target_link_libraries(ui PRIVATE SDL2_image::SDL2_image)

# Define targets
target_include_directories(ui_example PUBLIC "include/" "json/include/")
target_include_directories(ui PUBLIC "include/" "json/include/")