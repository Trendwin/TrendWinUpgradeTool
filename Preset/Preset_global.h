#ifndef PRESET_GLOBAL_H
#define PRESET_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(PRESET_LIBRARY)
#  define PRESET_EXPORT Q_DECL_EXPORT
#else
#  define PRESET_EXPORT Q_DECL_IMPORT
#endif

#endif // PRESET_GLOBAL_H
