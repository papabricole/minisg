HEADERS       = glwidget.h \
                window.h \
                mainwindow.h \
                tiny_obj_loader.h \
    mesh.h

SOURCES       = glwidget.cpp \
                main.cpp \
                window.cpp \
                mainwindow.cpp \
                tiny_obj_loader.cpp \
    mesh.cpp

QT           += widgets

# install
target.path = $$[QT_INSTALL_EXAMPLES]/opengl/hellogl2
INSTALLS += target
