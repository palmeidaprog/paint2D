#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QComboBox>
#include <QToolButton>
#include <QColorDialog>
#include <QSlider>
#include <QDial>
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
    QToolButton *colorBtn;
    QSlider *scaleSlider;
    QDial *dialRotation;
    QColor getColor(const QColor &startigColor);


public slots:
    void changeSides(int i);
    void changeColorSlot();
    void sliderChange(int i0, int i1);

};

#endif // MAINWINDOW_H
