#ifndef LANGUAGE_GLOBAL_H
#define LANGUAGE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LANGUAGE_LIBRARY)
#  define LANGUAGE_EXPORT Q_DECL_EXPORT
#else
#  define LANGUAGE_EXPORT Q_DECL_IMPORT
#endif

#endif // LANGUAGE_GLOBAL_H
