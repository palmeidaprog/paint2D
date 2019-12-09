#ifndef OPENGLPANEL_H
#define OPENGLPANEL_H

#define GL_SILENCE_DEPRECATION
#include <iostream>
#include <QApplication>
#include <QMainWindow>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <coordinate.h>

// Else is linux
#ifdef __APPLE__
#include <OpenGL.h>
#include <gl.h>
#include <glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <memory>
#include <cmath>
#include "paintobject.h"
#include "transformation.h"
#include "transformationtype.h"
#include <QComboBox>
#include "mainwindow.h"
#include "objectscontroller.h"
#include "camera.h"
#include "vector3.h"
#include "matrix4.h"

using std::cout;
using std::endl;
using std::unique_ptr;

//namespace Ui {
//class OpenGLPanel;
//}

class OpenGLPanel : public QOpenGLWidget, protected QOpenGLFunctions
{
Q_OBJECT
    int sides, z, meshX, meshY;
    bool toRotate, toTranslate, toScale, toReflect, toSheer, toggleLightning;
    QColor color;
    double radius, red, green, blue, alpha, angleRot;
    double smallerX, biggerX, smallerY, biggerY;
    QComboBox colorsCombo;
    static constexpr int MAX_SIDES = 360;
    static constexpr int MIN_SIDES = 3;
    ObjectsController &objects;
    double zoom;
    Camera *camera;

public:
    explicit OpenGLPanel(QWidget *parent = 0);
    virtual ~OpenGLPanel();

    int getSides();
    void setColor(QColor color);
    void rotate(float angle, float axis);
    void translate(double x, double y, double z);
    void scale(double x, double y);
    void shear(double b, double a);
    void reflection(double x, double y);

    void setZoom(double change) {
        this->zoom *= change;
        update();
    }

    void meshSize(int x, int y);
    void glShear(double b, double a);
    void glRef(double x, double y);
    void cameraMovement(double value, Coordinate coord);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

public slots:
    void changeRadius(double radius);
    void changeNumSides(int sides);
    void changeColors(int color);
    void updateColor(const QColor &color);
    void drawObject(int sides);
    inline void enableLightning(bool enable = true) {
        this->toggleLightning = enable;
    }

    //void rotate()

    inline const QColor &getColor() const noexcept {
        return this->color;
    }


private:
    void drawSphere();
    void drawCube();
    void drawCylinder();
    void drawCone();
    void drawPrimitives(const PaintObject &obj);
    void drawTriangle();
    void drawPyramid();
    void perspectiveGL(GLdouble fovY, GLdouble aspect, GLdouble zNear,
                       GLdouble zFar);
    Matrix4 lookAtGL(Vector3& eye, Vector3& target, Vector3& upDir);
    void initializeMesh(int w, int h);
    void pop();
    void lightning();
};

#endif // OPENGLPANEL_H
