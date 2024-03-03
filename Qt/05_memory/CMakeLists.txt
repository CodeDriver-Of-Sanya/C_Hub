# CMakeList.txt: 05_memory 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

# 如果支持，请为 MSVC 编译器启用热重载。
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

#指定项目名称
project ("05_memory")

#设置自动moc
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

#指定C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#在MSVC上必须指定 /Zc:__cplusplus 选项
if(MSVC)
	add_compile_options(/Zc:__cplusplus)
endif()

#指定头文件包含目录
include_directories("C:/Qt/6.5.2/msvc2019_64/include")
#查找指定模块
find_package(Qt6 COMPONENTS Widgets REQUIRED)
#配置资源文件（将源代码添加到此项目的可执行文件）
set(PROJECT_SOURCES 
	main.cpp
)
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

#指定 exe 等目标 生成位置
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)

#给目标连接库文件
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()

# TODO: 如有需要，请添加测试并安装目标。
