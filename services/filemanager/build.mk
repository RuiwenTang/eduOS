LOCAL_MODULE_NAME := filemanager

LOCAL_SRC_FILES := \
	main.c

LOCAL_CXX_FLAGS := \
	-std=c++14

-include $(TOPDIR)/build_executable.mk