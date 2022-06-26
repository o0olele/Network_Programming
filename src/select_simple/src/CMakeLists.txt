#查找当前目录下所有源文件并记录文件名到DIR_LIB_SRCS
aux_source_directory(. DIR_LIB_SRCS)
#由这些源文件生成名为wrappers的链接库
add_library( wrappers ${DIR_LIB_SRCS})
