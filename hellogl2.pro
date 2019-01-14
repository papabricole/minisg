HEADERS       = glwidget.h \
                mainwindow.h \
                tiny_obj_loader.h \
                nodes/mesh.h \
                box3d.h \
                nodes/camera.h \
    meshloader.h \
    nodes/node.h \
    nodes/group.h \
    refptr.h \
    action.h \
    renderaction.h \
    nodes/base.h \
    nodes/transform.h \
    elements/element.h \
    elements/cameraelement.h \
    elements/meshelement.h \
    elements/transformelement.h \
    state.h

SOURCES       = glwidget.cpp \
                main.cpp \
                mainwindow.cpp \
                tiny_obj_loader.cpp \
                nodes/mesh.cpp \
                nodes/camera.cpp \
    meshloader.cpp \
    nodes/node.cpp \
    nodes/group.cpp \
    action.cpp \
    renderaction.cpp \
    nodes/base.cpp \
    nodes/transform.cpp \
    elements/element.cpp \
    elements/cameraelement.cpp \
    elements/meshelement.cpp \
    elements/transformelement.cpp \
    state.cpp

QT           += widgets
CONFIG       -= app_bundle

RESOURCES += \
    resources.qrc

