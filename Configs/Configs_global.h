#ifndef CONFIGS_GLOBAL_H
#define CONFIGS_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(CONFIGS_LIBRARY)
#  define CONFIGS_EXPORT Q_DECL_EXPORT
#else
#  define CONFIGS_EXPORT Q_DECL_IMPORT
#endif

#endif // CONFIGS_GLOBAL_H
