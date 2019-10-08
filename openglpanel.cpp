#include "openglpanel.h"


OpenGLPanel::OpenGLPanel(QWidget *parent) : QOpenGLWidget(parent),
    objects(ObjectsController::getInstance()), meshX(40), meshY(40),sides(3),
    z(-1), radius(2.0f), color(Qt::cyan), smallerX(0), biggerX(10),
    smallerY(0), biggerY(10), angleRot(0.0), zoom(1.0) {

}

OpenGLPanel::~OpenGLPanel()
{

}

void OpenGLPanel::resizeGL(int w, int h) {
    //double smallerX = 0, biggerX = 10, smallerY = 0, biggerY = 10;
    glViewport( 0, 0, (GLint)w, (GLint)h );

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1,1,-1,1, -1, 1);

//    if (w > h) {
//        h = h?h:1;
//        double newW = (biggerX - smallerX) * w / h;
//        double difW = newW - (biggerX - smallerX);
//        smallerX = 0.0 - difW / 2.0;
//        biggerX = 10 + difW / 2.0;
//    } else {
//        w = w ? w : 1;
//        double newH = (biggerY - smallerY) * h / w;
//        double diffH = newH - (biggerY - smallerY);
//        smallerY = 0.0 - diffH / 2.0;
//        biggerY = 10 + diffH / 2.0;
//    }

    //glOrtho(smallerX, biggerX, smallerY, biggerY, -1, 1);
    glOrtho(0, w, 0, h, -1, 1);
    //glScalef(0.1, 0.1, 1);
    //glOrtho(-1,w,-1,h, -1, 1);
    //glRotatef(0.45, 0, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    //glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();
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
    //glTranslated(10.0, 10.0, 0.0);
    this->initializeMesh(meshX, meshY);

//    size_t size = this->objects.size();
//    for (size_t i = 0; i < size; i++) {
//        auto obj = *this->objects[i];
//        if (obj.getId() == this->selected) {
//            std::swap(this->objects[size-1], this->objects[i]);
//            obj = *this->objects[i];
//        }

    //cout << "update"<< endl; // @debug
    while(this->objects.hasNextObject()) {
        //cout << "test" << endl; // @debug
        auto obj = this->objects.getNextObject();
        if (obj == nullptr) {
            //cout << "Parou" << endl;
            break;
        }
        //cout << "test1" << endl; // @debug
        glPushMatrix();
        glLoadIdentity();
        //cout << "test2" << endl; // @debug
        cout << obj->getId() << " " << obj->getColor().redF() << endl;
        //cout << "test2.1" << endl;
        while(obj->hasNextTransformation()) {
            //cout << "test3" << endl; // @debug
            auto transformation = obj->nextTransformation();
            //cout << "test4" << endl; // @debug
            if (transformation.getType() == TransformationType::SCALE) {
                glTranslatef((this->width()/2.0), (this->height()/2.0), 0);
                glScalef(transformation.getData1(), transformation.getData2(),
                         1);
                glTranslatef(-(this->width()/2.0), -(this->height()/2.0), 0);
            } else if (transformation.getType() ==
                       TransformationType::ROTATE) {
                glTranslatef((this->width()/2.0), (this->height()/2.0), 0);
                glRotatef(transformation.getData1(), 0, 0, 1);
                glTranslatef(-(this->width()/2.0), -(this->height()/2.0), 0);
            } else if (transformation.getType() ==
                       TransformationType::TRANSLATE) {
                glTranslatef(transformation.getData1(),
                             transformation.getData2(), 0);
            }
        }
        //cout << "Finalizou trans" << endl; // @debug

        this->drawPrimitives(*obj);
        glPopMatrix();
    }
    this->objects.resetIndexing();
    glScalef(this->zoom, this->zoom, 1.0);
    //pop();
}

//    double x0 = this->width()/2.0;
//    double y0 = this->height()/2.0;
//    double s = sides << 1;

//    glBegin(GL_POLYGON);

//    glVertex2f(x0, y0);
//    for(int i = 1; i < s; i++) {
//        glVertex2f(this->width()/10.0 * cos((i<<2)*M_PI/s) + x0,
//                   this->height()/10.0 * sin((i<<2)*M_PI/s) + y0);
//    }
//    glEnd();

//    glBegin(GL_LINE_STRIP);

//    glColor4f(0, 0 , 0,1);
//    //glVertex2f(x0, y0);
//    for(int i = 1; i < s; i++) {
//        glVertex2f(this->width()/10.0 * cos((i<<2)*M_PI/s) + x0,
//                   this->height()/10.0 * sin((i<<2)*M_PI/s) + y0);
//    }
//    glEnd();
//    cout << "t" << endl;
//    glPopMatrix();

void OpenGLPanel::pop() {
    //glPushMatrix();

}

int OpenGLPanel::getSides() {
    return sides;
}

void OpenGLPanel::rotate(float angle) {
    this->objects.addRotation(angle);
    update();
}

void OpenGLPanel::translate(double x, double y)
{
    this->objects.getSelected()->addTranslation(x, y);
    update();
}

void OpenGLPanel::scale(double x, double y)
{
    this->objects.getSelected()->addScale(x, y);
    update();
}

void OpenGLPanel::meshSize(int x, int y)
{
    this->meshX = x;
    this->meshY = y;
    update();
}

void OpenGLPanel::drawObject(int sides) {
//    this->selected = this->lastId;
//    this->objects.push_back(new PaintObject(this->lastId++, sides, this->color));
    this->objects.addObject(new PaintObject(sides, color));
    update();
}

void OpenGLPanel::drawPrimitives(const PaintObject &obj)
{
    glLineWidth(2);
    //cout << "Printa primitivos" << endl; // @debug
    glColor4f(obj.getColor().redF(), obj.getColor().greenF(),
              obj.getColor().blueF(), obj.getColor().alphaF());
    double x0 = this->width()/2.0;
    double y0 = this->height()/2.0;
    double s = obj.numberOfSides() << 1;

    glBegin(GL_POLYGON);

    glVertex2f(x0, y0);
    for(int i = 1; i < s; i++) {
        glVertex2f(this->width()/10.0 * cos((i<<2)*M_PI/s) + x0,
                   this->height()/10.0 * sin((i<<2)*M_PI/s) + y0);
    }
    glEnd();

    if (this->objects.getSelected()->getId() == obj.getId()) {
        glBegin(GL_LINE_STRIP);

        glColor4f(0, 0 , 0,1);
        //glVertex2f(x0, y0);
        for(int i = 1; i < s; i++) {
            glVertex2f(this->width()/10.0 * cos((i<<2)*M_PI/s) + x0,
                       this->height()/10.0 * sin((i<<2)*M_PI/s) + y0);
        }
        glEnd();
    }
    //cout << "Fim dos primitivos " << endl; // @debug
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
    this->objects.setColor(color);
    update();
}

void OpenGLPanel::rotationChanged(int initial) noexcept {
    this->objects.addRotation(initial);
    update();
    //glRotated(initial/100.0, 0.0, 0.0, 0.0);
    //glRotated(initial, 0.0, 1.0, 0.0);

    //glLoadIdentity();

}

//void OpenGLPanel::initializeMesh(int w, int h) {
//    double height = biggerY - smallerY;
//    double increment = height/h;
//    QColor gray = Qt::lightGray;

//    glLineWidth(1);
//    for (double i = smallerY; i <= height; i += increment) {
//        glBegin(GL_LINES);
//        glColor4f(gray.redF(), gray.greenF(), gray.blueF(), gray.alphaF());
//        glVertex2i(i, 0);
//        glVertex2i(i, this->height());
//        glEnd();
//    }

//    double width = biggerX - smallerX;
//    increment = width/w;
//    for (double i = smallerX; i <= width; i += increment) {
//        glBegin((GL_LINES));
//        glColor4f(gray.redF(), gray.greenF(), gray.blueF(), gray.alphaF());
//        glVertex2i(0, i);
//        glVertex2i(this->width(), i);
//        glEnd();
//    }

//    glFlush();
//    //update();
//}


void OpenGLPanel::initializeMesh(int w, int h) {
    int increment = this->height()/h;
    QColor gray = Qt::lightGray;
    cout << this->height() << "x";
    glLineWidth(1);
    for (int i = 0; i <= this->height() + increment* 5; i += increment) {
        glBegin(GL_LINES);
        glColor4f(gray.redF(), gray.greenF(), gray.blueF(), gray.alphaF());
        glVertex2i(i, 0);
        glVertex2i(i, this->height());
        glEnd();
    }

    increment = this->width()/w;
    cout << this->width() << endl;
    for (int i = 0; i <= this->width() + increment* 5; i += increment) {
        glBegin((GL_LINES));
        glColor4f(gray.redF(), gray.greenF(), gray.blueF(), gray.alphaF());
        glVertex2i(0, i);
        glVertex2i(this->width(), i);
        glEnd();
    }

    //glFlush();
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


