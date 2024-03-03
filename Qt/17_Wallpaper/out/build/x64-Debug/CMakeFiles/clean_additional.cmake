# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "17_Wallpaper_autogen"
  "CMakeFiles\\17_Wallpaper_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\17_Wallpaper_autogen.dir\\ParseCache.txt"
  )
endif()
