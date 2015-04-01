TEMPLATE = lib

HEADERS *= BaseStringBuilder.h \
           BasicStringBuilder.h \
		   QStringBuilder.h

include(defines.pri)
include(../common.pri)

CONFIG *= static
