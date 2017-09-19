LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_CFLAGS := -Wall -Werror

LOCAL_SRC_FILES += \
    alloctest.cpp

LOCAL_SHARED_LIBRARIES += \
    libcutils   \
    liblog      \
    libutils    \
    libhardware  \
    libbase          \
    libfmq           \
    libhwbinder      \
    libhidlbase      \
    libhidlmemory    \
    libhidltransport \
    android.hidl.allocator@1.0 \
    android.hidl.memory@1.0

LOCAL_MODULE := alloctest

include $(BUILD_EXECUTABLE)
