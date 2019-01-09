HEADERS       = glwidget.h \
                mainwindow.h \
                tiny_obj_loader.h \
                mesh.h \
                box3d.h \
                camera.h \
    meshloader.h

SOURCES       = glwidget.cpp \
                main.cpp \
                mainwindow.cpp \
                tiny_obj_loader.cpp \
                mesh.cpp \
                camera.cpp \
    meshloader.cpp

QT           += widgets
CONFIG       -= app_bundle

RESOURCES += \
    resources.qrc

