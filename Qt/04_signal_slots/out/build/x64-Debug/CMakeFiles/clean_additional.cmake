# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\day04_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\day04_autogen.dir\\ParseCache.txt"
  "day04_autogen"
  )
endif()
