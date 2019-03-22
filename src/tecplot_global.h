#ifndef TECPLOT_GLOBAL_H
#define TECPLOT_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(TECPLOT_LIBRARY)
#  define TECPLOTSHARED_EXPORT Q_DECL_EXPORT
#else
#  define TECPLOTSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // TECPLOT_GLOBAL_H
