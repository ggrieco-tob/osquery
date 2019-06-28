/**
 *  Copyright (c) 2014-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed in accordance with the terms specified in
 *  the LICENSE file found in the root directory of this source tree.
 */

//#include <gtest/gtest.h>
#include <deepstate/DeepState.hpp>
#include <osquery/utils/base64.h>

namespace osquery {

class Base64Tests : public deepstate::Test {
};


TEST_F(Base64Tests, test_base64) {

  deepstate::ForAll<std::string>([] (const std::string &unencoded) {
  auto encoded = base64::encode(unencoded);
  //ASSERT_L(encoded.size(), 0U);

  auto unencoded2 = base64::decode(encoded);
  ASSERT_EQ(unencoded, unencoded2);
  });
}

} // namespace osquery

