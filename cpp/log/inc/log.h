#pragma once

#include <iostream>

namespace zlog
{
    class ZLog
    {
        public:
        ZLog();
        ZLog(std::ostream& logStream);

        void log(const char* formatString, ...);

        protected:
        std::string getTimeStamp();

        private:
        std::ostream& mLogStream;
    };
}