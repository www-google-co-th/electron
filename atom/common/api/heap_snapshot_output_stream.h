// Copyright (c) 2018 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef ATOM_COMMON_API_HEAP_SNAPSHOT_OUTPUT_STREAM_H_
#define ATOM_COMMON_API_HEAP_SNAPSHOT_OUTPUT_STREAM_H_

#include "base/files/file.h"
#include "base/files/file_path.h"
#include "v8/include/v8-profiler.h"

namespace atom {

class HeapSnapshotOutputStream : public v8::OutputStream {
 public:
  explicit HeapSnapshotOutputStream(base::File* file);

  bool IsComplete() const;

  // v8::OutputStream
  int GetChunkSize() override;
  void EndOfStream() override;
  v8::OutputStream::WriteResult WriteAsciiChunk(char* data, int size) override;

  static base::FilePath GetFilePath();

 private:
  base::File* file_ = nullptr;
  bool is_complete_ = false;
};

}  // namespace atom

#endif  // ATOM_COMMON_API_HEAP_SNAPSHOT_OUTPUT_STREAM_H_
