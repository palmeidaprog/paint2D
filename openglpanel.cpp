#include "openglpanel.h"


OpenGLPanel::OpenGLPanel(QWidget *parent) : QOpenGLWidget(parent), sides(3),
    radius(2.0f), red(1.0f/255*239), green(1.0f/255*145), blue(1.0f/255*143),
    alpha(0.7f) {
    //setFormat(QGL::DoubleBuffer | QGL::DepthBuffer);
    //ui = MainWindow::getInstance();
}

void OpenGLPanel::resizeGL(int w, int h) {
    double smallerX = 0, biggerX = 10, smallerY = 0, biggerY = 10;
    glViewport( 0, 0, (GLint)w, (GLint)h );

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1,1,-1,1, -1, 1);
    if (w > h) {
        h = h?h:1;
        double newW = (biggerX - smallerX) * w / h;
        double difW = newW - (biggerX - smallerX);
        smallerX = 0.0 - difW / 2.0;
        biggerX = 10 + difW / 2.0;
    } else {
        w = w ? w : 1;
        double newH = (biggerY - smallerY) * h / w;
        double diffH = newH - (biggerY - smallerY);
        smallerY = 0.0 - diffH / 2.0;
        biggerY = 10 + diffH / 2.0;
    }
    glOrtho(smallerX, biggerX, smallerY, biggerY, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}



void OpenGLPanel::initializeGL() {
    initializeOpenGLFunctions();
    glShadeModel(GL_SMOOTH);
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void OpenGLPanel::paintGL() {
    // GL_COLOR_BUFFET_BIT | GL_DEPTH_BUFFER_BIT
    glClear(GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslated(5.0, 5.0, 0.0);
    glLineWidth(1);
    //glColor4f(red, green, blue, alpha);
    glColor4f(this->color.redF(), this->color.greenF(),
              this->color.blueF(), this->color.alphaF());
    glBegin(GL_POLYGON);
    for(int i = 0; i < sides; i++) {
        glVertex2f(radius * cos(i*2*M_PI/sides),
                   radius * sin(i*2*M_PI/sides));

    }
    glEnd();
}

int OpenGLPanel::getSides() {
    return sides;
}


void OpenGLPanel::changeRadius(double radius) {
    if (radius != this->radius && radius >= 1.0 && radius <= 10.0) {
            this->radius = radius;
        update();
    }

}

void OpenGLPanel::changeNumSides(int sides) {
    if(sides != this->sides && sides >= MIN_SIDES && sides <= MAX_SIDES) {
        this->sides = sides;
        update();
    }
}

void OpenGLPanel::changeColors(int color) {
    switch(color) {
    case 0:
        red = 1.0f/255*239;
        green = 1.0f/255*45;
        blue = 1.0f/255*43;
        alpha = 0.7f;
        break;
    case 1:
        red = 1.0f/255*106;
        green = 1.0f/255*242;
        blue = 1.0f/255*99;
        alpha = 0.7f;
        break;
    case 2:
        red = 1.0f/255*0;
        green = 1.0f/255*0;
        blue = 1.0f/255*0;
        alpha = 1.0f;
        break;
    case 3:
        red = 1.0f/255*237;
        green = 1.0f/255*239;
        blue = 1.0f/255*143;
        alpha = 1.0f;
        break;
    default:
        red = 1.0f/255*20;
        green = 1.0f/255*20;
        blue = 1.0f/255*255;
        alpha = 0.7f;
        break;
    }
    update();
}

void OpenGLPanel::updateColor(const QColor &color) {
    this->color = color;
    update();
}

