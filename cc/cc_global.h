#ifndef CC_GLOBAL_H
#define CC_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(CC_LIBRARY)
#  define CC_EXPORT Q_DECL_EXPORT
#else
#  define CC_EXPORT Q_DECL_IMPORT
#endif

#endif // CC_GLOBAL_H
