cmake_minimum_required (VERSION 3.8)

project ("ui")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

add_subdirectory(${CMAKE_SOURCE_DIR}/JSON)
find_library(dict NAMES dict HINTS ${CMAKE_CURRENT_SOURCE_DIR}/dict/build/Debug/*)
find_library(json NAMES json HINTS ${CMAKE_CURRENT_SOURCE_DIR}/dict/build/Debug/*)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

if(dict)
  message("Found dict")
else()
  message("${CMAKE_CURRENT_SOURCE_DIR}/dict/build/Debug/")
endif()

# Add source to this project's executable.
add_executable (ui_example "UI.c" "UIButton.c" "UICheckbox.c" "UIDropdown.c" "UIElement.c" "UIImage.c" "UILabel.c" "UIRadioButton.c" "UISlider.c" "UITable.c" "UITextInput.c" "UIWindow.c" "main.c")

# Add source to this project's library
add_library    (ui SHARED "UI.c" "UIButton.c" "UICheckbox.c" "UIDropdown.c" "UIElement.c" "UIImage.c" "UILabel.c" "UIRadioButton.c" "UISlider.c" "UITable.c" "UITextInput.c" "UIWindow.c")

target_link_libraries(ui_example PUBLIC json dict ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
target_link_libraries(ui PUBLIC json dict ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
target_link_libraries(ui_example PRIVATE SDL2_image::SDL2_image)
target_link_libraries(ui PRIVATE SDL2_image::SDL2_image)

# Define targets
target_include_directories(ui_example PUBLIC "include/" "JSON/include")
target_include_directories(ui PUBLIC "include/" "JSON/include")


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET json PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
