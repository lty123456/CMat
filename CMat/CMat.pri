CONFIG += c++17 c++20

HEADERS += \
    $$PWD/cmatarray.h \
    $$PWD/cmatarraybase.h \
    $$PWD/cmatcomplexarray.h \
    $$PWD/cmatdata.h \
    $$PWD/cmatdata_arithmetic.h \
    $$PWD/cmatdata_cell.h \
    $$PWD/cmatdatabase.h \
    $$PWD/cmatdatadeclare.h \
    $$PWD/cmatdatatype.h \
    $$PWD/cmatdatatype_arithmetic.h \
    $$PWD/cmatdatatype_cell.h \
    $$PWD/cmatexception.h \
    $$PWD/cmatfile.h \
    $$PWD/cmatvariable.h \
    $$PWD/test.h

SOURCES += \
    $$PWD/cmatdata.cpp \
    $$PWD/cmatdatabase.cpp \
    $$PWD/cmatdatatype.cpp \
    $$PWD/cmatdatatype_cell.cpp \
    $$PWD/cmatexception.cpp \
    $$PWD/cmatfile.cpp \
    $$PWD/cmatvariable.cpp \
    $$PWD/test.cpp

INCLUDEPATH += $$PWD/extern/include
LIBS += $$PWD/extern/lib/win64/mingw64/libmat.lib
LIBS += $$PWD/extern/lib/win64/mingw64/libmx.lib

DISTFILES +=
