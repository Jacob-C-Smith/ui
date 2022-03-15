#pragma once

#include <stdio.h>

// Test everything
size_t ui_test_all                       ( void );

// Test specific components
size_t ui_test_button                    ( void );
size_t ui_test_canvas                    ( void );
size_t ui_test_chart                     ( void );
size_t ui_test_checkbox                  ( void );
size_t ui_test_container                 ( void );
size_t ui_test_dropdown                  ( void );
size_t ui_test_element                   ( void );
size_t ui_test_image                     ( void );
size_t ui_test_label                     ( void );
size_t ui_test_radio_button              ( void );
size_t ui_test_slider                    ( void );
size_t ui_test_text_input                ( void );
size_t ui_test_window                    ( void );

// Button tests
size_t ui_test_button_allocators         ( void );
size_t ui_test_button_constructors       ( void );
size_t ui_test_button_callbacks          ( void );
size_t ui_test_button_deallocators       ( void );

// Canvas tests
size_t ui_test_canvas_allocators         ( void );
size_t ui_test_canvas_constructors       ( void );
size_t ui_test_canvas_callbacks          ( void );
size_t ui_test_canvas_deallocators       ( void );

// Chart tests
size_t ui_test_chart_allocators          ( void );
size_t ui_test_chart_constructors        ( void );
size_t ui_test_chart_callbacks           ( void );
size_t ui_test_chart_deallocators        ( void );

// Checkbox tests
size_t ui_test_checkbox_allocators       ( void );
size_t ui_test_checkbox_constructors     ( void );
size_t ui_test_checkbox_callbacks        ( void );
size_t ui_test_checkbox_deallocators     ( void );

// Container tests
size_t ui_test_container_allocators      ( void );
size_t ui_test_container_constructors    ( void );
size_t ui_test_container_callbacks       ( void );
size_t ui_test_container_deallocators    ( void );

// Dropdown tests
size_t ui_test_dropdown_allocators       ( void );
size_t ui_test_dropdown_constructors     ( void );
size_t ui_test_dropdown_callbacks        ( void );
size_t ui_test_dropdown_deallocators     ( void );

// Element tests
size_t ui_test_element_allocators        ( void );
size_t ui_test_element_constructors      ( void );
size_t ui_test_element_callbacks         ( void );
size_t ui_test_element_deallocators      ( void );

// Image tests
size_t ui_test_image_allocators          ( void );
size_t ui_test_image_constructors        ( void );
size_t ui_test_image_callbacks           ( void );
size_t ui_test_image_deallocators        ( void );

// Label tests
size_t ui_test_label_allocators          ( void );
size_t ui_test_label_constructors        ( void );
size_t ui_test_label_callbacks           ( void );
size_t ui_test_label_deallocators        ( void );

// Radio button tests
size_t ui_test_radio_button_allocators   ( void );
size_t ui_test_radio_button_constructors ( void );
size_t ui_test_radio_button_callbacks    ( void );
size_t ui_test_radio_button_deallocators ( void );

// Slider tests
size_t ui_test_slider_allocators         ( void );
size_t ui_test_slider_constructors       ( void );
size_t ui_test_slider_callbacks          ( void );
size_t ui_test_slider_deallocators       ( void );

// Text input tests
size_t ui_test_text_input_allocators     ( void );
size_t ui_test_text_input_constructors   ( void );
size_t ui_test_text_input_callbacks      ( void );
size_t ui_test_text_input_deallocators   ( void );