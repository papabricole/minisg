#pragma once

#include <QWidget>

QT_BEGIN_NAMESPACE
class QSlider;
class QPushButton;
QT_END_NAMESPACE

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
    QSlider* createSlider();

    GLWidget* glWidget;
    QSlider* xSlider;
    QSlider* ySlider;
    QSlider* zSlider;
    MainWindow* mainWindow;
};
