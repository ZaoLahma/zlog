#include "zlog.h"

#include <chrono>
#include <iomanip>
#include <cstdarg>
#include <iostream>

#ifdef __APPLE__
#include <mach/mach.h>
#include <mach/mach_init.h>
#include <mach/mach_time.h>
#include <mach/clock.h>
#endif

#define ZLOG_TIME_STAMP_CHAR_LENGTH 31u

namespace zlog
{
    ZLog::ZLog() : mLogStream(std::cout)
    {
    }

    ZLog::ZLog(std::ostream& logStream) : mLogStream(logStream)
    {
    }

    ZLog::ZLog(const ZLog& other) : mLogStream(other.mLogStream)
    {
    }

    void ZLog::log(const std::string& logString)
    {
        std::stringstream stringToWriteToLog;

        stringToWriteToLog<<getTimeStamp()<<" ";

        stringToWriteToLog<<logString<<std::endl;

        writeToLogStream(stringToWriteToLog);
    }
    
    std::string ZLog::createString(const char* formatString, ...)
    {
        std::string retVal;

        va_list args;
        va_start(args, formatString);
        
        va_list argsCopy;
        va_copy(argsCopy, args);

        /* Figure out how large a buffer we will need for this log entry */
        const int neededBufSize = vsnprintf(NULL, 0u, formatString, args) + 1;
        va_end(args);

        /* And finally produce the string that we want to return */
        if (0 < neededBufSize)
        {
            char buf[neededBufSize];

            (void) vsnprintf(buf, neededBufSize, formatString, argsCopy);

            retVal = std::string(buf);
        }

        va_end(argsCopy);

        return retVal;
    }

    std::string ZLog::getTimeStamp()
    {
        timespec ts;
        struct tm* currentTime;

        #ifdef WIN32
            time_t now = time(0);
            currentTime = (tm*)malloc(sizeof(tm));
            localtime_s(currentTime, &now);
            ts.tv_nsec = 0;
        #else
        #ifdef __APPLE__
            clock_serv_t cclock;
            mach_timespec_t mts;
            host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
            clock_get_time(cclock, &mts);
            mach_port_deallocate(mach_task_self(), cclock);
            ts.tv_sec = mts.tv_sec;
            ts.tv_nsec = mts.tv_nsec;
        #else
            clock_gettime(CLOCK_REALTIME, &ts);
        #endif
        
        currentTime = localtime(&(ts.tv_sec));
        #endif

        unsigned int year = currentTime->tm_year + 1900;
        unsigned int month = currentTime->tm_mon + 1;
        unsigned int day = currentTime->tm_mday;
        unsigned int hour = currentTime->tm_hour;
        unsigned int minute = currentTime->tm_min;
        unsigned int second = currentTime->tm_sec;
        unsigned int nsecond = ts.tv_nsec;
        
        #ifdef WIN32
            free(currentTime);
        #endif

        /* The buf size of the time stamp is constant */
        char buf[ZLOG_TIME_STAMP_CHAR_LENGTH];
        sprintf(buf, 
                "[%d-%02d-%02d %02d:%02d:%02d.%.9d]",
                year,
                month,
                day,
                hour,
                minute,
                second,
                nsecond);

        return std::string(buf);
    }

    void ZLog::writeToLogStream(const std::stringstream& toWrite)
    {
        std::lock_guard<std::mutex> logStreamLock(mLogStreamMutex);
        mLogStream<<toWrite.str();
    }
}