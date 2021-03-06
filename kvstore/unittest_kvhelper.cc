#include "cchash.h"
#include "kvhelper.h"
#include <gtest/gtest.h>
#include <iostream>
#include <string>

ConcurrentHashTable<std::string, std::string> hs;
// test the put method naively
TEST(test, put) {
  auto i = helper::Put(hs, "test1", "val1");
  ASSERT_EQ(hs.GetValue("test1"), "val1");
  ASSERT_EQ(0, i);
}
// assert that put method will not update value
TEST(test, put2) {
  auto i = helper::Put(hs, "test1", "val2");
  ASSERT_EQ(0, i);
  ASSERT_EQ(hs.GetValue("test1"), "val2");
  i = helper::Put(hs, "test2", "val2");
  ASSERT_EQ(hs.GetValue("test2"), "val2");
  ASSERT_EQ(0, i);
}
// Test whether get method which return a value works
TEST(test, get) {
  auto str = helper::Get(hs, "test2");
  ASSERT_EQ("val2", str);
  ASSERT_EQ(str, hs.GetValue("test2"));
}
// Test whether we can delete a key
TEST(test, deletekey) {
  auto i = helper::Delete(hs, "test2");
  ASSERT_EQ(0, i);
  i = helper::Delete(hs, "test2");
  ASSERT_EQ(-1, i);
  ASSERT_EQ(false, hs.Has("test2"));
}
int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
