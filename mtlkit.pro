QT += core
QT -= gui

TARGET = mtlkit
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app
INCLUDEPATH += \
    include/ \
    src/ \
    libs/XmlLoader/

SOURCES += \
    src/main.cpp \
    src/GlContext.cpp \
    src/ShaderProgram.cpp \
    libs/XmlLoader/tinyxml2.cpp \
    libs/XmlLoader/XmlBase.cpp \
    libs/XmlLoader/XmlLoader.cpp \
    libs/XmlLoader/XmlWriter.cpp \
    src/Events.cpp \
    src/Pipeline.cpp \
    src/Pipeline_traits.cpp

HEADERS += \
    include/GlContext.hpp \
    include/GlCore.hpp \
    include/Shader.hpp \
    include/ShaderProgram.hpp \
    libs/XmlLoader/tinyxml2.h \
    libs/XmlLoader/XmlBase.hpp \
    libs/XmlLoader/XmlLoader.hpp \
    libs/XmlLoader/XmlWriter.hpp \
    include/Events.hpp \
    include/Loop.hpp \
    include/Pipeline.hpp \
    include/Pipeline_traits.hpp \
    include/vec.hpp \
    include/keymap.hpp

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra 
LIBS += -lGLEW -lSDL2 -lSDL2_image -lGL

DISTFILES += \
    src/shaders/blinn_phong.glsl \
    assets/xml/PipelineConfig.xml
