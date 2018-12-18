HEADERS       = glwidget.h \
                window.h \
                mainwindow.h \
                tiny_obj_loader.h \
                mesh.h \
                box3d.h \
                camera.h

SOURCES       = glwidget.cpp \
                main.cpp \
                window.cpp \
                mainwindow.cpp \
                tiny_obj_loader.cpp \
                mesh.cpp \
                camera.cpp

QT           += widgets
CONFIG       -= app_bundle

RESOURCES += \
    resources.qrc

