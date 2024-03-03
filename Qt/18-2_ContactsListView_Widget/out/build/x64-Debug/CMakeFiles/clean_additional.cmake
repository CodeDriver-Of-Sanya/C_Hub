# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "18-2_ContactsListView_Widget_autogen"
  "CMakeFiles\\18-2_ContactsListView_Widget_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\18-2_ContactsListView_Widget_autogen.dir\\ParseCache.txt"
  )
endif()
