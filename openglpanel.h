#ifndef OPENGLPANEL_H
#define OPENGLPANEL_H

#define GL_SILENCE_DEPRECATION
#include <QApplication>
#include <QMainWindow>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <OpenGL/gl.h>
#include <OpenGL.h>
#include <gl.h>
#include <cmath>
#include <iostream>
#include <QComboBox>
#include "mainwindow.h"

using std::cout;
using std::endl;

//namespace Ui {
//class OpenGLPanel;
//}

class OpenGLPanel : public QOpenGLWidget, protected QOpenGLFunctions
{
Q_OBJECT
public:
    explicit OpenGLPanel(QWidget *parent = 0);
    virtual ~OpenGLPanel() { }

    int getSides();
    void setColor(QColor color);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

public slots:
    void changeRadius(double radius);
    void changeNumSides(int sides);
    void changeColors(int color);
    void updateColor(const QColor &color);

    inline const QColor &getColor() const noexcept {
        return this->color;
    }


private:
    int sides;
    QColor color;
    double radius, red, green, blue, alpha;
    QComboBox colorsCombo;
    static constexpr int MAX_SIDES = 360;
    static constexpr int MIN_SIDES = 3;
};

#endif // OPENGLPANEL_H
