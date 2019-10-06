#include "openglpanel.h"


OpenGLPanel::OpenGLPanel(QWidget *parent) : QOpenGLWidget(parent), sides(3),
    radius(2.0f), color(Qt::cyan) {
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
    //glScalef(0.1, 0.1, 1);
    glMatrixMode(GL_MODELVIEW);
    //glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}



void OpenGLPanel::initializeGL() {
    initializeOpenGLFunctions();
    glShadeModel(GL_SMOOTH);
    glClearColor(1.0, 1, 1, 1);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    update();
}

void OpenGLPanel::paintGL() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glLoadIdentity();
    glTranslated(5.0, 5.0, 0.0);
    glLineWidth(1);
    glColor4f(this->color.redF(), this->color.greenF(),
              this->color.blueF(), this->color.alphaF());
    this->initializeMesh(40, 20);
    glBegin(GL_POLYGON);
    for(int i = 0; i < sides; i++) {
        glVertex2f(radius * cos(i*2*M_PI/sides),
                   radius * sin(i*2*M_PI/sides));

    }
    glEnd();

    glBegin(GL_LINE_STRIP);
    glLineWidth(3);

    glColor4f(0, 0 , 0,1);
    for(int i = 0; i < sides; i++) {
        glVertex2f(radius * cos(i*2*M_PI/sides),
                   radius * sin(i*2*M_PI/sides));

    }
    glEnd();
}

int OpenGLPanel::getSides() {
    return sides;
}

void OpenGLPanel::drawObject(int sides) {
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

void OpenGLPanel::updateColor(const QColor &color) {
    this->color = color;
    update();
}

void OpenGLPanel::rotationChanged(int initial) noexcept {

    //glRotated(initial/100.0, 0.0, 0.0, 0.0);
    //glRotated(initial, 0.0, 1.0, 0.0);
    cout << initial << endl;
    //glLoadIdentity();
    glLoadIdentity();
    glTranslatef(0.5f, 0.5f, 0.5f);
    glRotatef(45.f, 1.f, 1.f, 1.f);
    glTranslatef(-0.5f, -0.5f, -0.5f);
    glColor3f(0.f, 0.f, 1.f);
    update();
}

void OpenGLPanel::initializeMesh(int w, int h) {
    int increment = this->height()/h;
    QColor gray = Qt::lightGray;
    cout << this->height() << "x";
    for (int i = 0; i <= this->height(); i += increment) {
        glBegin(GL_LINES);
        glColor4f(gray.redF(), gray.greenF(), gray.blueF(), gray.alphaF());
        glVertex2i(i, 0);
        glVertex2i(i, this->height());
        glEnd();
    }

    increment = this->width()/w;
    cout << this->width() << endl;
    for (int i = 0; i <= this->width(); i += increment) {
        glBegin((GL_LINES));
        glColor4f(gray.redF(), gray.greenF(), gray.blueF(), gray.alphaF());
        glVertex2i(0, i);
        glVertex2i(this->width(), i);
        glEnd();
    }

    glFlush();
    //update();
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


