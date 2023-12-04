# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "RelWithDebInfo")
  file(REMOVE_RECURSE
  "test_QDialog\\CMakeFiles\\test_QDialog_autogen.dir\\AutogenUsed.txt"
  "test_QDialog\\CMakeFiles\\test_QDialog_autogen.dir\\ParseCache.txt"
  "test_QDialog\\test_QDialog_autogen"
  "test_QWidget\\CMakeFiles\\test_QWidget_autogen.dir\\AutogenUsed.txt"
  "test_QWidget\\CMakeFiles\\test_QWidget_autogen.dir\\ParseCache.txt"
  "test_QWidget\\test_QWidget_autogen"
  "test_other\\CMakeFiles\\test_other_autogen.dir\\AutogenUsed.txt"
  "test_other\\CMakeFiles\\test_other_autogen.dir\\ParseCache.txt"
  "test_other\\test_other_autogen"
  )
endif()
