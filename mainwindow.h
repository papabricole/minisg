#pragma once

#include <QMainWindow>

class GLWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    MainWindow();

  protected:
    void keyPressEvent(QKeyEvent* event) override;

  private:
    GLWidget* glWidget;
};
