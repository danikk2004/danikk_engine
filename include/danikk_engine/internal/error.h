#pragma once

#include <danikk_engine/localization.h>

namespace danikk_engine
{
	void fatalError();

    template<class ...args_t> inline static void formatFatalError(const char* format, const args_t&... args)
    {
    	String fatalErrorBuffer;
    	danikk_framework::format(fatalErrorBuffer, format, args...);
    	logFatal(fatalErrorBuffer);
    	fatalError();
    }


    template<class ...args_t> inline static void fatalError(const char* message)
    {
    	logFatal(message);
    	fatalError();
    }
}
