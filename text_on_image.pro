TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

HEADERS += \
    rdi_text_on_image.h \
    catch.hpp \
    stb_image.h \
    stb_image_write.h
