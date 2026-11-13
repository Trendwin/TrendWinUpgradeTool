#ifndef LOGGERMANAGER_GLOBAL_H
#define LOGGERMANAGER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LOGGER_LIBRARY)
#  define LOGGER_EXPORT Q_DECL_EXPORT
#else
#  define LOGGER_EXPORT Q_DECL_IMPORT
#endif

#endif // LOGGERMANAGER_GLOBAL_H
