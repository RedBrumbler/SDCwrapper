# Copyright (C) 2009 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.


LOCAL_PATH := $(call my-dir)
TARGET_ARCH_ABI := $(APP_ABI)

rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

# Creating prebuilt for dependency: songdatacore - version: 0.4.1
include $(CLEAR_VARS)
LOCAL_MODULE := android-libsong_data_core_rust
LOCAL_EXPORT_C_INCLUDES := extern/songdatacore
LOCAL_SRC_FILES := extern/libandroid-libsong_data_core_rust.so
include $(PREBUILT_SHARED_LIBRARY)
# Creating prebuilt for dependency: beatsaber-hook - version: 2.3.0
include $(CLEAR_VARS)
LOCAL_MODULE := beatsaber-hook_2_3_0
LOCAL_EXPORT_C_INCLUDES := extern/beatsaber-hook
LOCAL_SRC_FILES := extern/libbeatsaber-hook_2_3_0.so
include $(PREBUILT_SHARED_LIBRARY)
# Creating prebuilt for dependency: modloader - version: 1.2.3
include $(CLEAR_VARS)
LOCAL_MODULE := modloader
LOCAL_EXPORT_C_INCLUDES := extern/modloader
LOCAL_SRC_FILES := extern/libmodloader.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := sdcwrapper
LOCAL_SRC_FILES += $(call rwildcard,src/**,*.cpp)
LOCAL_SRC_FILES += $(call rwildcard,extern/beatsaber-hook/src/inline-hook,*.cpp)
LOCAL_SRC_FILES += $(call rwildcard,extern/beatsaber-hook/src/inline-hook,*.c)
LOCAL_SHARED_LIBRARIES += android-libsong_data_core_rust
LOCAL_SHARED_LIBRARIES += beatsaber-hook_2_3_0
LOCAL_SHARED_LIBRARIES += modloader
LOCAL_LDLIBS += -llog -lz
LOCAL_CFLAGS += -DID='"SDCWrapper"' -DVERSION='"0.1.0"' -Wno-inaccessible-base -O2
LOCAL_C_INCLUDES += ./include ./src ./extern ./extern/codegen/include ./extern/libil2cpp/il2cpp/libil2cpp ./shared
LOCAL_CPP_FEATURES += rtti exceptions
include $(BUILD_SHARED_LIBRARY)
