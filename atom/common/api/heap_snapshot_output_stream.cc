// Copyright (c) 2018 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "atom/common/api/heap_snapshot_output_stream.h"

#include "base/path_service.h"
#include "base/strings/stringprintf.h"
#include "brightray/browser/brightray_paths.h"
#include "uv.h"  // NOLINT(build/include)

namespace atom {

HeapSnapshotOutputStream::HeapSnapshotOutputStream(base::File* file)
    : file_(file) {
  DCHECK(file_);
}

bool HeapSnapshotOutputStream::IsComplete() const {
  return is_complete_;
}

int HeapSnapshotOutputStream::GetChunkSize() {
  return 65536;
}

void HeapSnapshotOutputStream::EndOfStream() {
  is_complete_ = true;
}

v8::OutputStream::WriteResult HeapSnapshotOutputStream::WriteAsciiChunk(
    char* data,
    int size) {
  auto bytes_written = file_->WriteAtCurrentPos(data, size);
  return bytes_written == size ? kContinue : kAbort;
}

// static
base::FilePath HeapSnapshotOutputStream::GetFilePath() {
  base::FilePath user_data;
  if (!PathService::Get(brightray::DIR_USER_DATA, &user_data))
    return base::FilePath();

  auto now = uv_hrtime();
  auto sec = static_cast<unsigned int>(now / 1000000);
  auto usec = static_cast<unsigned int>(now % 1000000);
  auto filename = base::StringPrintf("heapdump-%u-%u.heapsnapshot", sec, usec);

  return user_data.AppendASCII(filename.c_str());
}

}  // namespace atom
