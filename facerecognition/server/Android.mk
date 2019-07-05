LOCAL_PATH := $(call my-dir)

# Build frd
include $(CLEAR_VARS)

LOCAL_CFLAGS +=

D_CFLAGS +=

LOCAL_CFLAGS +=

LOCAL_SRC_FILES := \
       frd.cpp	   \
       ../service/IFrService.cpp

LOCAL_C_INCLUDES := \
		system/biometrics/facerecognition/service \
		system/media/camera/include \
    system/media/private/camera/include \
    frameworks/native/include/media/openmax \
    external/jpeg


LOCAL_SHARED_LIBRARIES += \
    libcutils \
    libutils \
    liblog \
    libbinder \
    libui \
    liblog \
    libutils \
    libmedia \
    libmediautils \
    libcamera_client \
    libgui \
    libhardware \
    libsync \
    libcamera_metadata \
    libjpeg

LOCAL_MODULE := frd
LOCAL_MODULE_PATH := $(TARGET_OUT_EXECUTABLES)
LOCAL_MODULE_TAGS := optional

LOCAL_CFLAGS += $(D_CFLAGS)
LOCAL_CFLAGS += -DDEBUG -Wall

include $(BUILD_EXECUTABLE)
