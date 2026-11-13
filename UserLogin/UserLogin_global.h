#ifndef USERLOGIN_GLOBAL_H
#define USERLOGIN_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(USERLOGIN_LIBRARY)
#  define USERLOGIN_EXPORT Q_DECL_EXPORT
#else
#  define USERLOGIN_EXPORT Q_DECL_IMPORT
#endif

#endif // USERLOGIN_GLOBAL_H
