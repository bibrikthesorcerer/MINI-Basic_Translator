QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    LexBlock/Determ_analizer.cpp \
    LexBlock/State.cpp \
    LexBlock/lex_block.cpp \
    SynthBlock/CF_grammar.cpp \
    SynthBlock/symbol.cpp \
    SynthBlock/synth_block.cpp \
    main.cpp \
    mdidocument.cpp \
    translator.cpp

HEADERS += \
    LexBlock/Determ_analizer.h \
    LexBlock/State.h \
    LexBlock/lex_block.h \
    SynthBlock/CF_grammar.h \
    SynthBlock/symbol.h \
    SynthBlock/synth_block.h \
    mdidocument.h \
    translator.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc

OTHERFILES += \
    grammar.txt \
    input.txt

DISTFILES += \
    ../build-Translator-Mini-Basic-Desktop_Qt_6_4_1_MinGW_64_bit-Debug/grammar.txt
