LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

SRC_ROOT := .

LOCAL_C_INCLUDES := \
    $(SRC_ROOT)

LOCAL_CFLAGS := -DMAKE_FOR_ANDROID
LOCAL_CXXFLAGS := -DMAKE_FOR_ANDROID

LOCAL_MODULE    := JNIUtil

LOCAL_SRC_FILES := \
	$(SRC_ROOT)/JNIUtil/Code_Conversion.cpp \
	$(SRC_ROOT)/JNIUtil/EncodeTransform.cpp \
	$(SRC_ROOT)/JNIUtil/JNIUtil.c \
	$(SRC_ROOT)/JNIUtil/JNIUtilPrint.c 
	
LOCAL_LDLIBS    := -llog

include $(BUILD_SHARED_LIBRARY)
#include $(PREBUILT_STATIC_LIBRARY)
