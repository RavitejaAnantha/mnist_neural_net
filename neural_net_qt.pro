# Created by and for Qt Creator. This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

#TARGET = neural_net_qt

HEADERS = \
   $$PWD/network/Network.h \
   $$PWD/network/Nodes.h \
   $$PWD/network/NodesLayer.h \
   $$PWD/utils/MathNN.h \
   $$PWD/utils/Mnist.h \
   $$PWD/utils/MnistReader.h

SOURCES = \
   $$PWD/utils/MnistReader.cpp \
   $$PWD/network/Network.cpp \
   $$PWD/network/Nodes.cpp \
   $$PWD/network/NodesLayer.cpp \
   $$PWD/utils/MathNN.cpp \
   $$PWD/main.cpp \
   $$PWD/utils/Mnist.cpp

INCLUDEPATH = \
    $$PWD/network/headers \
    $$PWD/utils \
    $$PWD/assets

#DEFINES =

copydata.commands = $(COPY_DIR) $$PWD/assets $$OUT_PWD
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata
