

// .NAME __Zhi_Huang_MypluginName_Export - manage Windows system differences
// .SECTION Description
// The __Zhi_Huang_MypluginName_Export captures some system differences between Unix
// and Windows operating systems. 

#ifndef __Zhi_Huang_MypluginName_Export_h
#define __Zhi_Huang_MypluginName_Export_h

#include <QtCore/qglobal.h>

#if defined(Q_OS_WIN) || defined(Q_OS_SYMBIAN)
#  if defined(Zhi_Huang_MypluginName_EXPORTS)
#    define Zhi_Huang_MypluginName_EXPORT Q_DECL_EXPORT
#  else
#    define Zhi_Huang_MypluginName_EXPORT Q_DECL_IMPORT
#  endif
#endif

#if !defined(Zhi_Huang_MypluginName_EXPORT)
//#  if defined(CTK_SHARED)
#    define Zhi_Huang_MypluginName_EXPORT Q_DECL_EXPORT
//#  else
//#    define Zhi_Huang_MypluginName_EXPORT
//#  endif
#endif

#endif

