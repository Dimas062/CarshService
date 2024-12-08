#ifndef LICENCE_GLOBAL_H
#define LICENCE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LICENCE_LIBRARY)
#  define LICENCESHARED_EXPORT Q_DECL_EXPORT
#else
#  define LICENCESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif
