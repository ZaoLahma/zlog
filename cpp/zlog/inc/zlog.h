#pragma once

#include <sstream>
#include <string>
#include <mutex>
#include <cstdint>

namespace zlog
{
    class ZLog
    {
        public:
        ZLog();
        ZLog(std::ostream& logStream);
        ZLog(const ZLog& logStream);

        template<typename ... Args>
        void log(const char* formatString, Args&&... args)
        {
            log(createString(formatString, std::forward<Args>(args)...));
        }

        template<typename ... Args>
        void logExtra(const std::string& extra, const char* formatString, Args&&... args)
        {
            std::stringstream stringToWriteToLog;

            stringToWriteToLog<<extra<<" "<<createString(formatString, std::forward<Args>(args)...);
            
            log(stringToWriteToLog.str());
        } 

        std::string createString(const char* formatString, ...); 

        protected:
        void log(const std::string& logString);   
        std::string getTimeStamp();
        void writeToLogStream(const std::stringstream& toWrite);

        private:
        std::mutex mLogStreamMutex;
        std::ostream& mLogStream;
    };
}