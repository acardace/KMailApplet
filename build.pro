TARGET = KMailApplet
HEADERS += include/*.hpp
SOURCES += src/main.cpp
SOURCES += src/cmdLineParser/*.cpp
SOURCES += src/mailWatcher/*.cpp

INCLUDEPATH += include/
QMAKE_CXXFLAGS += --std=c++11 -Wno-missing-field-initializers
LIBS += -lboost_system -lboost_filesystem

QT += core
QT += widgets
QT += gui
