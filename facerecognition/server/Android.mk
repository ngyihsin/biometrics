LOCAL_PATH := $(call my-dir)

# Build frd
include $(CLEAR_VARS)

LOCAL_CFLAGS +=

D_CFLAGS +=

LOCAL_CFLAGS +=

LOCAL_SRC_FILES := \
       frd.cpp	   \
       ../service/IFrService.cpp

LOCAL_C_INCLUDES := system/biometrics/facerecognition/service

LOCAL_SHARED_LIBRARIES += \
    libcutils \
    libutils \
    liblog \
    libbinder

LOCAL_MODULE := frd
LOCAL_MODULE_PATH := $(TARGET_OUT_EXECUTABLES)
LOCAL_MODULE_TAGS := optional

LOCAL_CFLAGS += $(D_CFLAGS)
LOCAL_CFLAGS += -DDEBUG -Wall

include $(BUILD_EXECUTABLE)
