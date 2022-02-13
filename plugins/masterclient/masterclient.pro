TEMPLATE        = lib
CONFIG         += plugin
QT             += network
INCLUDEPATH    += ../../edgeworth/interfaces
HEADERS         = masterclient.hpp
SOURCES         = masterclient.cpp
CONFIG -= \
        copy_dir_files \
        debug_and_release \
        debug_and_release_target
CONFIG += release

DESTDIR = $$PWD/../../bin/plugins
