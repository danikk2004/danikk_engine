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

    template<class ...args_t> inline static void formatFatalError(const String& format, const args_t&... args)
    {
    	formatFatalError(format.c_string(), args...);
    }

    template<class out_t> static inline void appendFailError(out_t& out, const char* localizationKey)
    {
    	formatAppend(out, "% %", localization("failed"), localization(localizationKey));
    }

    inline void fatalFail(const char* localizationKey)
    {
    	String log_buffer;
    	appendFailError(log_buffer, localizationKey);
    	logFatal(log_buffer);
    	fatalError();
    }

    template<class out_t> static inline void appendMismatchError(out_t& out, const char* localizationKey)
    {
    	formatAppend(out, "% %.", localization("mismatch"), localization(localizationKey));
    }

    template<class out_t, class var_t> static inline void appendOutputInfo(out_t& out, const char* localizationKey, const var_t& var)
    {
    	StringBuffer<64> fullLocalizationKey;
    	format(fullLocalizationKey, "info_out/%", localizationKey);
    	formatAppend(out, " % : %.", localization(fullLocalizationKey.c_string()), var);
    }
}
