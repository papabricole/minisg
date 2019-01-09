#include "glwidget.h"
#include "window.h"
#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QKeyEvent>

Window::Window(MainWindow* mw)
  : mainWindow(mw)
{
    setFocusPolicy(Qt::StrongFocus);

    glWidget = new GLWidget;

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(glWidget);

    setLayout(mainLayout);

    setWindowTitle(tr("Hello GL"));
}

void
Window::keyPressEvent(QKeyEvent* e)
{
    if (e->key() == Qt::Key_Space) {
        glWidget->viewAll();
    } else
        QWidget::keyPressEvent(e);
}
