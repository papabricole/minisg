#include "mainwindow.h"
#include "glwidget.h"
#include <QMenuBar>
#include <QMenu>
#include <QKeyEvent>

MainWindow::MainWindow()
{
    QMenuBar* menuBar = new QMenuBar;

    setMenuBar(menuBar);

    glWidget = new GLWidget;

    setCentralWidget(glWidget);
}

void
MainWindow::keyPressEvent(QKeyEvent* e)
{
    if (e->key() == Qt::Key_Space) {
        glWidget->viewAll();
    } else
        QWidget::keyPressEvent(e);
}
