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
           train_neural.cpp \
           io_png.c

HEADERS += commonUtil.h \
           connected.h \
           Detector.h \
           detectUtil.h \
           TrainExamples.h \
           io_png.h \
    train_neural.h

OTHER_FILES += .astylerc

INSTALL_HEITOR.path = $$OUT_PWD/
INSTALL_HEITOR.files = test.png photoData.dat

INSTALLS += INSTALL_HEITOR

LIBS += -lboost_system -lboost_program_options -lpng -lopencv_core -lopencv_highgui -lopencv_imgproc -larmadillo -lfann
