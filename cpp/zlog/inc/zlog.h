#pragma once

#include <iostream>
#include <stdio.h>
#include <mutex>

namespace zlog
{
    class ZLog
    {
        public:
        ZLog();
        ZLog(std::ostream& logStream);
        ZLog(const ZLog& logStream);

        void log(const char* formatString, ...);
        void logExtra(const std::string& extra, const char* formatString, ...);

        protected:
        std::string getTimeStamp();
        void writeToLogStream(const std::stringstream& toWrite);

        private:
        std::mutex mLogStreamMutex;
        std::ostream& mLogStream;
    };
}