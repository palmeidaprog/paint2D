#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QComboBox>
#include "openglpanel.h"

namespace Ui {
class MainWindow;
}
class OpenGLPanel;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    OpenGLPanel *panel;
    QSpinBox *spinBoxSides;
    QDoubleSpinBox *doubleSpinBoxRadius;
    QComboBox *colorsCombo;

public slots:
    void changeSides(int i);

};

#endif // MAINWINDOW_H
