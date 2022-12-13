#include "zlog.h"
#include <chrono>

#include <sstream>
#include <iomanip>
#include <cstdarg>

#ifdef __APPLE__
#include <mach/mach.h>
#include <mach/mach_init.h>
#include <mach/mach_time.h>
#include <mach/clock.h>
#endif

namespace zlog
{
    ZLog::ZLog() : mLogStream(std::cout), mContext("")
    {
    }

    ZLog::ZLog(const std::string& context) : mLogStream(std::cout), mContext(context)
    {
    }

    ZLog::ZLog(std::ostream& logStream) : mLogStream(logStream), mContext("")
    {
    }

    ZLog::ZLog(const std::string& context, std::ostream& logStream) : mLogStream(logStream), mContext(context)
    {
    }

    ZLog::ZLog(const ZLog& other) : mLogStream(other.mLogStream), mContext(other.mContext)
    {
        
    }

    void ZLog::log(const char* formatString, ...)
    {
        std::stringstream stringToPrint;

        stringToPrint<<getTimeStamp()<<" ";

        if ("" != mContext)
        {
            stringToPrint<<mContext<<" - ";
        }

        char buf[2048];

        va_list args;
        va_start(args, formatString);
        vsprintf(buf, formatString, args);
        va_end (args);

        stringToPrint<<std::string(buf)<<std::endl;

        mLogStream<<stringToPrint.str();
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

        const uint8_t buf_size = 31;
        char buf[buf_size];
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
}