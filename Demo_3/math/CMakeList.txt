# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_LIB_SRCS变量
aux_source_directory(. DIR_LIB_SRCS)

add_library(MathFunctions ${DIR_LIB_SRCS})
