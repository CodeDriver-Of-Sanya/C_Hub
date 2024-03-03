# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\LoginRegister_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\LoginRegister_autogen.dir\\ParseCache.txt"
  "LoginRegister_autogen"
  )
endif()
