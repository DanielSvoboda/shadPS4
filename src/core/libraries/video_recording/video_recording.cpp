// SPDX-FileCopyrightText: Copyright 2026 shadPS4 Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#include "common/logging/log.h"
#include "core/libraries/libs.h"
#include "core/libraries/video_recording/video_recording.h"
#include "core/libraries/video_recording/video_recording_error.h"

namespace Libraries::VideoRecording {

s32 PS4_SYSV_ABI sceVideoRecordingSetInfo(OrbisVideoRecordingInfo set_info, const void* info,
                                          u64 info_len) {
    LOG_ERROR(Lib_VideoRecording, "(STUBBED) called, set_info = {:#x}, info_len = {:#x}",
              static_cast<u32>(set_info), info_len);
    if (set_info < OrbisVideoRecordingInfo::Subtitle ||
        (set_info > OrbisVideoRecordingInfo::Subtitle &&
         set_info < OrbisVideoRecordingInfo::Description) ||
        (set_info > OrbisVideoRecordingInfo::Keywords &&
         set_info < OrbisVideoRecordingInfo::Chapter) ||
        (set_info > OrbisVideoRecordingInfo::Chapter &&
         set_info < OrbisVideoRecordingInfo::Copyright) ||
        (set_info > OrbisVideoRecordingInfo::Chapter &&
         set_info < OrbisVideoRecordingInfo::PermisssionLevel) ||
        set_info > OrbisVideoRecordingInfo::UserMeta) {
        return ORBIS_VIDEO_RECORDING_ERROR_INVALID_VALUE;
    }

    // The library seems to rely on libSceAvcap to provide errors for other parameters.
    if (!info) {
        return ORBIS_VIDEO_RECORDING_ERROR_INVALID_VALUE;
    }
    return ORBIS_OK;
}

s32 PS4_SYSV_ABI sceVideoRecordingGetStatus() {
    LOG_TRACE(Lib_VideoRecording, "called");
    return OrbisVideoRecordingStatus::None;
}

s32 PS4_SYSV_ABI sceVideoRecordingQueryMemSize2(const OrbisVideoRecordingParam2* param) {
    LOG_TRACE(Lib_VideoRecording, "called");
    if (param == nullptr) {
        return ORBIS_VIDEO_RECORDING_ERROR_INVALID_VALUE;
    }
    return ORBIS_VIDEO_RECORDING_MAX_MEM_SIZE;
}

s32 PS4_SYSV_ABI sceVideoRecordingOpen2(const char* path, const OrbisVideoRecordingParam2* param,
                                       void* heap, s32 heap_size) {
    LOG_TRACE(Lib_VideoRecording, "called");
    if (path == nullptr || param == nullptr) {
        return ORBIS_VIDEO_RECORDING_ERROR_INVALID_VALUE;
    }
    return ORBIS_VIDEO_RECORDING_ERROR_INVALID_STATE;
}

s32 PS4_SYSV_ABI sceVideoRecordingStart() {
    LOG_TRACE(Lib_VideoRecording, "called");
    return ORBIS_VIDEO_RECORDING_ERROR_INVALID_STATE;
}

s32 PS4_SYSV_ABI sceVideoRecordingStop() {
    LOG_TRACE(Lib_VideoRecording, "called");
    return ORBIS_VIDEO_RECORDING_ERROR_INVALID_STATE;
}

s32 PS4_SYSV_ABI sceVideoRecordingClose(s32 discard) {
    LOG_TRACE(Lib_VideoRecording, "called");
    return ORBIS_OK;
}

void RegisterLib(Core::Loader::SymbolsResolver* sym) {
    LIB_FUNCTION("Fc8qxlKINYQ", "libSceVideoRecording", 1, "libSceVideoRecording",
                 sceVideoRecordingSetInfo);
    LIB_FUNCTION("fZJQzFK4Gv4", "libSceVideoRecording", 1, "libSceVideoRecording",
                 sceVideoRecordingGetStatus);
    LIB_FUNCTION("bGYkY6q3bIw", "libSceVideoRecording", 1, "libSceVideoRecording",
                 sceVideoRecordingQueryMemSize2);
    LIB_FUNCTION("s28dalBwp2g", "libSceVideoRecording", 1, "libSceVideoRecording",
                 sceVideoRecordingOpen2);
    LIB_FUNCTION("tWoe9IlGAhs", "libSceVideoRecording", 1, "libSceVideoRecording",
                 sceVideoRecordingStart);
    LIB_FUNCTION("OOFxrMY+mfI", "libSceVideoRecording", 1, "libSceVideoRecording",
                 sceVideoRecordingStop);
    LIB_FUNCTION("KHvkPQJDMLk", "libSceVideoRecording", 1, "libSceVideoRecording",
                 sceVideoRecordingClose);
}
} // namespace Libraries::VideoRecording