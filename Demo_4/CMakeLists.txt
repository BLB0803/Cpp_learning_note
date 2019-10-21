# CMake最低版本号要求
cmake_minimum_required(VERSION 2.8)

# 项目信息
project(Demo_4)

# 加入一个配置头文件，用于处理CMake对源码的设置
configure_file(
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
  )

# 是否使用自己的MathFunctions库
option(USE_MYMATH
       "Use provided math implementation"
	ON
  )

# 是否加入MathFunctions库
if (USE_MYMATH)
  # 添加头文件路径
  include_directories("${PROJECT_SOURCE_DIR}/math")
  # 添加math子目录
  add_subdirectory(math)
  # 收集可选库地址存于EXTRA_LIBS
  set(EXTRA_LIBS ${EXTRA_LIBS} MathFunctions)
endif (USE_MYMATH)

# 查找当前目录下的所有源文件，并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)

# 指定生成目标
add_executable(Demo ${DIR_SRCS})

# 添加链接库
target_link_libraries(Demo ${EXTRA_LIBS})



