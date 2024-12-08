#pragma once
#include <QtCore/QtGlobal>

#if defined(INTERACTION_PROTOCOL_LIB)
#define INTERACTION_PROTOCOL_API Q_DECL_EXPORT
#else
#define INTERACTION_PROTOCOL_API Q_DECL_IMPORT
#endif

