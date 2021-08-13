TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    collisions.cpp \
    engine.cpp \
    spring.cpp

HEADERS += \
    sphere.h \
    triangle.h \
    plane.h \
    collisions.h \
    obj.h \
    engine.h \
    spring.h
