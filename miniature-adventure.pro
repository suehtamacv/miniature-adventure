TEMPLATE = app

CONFIG += console c++11
CONFIG -= app_bundle qt

QMAKE_CXXFLAGS += -std=c++11 -fopenmp
QMAKE_LFLAGS += -std=c++11 -fopenmp
QMAKE_CXXFLAGS_RELEASE -= -O
QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE *= -O3

SOURCES += commonUtil.cpp \
           detect.cpp \
           Detector.cpp \
           detectUtil.cpp \
           io_png.c

HEADERS += commonUtil.h \
           connected.h \
           Detector.h \
           detectUtil.h \
           io_png.h

LIBS += -lboost_system -lboost_program_options -larmadillo -lpng

INCLUDEPATH += /usr/include/eigen3
