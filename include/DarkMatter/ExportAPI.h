#ifndef _DM_EXPORT_API_H_INCLUDED_
#define _DM_EXPORT_API_H_INCLUDED_

#ifdef WIN32
   #ifdef DM_EXPORT_SYMBOLS
      #define DM_API __declspec(dllexport)
   #else
      #define DM_API __declspec(dllimport)
   #endif
#else
   #define DM_API
#endif

#endif