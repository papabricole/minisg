HEADERS       = glwidget.h \
                mainwindow.h \
                tiny_obj_loader.h \
                mesh.h \
                box3d.h \
                camera.h \
    meshloader.h \
    node.h \
    group.h \
    refptr.h \
    action.h \
    renderaction.h \
    base.h \
    transform.h \
    element.h \
    cameraelement.h \
    meshelement.h \
    transformelement.h

SOURCES       = glwidget.cpp \
                main.cpp \
                mainwindow.cpp \
                tiny_obj_loader.cpp \
                mesh.cpp \
                camera.cpp \
    meshloader.cpp \
    node.cpp \
    group.cpp \
    action.cpp \
    renderaction.cpp \
    base.cpp \
    transform.cpp \
    element.cpp \
    cameraelement.cpp \
    meshelement.cpp \
    transformelement.cpp

QT           += widgets
CONFIG       -= app_bundle

RESOURCES += \
    resources.qrc

