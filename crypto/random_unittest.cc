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

const int samples = 1000;
const int bytesSize = 16;
const float threshold = 0.1f;

bool IsEvenlyDistributed() {
  int* zeroes[bytesSize] = {0};
  int* ones[bytesSize] = {0};
  std::string bytes(bytesSize, '\0');
  for (size_t i = 0; i < samples; i++) {
    crypto::RandBytes(base::WriteInto(&bytes, bytesSize), bytesSize);
    for (size_t j = 0; j < bytesSize; j++) {
      if(bytes[j] == 0)
      {
        zeroes[j] = zeroes[j] + 1;
      }
      else if(bytes[j] == 1)
      {
        ones[j] = ones[j] + 1;
      }
      else
      {
        // Something is really broken if this happens.
        return false;
      }
    }
  }
  for (size_t i = 0; i < bytesSize; i++) {
    if(zeroes[i] + ones[i] != samples)
    {
      // Something is wrong if this happens.
      return false;
    }
    float ratio = (float) zeroes[i] / (float) samples;
    if(ratio - treshold > 0.5 || ratio + threshold < 0.5)
    {
      return false;
    }
  }
  return true;
}

TEST(RandBytes, RandBytes) {
  std::string bytes(16, '\0');
  crypto::RandBytes(base::WriteInto(&bytes, bytes.size()), bytes.size());
  EXPECT_TRUE(!IsTrivial(bytes));
}
