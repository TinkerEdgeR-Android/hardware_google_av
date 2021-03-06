/*
 * Copyright 2018 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

//#define LOG_NDEBUG 0
#define LOG_TAG "C2SoftwareCodecServiceRegistrant"

#include <C2PlatformSupport.h>
#include <codec2/hidl/1.0/ComponentStore.h>
#include <media/CodecServiceRegistrant.h>
#include <media/stagefright/omx/1.0/Omx.h>
#include <log/log.h>

extern "C" void RegisterCodecServices() {
    using namespace ::hardware::google::media::c2::V1_0;
    android::sp<IComponentStore> store =
        new utils::ComponentStore(
                android::GetCodec2PlatformComponentStore());
    if (store == nullptr) {
        ALOGE("Cannot create Codec2's IComponentStore software service.");
    } else {
        if (store->registerAsService("software") != android::OK) {
            ALOGE("Cannot register Codec2's "
                    "IComponentStore software service.");
        } else {
            ALOGI("Codec2's IComponentStore software service created.");
        }
    }

    // Default codec services
    using namespace ::android::hardware::media::omx::V1_0;
    android::sp<IOmx> omx = new implementation::Omx();
    if (omx == nullptr) {
        ALOGE("Cannot create IOmx HAL service.");
    } else if (omx->registerAsService() != android::OK) {
        ALOGE("Cannot register IOmx HAL service.");
    }

}

