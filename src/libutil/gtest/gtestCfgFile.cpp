#include "gtest/gtest.h"
#include "CfgFile.h"

TEST(CfgFileTest, WriteLoadAndGetValue) {
    RecordProperty("Description", "Test writing, loading and getting values from CfgFile");
    platform::CfgFile cfg;
    cfg.setValue("key1", "value1");
    cfg.setValue("key2", "value2");
    cfg.setValue("key3", "value3");
    bool written = cfg.write("test.cfg");
    EXPECT_TRUE(written);

    // now try the written file
    platform::CfgFile cfg2;
    bool loaded = cfg2.load("test.cfg");
    EXPECT_TRUE(loaded);
    EXPECT_EQ(cfg2.getValue("key1"), "value1");
    EXPECT_EQ(cfg2.getValue("key2"), "value2");
    EXPECT_EQ(cfg2.getValue("key3"), "value3");
    EXPECT_EQ(cfg2.getValue("nonexistent", "default"), "default");

    // test getAllKeys
    std::list<std::string> keys = cfg2.getAllKeys();
    EXPECT_EQ(keys.size(), 3);
    EXPECT_EQ(keys.front(), "key3");
    EXPECT_EQ(keys.back(), "key1");

    // delete the file after test
    std::remove("test.cfg");
}
