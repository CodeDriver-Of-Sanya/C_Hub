# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "19-2_ModelView_BookManagerSystem_autogen"
  "CMakeFiles\\19-2_ModelView_BookManagerSystem_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\19-2_ModelView_BookManagerSystem_autogen.dir\\ParseCache.txt"
  "LoginRegister\\CMakeFiles\\LoginRegister_autogen.dir\\AutogenUsed.txt"
  "LoginRegister\\CMakeFiles\\LoginRegister_autogen.dir\\ParseCache.txt"
  "LoginRegister\\LoginRegister_autogen"
  "UiTools\\CMakeFiles\\UiTools_autogen.dir\\AutogenUsed.txt"
  "UiTools\\CMakeFiles\\UiTools_autogen.dir\\ParseCache.txt"
  "UiTools\\UiTools_autogen"
  )
endif()
