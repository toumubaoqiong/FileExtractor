LOCAL_PATH := $(call my-dir)

SRC_ROOT := .

include ./JNIUtil.mk
include ./FileExtractor.mk

include $(CLEAR_VARS)

LOCAL_C_INCLUDES := \
	$(SRC_ROOT)/FileExtractor \
	$(SRC_ROOT)/JNIUtil
	
LOCAL_CFLAGS := -DMAKE_FOR_ANDROID
LOCAL_CXXFLAGS := -DMAKE_FOR_ANDROID

LOCAL_MODULE    := FileExtractor-jni

LOCAL_SRC_FILES := FileExtractor-jni.c

LOCAL_SHARED_LIBRARIES := libFileExtractor libJNIUtil

LOCAL_LDLIBS    := -llog

include $(BUILD_SHARED_LIBRARY)
