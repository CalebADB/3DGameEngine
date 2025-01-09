#ifndef _UTILITIESDEBUG_H
#define _UTILITIESDEBUG_H

namespace ge
{
	namespace debug
	{
        enum EOutputType
        {
            Initialize,
            Update,
            Physics,
            Render,
            Always // Used primarily for ERROR calls
        };
        static bool PRINTDEBUGINITIALIZE = false;
        static bool PRINTDEBUGUPDATE = false; 
        static bool PRINTDEBUGPHYSICS = false;
        static bool PRINTDEBUGRENDER = false;
        static bool PRINTDEBUGALWAYS = true;

        template<typename... Args>
        void Output(EOutputType Type, const char* inString, Args... args)
        {
            switch (Type)
            {
            case Initialize:
                if (!PRINTDEBUGINITIALIZE) return;
                break;
            case Update:
                if (!PRINTDEBUGUPDATE) return;
                break;
            case Physics:
                if (!PRINTDEBUGPHYSICS) return;
                break;
            case Render:
                if (!PRINTDEBUGRENDER) return;
                break;
            case Always:
                if (!PRINTDEBUGALWAYS) return;
                break;
            }

            char buffer[100];
            int x = 10;
            snprintf(buffer, sizeof(buffer), inString, args...);

            // Convert to std::wstring
            std::wstring wideString;
            for (size_t i = 0; i < std::strlen(buffer); ++i) {
                wideString += static_cast<wchar_t>(buffer[i]);
            }

            wideString += static_cast<wchar_t>('\n');

            // Use OutputDebugStringW for wide strings
            OutputDebugStringW(wideString.c_str());
        }
    }
};

#endif //_UTILITIESDEBUG_H
