// SPDX-FileCopyrightText: Copyright 2026 shadPS4 Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include "common/types.h"

namespace Core::Loader {
class SymbolsResolver;
}

namespace Libraries::VideoRecording {

struct OrbisVideoRecordingParam2 {
    u64 size;
    u64 affinity_mask;
    s32 thread_priority;
    s32 ring_sec;
};

struct OrbisVideoRecordingInfoUserMeta {
    u64 size;
    s32 flags;
    char name[32];
    char data[128];
};

struct OrbisVideoRecordingInfoGuardArea {
    float x1, y1;
    float x2, y2;
};

enum OrbisVideoRecordingStatus {
    None = 0,
    Running = 1,
    Paused = 2,
};

enum OrbisVideoRecordingInfo {
    Subtitle = 0x2,
    Description = 0x6,
    Comments = 0x7,
    Keywords = 0x8,
    Chapter = 0xd,
    Copyright = 0xa01,
    PermisssionLevel = 0xa007,
    GuardArea = 0xa008,
    UserMeta = 0xa009,
};

enum OrbisVideoRecordingChapter {
    Change = 0,
    Prohibit = 1,
};

enum OrbisVideoRecordingUserMeta {
    Constant = 1,
    Timeline = 2,
    Variable = 3,
    Debug = 0x8000,
};

constexpr s32 ORBIS_VIDEO_RECORDING_MAX_MEM_SIZE = 2048 * 1024; // 2MiB

s32 PS4_SYSV_ABI sceVideoRecordingSetInfo(OrbisVideoRecordingInfo set_info, const void* info,
                                           u64 info_len);
s32 PS4_SYSV_ABI sceVideoRecordingGetStatus();
s32 PS4_SYSV_ABI sceVideoRecordingQueryMemSize2(const OrbisVideoRecordingParam2* param);
s32 PS4_SYSV_ABI sceVideoRecordingOpen2(const char* path, const OrbisVideoRecordingParam2* param,
                                       void* heap, s32 heap_size);
s32 PS4_SYSV_ABI sceVideoRecordingStart();
s32 PS4_SYSV_ABI sceVideoRecordingStop();
s32 PS4_SYSV_ABI sceVideoRecordingClose(s32 discard);

void RegisterLib(Core::Loader::SymbolsResolver* sym);
} // namespace Libraries::VideoRecording