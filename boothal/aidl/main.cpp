/*
 * Copyright (C) 2022 The Android Open Source Project
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
/*
 * Changes from Qualcomm Innovation Center are provided under the following license:
 * Copyright (c) 2023 Qualcomm Innovation Center, Inc. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause-Clear
 */
#include "BootControl.h"

#include <android-base/logging.h>
#include <android/binder_manager.h>
#include <android/binder_process.h>


using aidl::android::hardware::boot::BootControl;
using aidl::android::hardware::boot::IBootControl;

int main(int, char* argv[]) {
    android::base::InitLogging(argv, android::base::KernelLogger);
    ABinderProcess_setThreadPoolMaxThreadCount(0);
    std::shared_ptr<IBootControl> service = ndk::SharedRefBase::make<BootControl>();

    const std::string instance = std::string(BootControl::descriptor) + "/default";
    if (service != NULL) {
        auto status = AServiceManager_addService(service->asBinder().get(), instance.c_str());
        CHECK_EQ(status, STATUS_OK) << "Failed to add service " << instance << " " << status;
        LOG(INFO) << "IBootControl AIDL service running...";

        ABinderProcess_joinThreadPool();
    }
    return EXIT_FAILURE;  // should not reach
}
