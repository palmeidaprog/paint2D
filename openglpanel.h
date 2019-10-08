#ifndef OPENGLPANEL_H
#define OPENGLPANEL_H

#define GL_SILENCE_DEPRECATION
#include <iostream>
#include <QApplication>
#include <QMainWindow>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
//#include <OpenGL/gl.h>
//#include <OpenGL/OpenGL.h>
#include <OpenGL.h>
#include <gl.h>
#include <cmath>
#include "paintobject.h"
#include "transformation.h"
#include "transformationtype.h"
#include <QComboBox>
#include "mainwindow.h"
#include "objectscontroller.h"

using std::cout;
using std::endl;

//namespace Ui {
//class OpenGLPanel;
//}

class OpenGLPanel : public QOpenGLWidget, protected QOpenGLFunctions
{
Q_OBJECT
    int sides, z, meshX, meshY;
    bool toRotate, toTranslate, toScale, toReflect, toSheer;
    QColor color;
    double radius, red, green, blue, alpha, angleRot;
    double smallerX, biggerX, smallerY, biggerY;
    QComboBox colorsCombo;
    static constexpr int MAX_SIDES = 360;
    static constexpr int MIN_SIDES = 3;
    ObjectsController &objects;
    double zoom;

public:
    explicit OpenGLPanel(QWidget *parent = 0);
    virtual ~OpenGLPanel();

    int getSides();
    void setColor(QColor color);
    void rotate(float angle);
    void translate(double x, double y);
    void scale(double x, double y);

    void setZoom(double change) {
        this->zoom *= change;
        update();
    }

    void meshSize(int x, int y);


protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

public slots:
    void changeRadius(double radius);
    void changeNumSides(int sides);
    void changeColors(int color);
    void updateColor(const QColor &color);
    void rotationChanged(int initial) noexcept;
    void drawObject(int sides);

    //void rotate()

    inline const QColor &getColor() const noexcept {
        return this->color;
    }


private:

    void drawPrimitives(const PaintObject &obj);
    void initializeMesh(int w, int h);
    void pop();
};

#endif // OPENGLPANEL_H
