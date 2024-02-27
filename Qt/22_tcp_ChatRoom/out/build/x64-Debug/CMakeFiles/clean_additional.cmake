# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "ChatRoom-Client\\CMakeFiles\\ChatRoom-Client_autogen.dir\\AutogenUsed.txt"
  "ChatRoom-Client\\CMakeFiles\\ChatRoom-Client_autogen.dir\\ParseCache.txt"
  "ChatRoom-Client\\ChatRoom-Client_autogen"
  )
endif()
