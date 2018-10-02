// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "crypto/random.h"

#include <stddef.h>

#include <string>

#include "base/strings/string_util.h"
#include "testing/gtest/include/gtest/gtest.h"

// Basic functionality tests. Does NOT test the security of the random data.

// Ensures we don't have all trivial data, i.e. that the data is indeed random.
// Currently, that means the bytes cannot be all the same (e.g. all zeros).
bool IsTrivial(const std::string& bytes) {
  for (size_t i = 0; i < bytes.size(); i++) {
    if (bytes[i] != bytes[0]) {
      return false;
    }
  }
  return true;
}

bool IsEqual(const std::string& bytes1, const std::string& bytes2) {
  if(bytes1.size() != bytes2.size())
  {
    //Log size mismatch error here, this should not happen.
    return false;
  }
  for (size_t i = 0; i < bytes1.size(); i++) {
    if (bytes1[i] != bytes2[0]) {
      return false;
    }
  }
  return true;
}

TEST(RandBytes, RandBytes) {
  std::string bytes1(16, '\0');
  std::string bytes2(16, '\0');
  crypto::RandBytes(base::WriteInto(&bytes1, bytes1.size()), bytes1.size());
  crypto::RandBytes(base::WriteInto(&bytes2, bytes2.size()), bytes2.size());
  EXPECT_TRUE(!IsTrivial(bytes1));
  EXPECT_TRUE(!IsEqual(bytes1, bytes2));
}
