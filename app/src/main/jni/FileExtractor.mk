LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

SRC_ROOT := .

LOCAL_C_INCLUDES := \
    $(SRC_ROOT)/7z_C \
    $(SRC_ROOT)/fex \
    $(SRC_ROOT)/FileSystem \
    $(SRC_ROOT)/Print \
    $(SRC_ROOT)/unrar \
    $(SRC_ROOT)/zlib 

LOCAL_CFLAGS := -DMAKE_FOR_ANDROID
LOCAL_CXXFLAGS := -DMAKE_FOR_ANDROID

LOCAL_MODULE    := FileExtractor

LOCAL_SRC_FILES := \
	$(SRC_ROOT)/FileExtractor/7z_C/7zAlloc.c \
	$(SRC_ROOT)/FileExtractor/7z_C/7zBuf.c \
	$(SRC_ROOT)/FileExtractor/7z_C/7zCrc.c \
	$(SRC_ROOT)/FileExtractor/7z_C/7zDecode.c \
	$(SRC_ROOT)/FileExtractor/7z_C/7zExtract.c \
	$(SRC_ROOT)/FileExtractor/7z_C/7zHeader.c \
	$(SRC_ROOT)/FileExtractor/7z_C/7zIn.c \
	$(SRC_ROOT)/FileExtractor/7z_C/7zItem.c \
	$(SRC_ROOT)/FileExtractor/7z_C/7zStream.c \
	$(SRC_ROOT)/FileExtractor/7z_C/Bcj2.c \
	$(SRC_ROOT)/FileExtractor/7z_C/Bra86.c \
	$(SRC_ROOT)/FileExtractor/7z_C/LzmaDec.c \
    $(SRC_ROOT)/FileExtractor/fex/Binary_Extractor.cpp \
    $(SRC_ROOT)/FileExtractor/fex/blargg_common.cpp \
    $(SRC_ROOT)/FileExtractor/fex/blargg_errors.cpp \
    $(SRC_ROOT)/FileExtractor/fex/Data_Reader.cpp \
    $(SRC_ROOT)/FileExtractor/fex/fex.cpp \
    $(SRC_ROOT)/FileExtractor/fex/File_Extractor.cpp \
    $(SRC_ROOT)/FileExtractor/fex/Gzip_Extractor.cpp \
    $(SRC_ROOT)/FileExtractor/fex/Gzip_Reader.cpp \
    $(SRC_ROOT)/FileExtractor/fex/Rar_Extractor.cpp \
    $(SRC_ROOT)/FileExtractor/fex/Zip_Extractor.cpp \
    $(SRC_ROOT)/FileExtractor/fex/Zip7_Extractor.cpp \
    $(SRC_ROOT)/FileExtractor/fex/Zlib_Inflater.cpp \
    $(SRC_ROOT)/FileExtractor/FileSystem/FileSystem.c \
    $(SRC_ROOT)/FileExtractor/Print/Print.c \
    $(SRC_ROOT)/FileExtractor/unrar/archive.cpp \
    $(SRC_ROOT)/FileExtractor/unrar/arcread.cpp \
    $(SRC_ROOT)/FileExtractor/unrar/coder.cpp \
    $(SRC_ROOT)/FileExtractor/unrar/crc.cpp \
    $(SRC_ROOT)/FileExtractor/unrar/encname.cpp \
    $(SRC_ROOT)/FileExtractor/unrar/extract.cpp \
    $(SRC_ROOT)/FileExtractor/unrar/getbits.cpp \
    $(SRC_ROOT)/FileExtractor/unrar/model.cpp \
    $(SRC_ROOT)/FileExtractor/unrar/rarvm.cpp \
    $(SRC_ROOT)/FileExtractor/unrar/rarvmtbl.cpp \
    $(SRC_ROOT)/FileExtractor/unrar/rawread.cpp \
    $(SRC_ROOT)/FileExtractor/unrar/suballoc.cpp \
    $(SRC_ROOT)/FileExtractor/unrar/unicode.cpp \
    $(SRC_ROOT)/FileExtractor/unrar/unpack.cpp \
    $(SRC_ROOT)/FileExtractor/unrar/unpack15.cpp \
    $(SRC_ROOT)/FileExtractor/unrar/unpack20.cpp \
    $(SRC_ROOT)/FileExtractor/unrar/unrar_misc.cpp \
    $(SRC_ROOT)/FileExtractor/unrar/unrar_open.cpp \
    $(SRC_ROOT)/FileExtractor/unrar/unrar.cpp \
    $(SRC_ROOT)/FileExtractor/zlib/adler32.c \
    $(SRC_ROOT)/FileExtractor/zlib/crc32.c \
	$(SRC_ROOT)/FileExtractor/zlib/inffast.c \
	$(SRC_ROOT)/FileExtractor/zlib/inflate.c \
	$(SRC_ROOT)/FileExtractor/zlib/inftrees.c \
	$(SRC_ROOT)/FileExtractor/zlib/zutil.c
	
LOCAL_LDLIBS    := -llog

include $(BUILD_SHARED_LIBRARY)
