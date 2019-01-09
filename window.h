#pragma once

#include <QWidget>

class GLWidget;
class MainWindow;

class Window : public QWidget
{
    Q_OBJECT

  public:
    Window(MainWindow* mw);

  protected:
    void keyPressEvent(QKeyEvent* event) override;

  private:
    GLWidget* glWidget;
    MainWindow* mainWindow;
};
