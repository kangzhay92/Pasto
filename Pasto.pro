QT += core network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Pasto
TEMPLATE = app

HEADERS += \
    pasto.h \
    editor.h

SOURCES += \
    pasto.cpp \
    main.cpp \
    editor.cpp
