# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "23_WebSocket_FileTransfer_autogen"
  "CMakeFiles\\23_WebSocket_FileTransfer_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\23_WebSocket_FileTransfer_autogen.dir\\ParseCache.txt"
  )
endif()
