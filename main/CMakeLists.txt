# Get all cpp-files in the current directory
file(GLOB main_list RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)


foreach(main_filename ${main_list})
  # Get file name without extension
  get_filename_component(main ${main_filename} NAME_WE)

  # Add and configure executable file to be produced
  add_executable(${main} ${main_filename})
  target_link_libraries(${main} ${MP2_LIBRARY})
  set_target_properties(${main} PROPERTIES
    OUTPUT_NAME "${main}"
    PROJECT_LABEL "${main}"
    RUNTIME_OUTPUT_DIRECTORY "../")
endforeach()
