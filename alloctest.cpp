#define LOG_TAG "AllocTest"
#define LOG_NDEBUG 0

#include <android/hidl/allocator/1.0/IAllocator.h>
#include <utils/Log.h>

using android::hidl::allocator::V1_0::IAllocator;
using android::sp;
using android::status_t;
using android::hardware::Return;
using android::hardware::hidl_memory;
using android::NO_INIT;
using android::NO_MEMORY;
using android::FAILED_TRANSACTION;
using android::OK;

status_t testAllocate(int size) {
    sp<IAllocator> ashmem = IAllocator::getService("ashmem");
    if (ashmem == 0) {
        ALOGE("Failed to retrieve ashmem allocator service");
        return NO_INIT;
    }
    ALOGE("Trying to allocate %d bytes from ashmem", size);
    
    status_t retval = NO_MEMORY;
    Return<void> result = ashmem->allocate(
        size,
        [&](bool success, const hidl_memory&) {
            ALOGE("Callback from allocate %d bytes from ashmem with success = %d", size, success);
            if (success) {
                retval = OK;
            }
        });
    if (result.isOk() && retval == OK) {
        ALOGE("Allocated %d bytes from ashmem", size);
    } else {
        ALOGE("Failed to allocate %d bytes from ashmem", size);
    }
    return result.isOk() ? retval : FAILED_TRANSACTION;
}

int main() {
    status_t res = testAllocate(4096);
    if (res == OK) {
        printf("Yay\n");
    } else {
        printf("Nay\n");
    }
    return 0;
}
