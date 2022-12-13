#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <fstream>
#include <vector>
#include <string>
#include <string_view>

#include "zlog.h"

class LogTest : public ::testing::Test
{
    public:

    protected:

    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
};

TEST_F(LogTest, TestDefaultCoutLog)
{
    zlog::ZLog log;

    log.log("Test integer %i", 1234);
}

TEST_F(LogTest, TestDefaultCoutLogWithContext)
{
    zlog::ZLog log("MyContext");

    log.log("Test integer %i", 1234);
}

TEST_F(LogTest, TestFileLog)
{
    std::ofstream logFileOutStream("file.log", std::ofstream::out);

    zlog::ZLog log(logFileOutStream);

    log.log("Test integer %i", 999111);
    log.log("Test String %s", "TestString");

    logFileOutStream.flush();

    std::ifstream logFileInStream("file.log");

    std::vector<std::string> fileLines;

    std::string line;
    while (std::getline(logFileInStream, line))
    {
        fileLines.push_back(line);
    }

    ASSERT_EQ(2, fileLines.size());
    ASSERT_EQ(true, std::string_view(fileLines[0]).ends_with("999111"));
    ASSERT_EQ(true, std::string_view(fileLines[1]).ends_with("TestString"));


    std::remove("file.log");
}