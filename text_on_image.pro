TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

HEADERS += \
    rdi_text_on_image.h \
    catch.hpp \
    stb_image_resize.h \
    stb_image.h \
    stb_image_write.h
