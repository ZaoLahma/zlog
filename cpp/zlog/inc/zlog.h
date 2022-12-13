#pragma once

#include <iostream>

namespace zlog
{
    class ZLog
    {
        public:
        ZLog();
        ZLog(const std::string& context);
        ZLog(std::ostream& logStream);
        ZLog(const std::string& context, std::ostream& logStream);
        ZLog(const ZLog& logStream);

        void log(const char* formatString, ...);

        protected:
        std::string getTimeStamp();

        private:
        std::ostream& mLogStream;
        const std::string& mContext;
    };
}