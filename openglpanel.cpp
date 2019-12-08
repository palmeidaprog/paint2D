#include "openglpanel.h"


OpenGLPanel::OpenGLPanel(QWidget *parent) : QOpenGLWidget(parent),
    objects(ObjectsController::getInstance()), meshX(40), meshY(40),sides(3),
    z(-1), radius(2.0f), color(Qt::cyan), smallerX(0), biggerX(10),
    smallerY(0), biggerY(10), angleRot(0.0), zoom(1.0),
    camera(unique_ptr<Camera>(new Camera())) {
    //this->initializeGL();
    //glEnable (GL_NORMALIZE);
}

OpenGLPanel::~OpenGLPanel()
{

}

void OpenGLPanel::resizeGL(int w, int h) {
    glViewport(0, 0, (GLint)w, (GLint)h);
    GLfloat fAspect = (GLint)w/(GLint)h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    this->perspectiveGL(45,fAspect,0.1,500);
    //this->
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

//    glViewport( 0, 0, (GLint)w, (GLint)h );

//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    glOrtho(-1,1,-1,1, -1, 1);

//    glOrtho(0, w, 0, h, -1, 1);
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();


}

Matrix4 OpenGLPanel::lookAtGL(Vector3& eye, Vector3& target, Vector3& upDir)
{
    // compute the forward vector from target to eye
    Vector3 forward = eye - target;
    forward.normalize();                 // make unit length

    // compute the left vector
    Vector3 left = upDir.cross(forward); // cross product
    left.normalize();

    // recompute the orthonormal up vector
    Vector3 up = forward.cross(left);    // cross product

    // init 4x4 matrix
    Matrix4 matrix;
    matrix.identity();

    // set rotation part, inverse rotation matrix: M^-1 = M^T for Euclidean transform
    matrix[0] = left.x;
    matrix[4] = left.y;
    matrix[8] = left.z;
    matrix[1] = up.x;
    matrix[5] = up.y;
    matrix[9] = up.z;
    matrix[2] = forward.x;
    matrix[6] = forward.y;
    matrix[10]= forward.z;

    // set translation part
    matrix[12]= -left.x * eye.x - left.y * eye.y - left.z * eye.z;
    matrix[13]= -up.x * eye.x - up.y * eye.y - up.z * eye.z;
    matrix[14]= -forward.x * eye.x - forward.y * eye.y - forward.z * eye.z;

    return matrix;
}

//void OpenGLPanel::lookAtGL(GLfloat eyeX, GLfloat eyeY, GLfloat eyeZ,
//                           GLfloat lookAtX, GLfloat lookAtY, GLfloat lookAtZ,
//                           GLfloat upX, GLfloat upY, GLfloat upZ) {
//    Vector3f x, y, z;
//    z = Vector3f(eyeX-lookAtX, eyeY-lookAtY, eyeZ-lookAtZ).normalize();
//    y = Vector3f(upX, upY, upZ);
//    x = y ^ z; // <------------------------------ Marcio, OU EXCLUSIVO :)
//    y = z ^ x; // <------------------------------ Marcio, OU EXCLUSIVO :)
//    x = x.normalize();
//    y = y.normalize();
//    // mat is given transposed so OpenGL can handle it.
//    Matrix4x4 mat (new GLfloat[16]
//                     {x.getX(), y.getX(),   z.getX(),   0,
//                     x.getY(),  y.getY(),   z.getY(),   0,
//                     x.getZ(),  y.getZ(),   z.getZ(),   0,
//                     -eyeX,     -eyeY,      -eyeZ,      1});
//    glMultMatrixf(mat.getComponents());
//}

void OpenGLPanel::perspectiveGL(GLdouble fovY, GLdouble aspect,
                                GLdouble zNear, GLdouble zFar ) {
    constexpr GLdouble pi = 3.1415926535897932384626433832795;
    GLdouble fW, fH;

    //fH = tan( (fovY / 2) / 180 * pi ) * zNear;
    fH = tan( fovY / 360 * pi ) * zNear;
    fW = fH * aspect;

    glFrustum(-fW, fW, -fH, fH, zNear, zFar);
}


void OpenGLPanel::initializeGL() {
    GLfloat specLight[4]={1.0, 1.0, 1.0, 1.0};
    GLfloat positionLight[4]={30.0, 30.0, 30.0, 1.0};
    GLfloat ambientLight[4]={1.2,1.2,1.2,2.0};
    GLfloat difLight[4]={0.7,0.7,0.7,1.0};
    GLfloat spec[4]={1.0,1.0,1.0,1.0};
    GLint specMaterial = 60;


    initializeOpenGLFunctions();
    glEnable (GL_NORMALIZE);

    glMaterialfv(GL_FRONT,GL_SPECULAR, spec);
    glMateriali(GL_FRONT,GL_SHININESS, specMaterial);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, difLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specLight);
    glLightfv(GL_LIGHT0, GL_POSITION, positionLight);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);


//    glShadeModel(GL_SMOOTH);
//    glClearColor(1.0, 1, 1, 1);
//    glEnable(GL_DEPTH_TEST);
//    glDepthFunc(GL_LEQUAL);
//    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    //update();
}

void OpenGLPanel::paintGL() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    glTranslated(.01,.01,0.0);
    Vector3 eye = camera->getEye();
    Vector3 target = camera->getTarget();
    Vector3 upDir = camera->getUpDir();
    this->lookAtGL(eye, target, upDir);
    this->initializeMesh(meshX, meshY);
    this->objects.resetIndexing();

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
        //glLoadIdentity();
        //cout << "test2" << endl; // @debug
        while(obj->hasNextTransformation()) {
            cout << "test3" << endl; // @debug
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
            } else if (transformation.getType() ==
                       TransformationType::REFLECTION) {
                glTranslatef((this->width()/2.0), (this->height()/2.0), 0);
                glRef(transformation.getData1(),
                             transformation.getData2());
                glTranslatef(-(this->width()/2.0), -(this->height()/2.0), 0);
            } else if (transformation.getType() ==
                       TransformationType::SHEAR) {
                glTranslatef((this->width()/2.0), (this->height()/2.0), 0);
                glShear(transformation.getData1(), transformation.getData2());
                glTranslatef(-(this->width()/2.0), -(this->height()/2.0), 0);
            }

        }
        obj->resetIndexes();
        //cout << "Finalizou trans" << endl; // @debug

        this->drawPrimitives(*obj);
        glPopMatrix();
    }
    //glLoadIdentity();
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

void OpenGLPanel::shear(double b, double a)
{
    this->objects.addShear(b, a);
    update();
}

void OpenGLPanel::reflection(double x, double y)
{
    this->objects.addReflection(x, y);
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



void OpenGLPanel::glShear(double b, double a)
{
    GLfloat m[16] = {
        1.0f, (GLfloat)b, 0.0f, 0.0f,
        (GLfloat)a, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    glMultMatrixf(m);
}

void OpenGLPanel::glRef(double x, double y)
{
    GLfloat m[16] = {
        (GLfloat)x, 0.0f, 0.0f, 0.0f,
        0.0f, (GLfloat)y, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    glMultMatrixf(m);
}


void OpenGLPanel::drawPrimitives(const PaintObject &obj)
{
    glLineWidth(2);
    //cout << "Printa primitivos" << endl; // @debug
    glColor4f(obj.getColor().redF(), obj.getColor().greenF(),
              obj.getColor().blueF(), obj.getColor().alphaF());
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    if (obj.numberOfSides() == 3) {
        this->drawTriangle();
    }

//    glEnable(GL_BLEND);

//    double x0 = this->width()/2.0;
//    double y0 = this->height()/2.0;
//    double s = obj.numberOfSides() << 1;

//    glBegin(GL_POLYGON);

//    glVertex2f(x0, y0);
//    for(int i = 1; i < s; i++) {
//        glVertex2f(this->width()/10.0 * cos((i<<2)*M_PI/s) + x0,
//                   this->height()/10.0 * sin((i<<2)*M_PI/s) + y0);
//    }
//    glEnd();

//    if (this->objects.getSelected()->getId() == obj.getId()) {
//        glBegin(GL_LINE_STRIP);

//        glColor4f(0, 0 , 0,1);
//        //glVertex2f(x0, y0);
//        for(int i = 1; i < s; i++) {
//            glVertex2f(this->width()/10.0 * cos((i<<2)*M_PI/s) + x0,
//                       this->height()/10.0 * sin((i<<2)*M_PI/s) + y0);
//        }
//        glEnd();
//    }
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
    glColor3f(0,0,0);
    glLineWidth(0.5);
    glLineStipple(2, 0xAAAA);
    glEnable(GL_LINE_STIPPLE);
    glBegin(GL_LINES);
    for(int i = 0; i <= 150; i++){
        glVertex3i(0, i, 0);//X e Y
        glVertex3i( 0, i, 150);
        glVertex3i( 0, 0, i);
        glVertex3i( 0, 150, i);
        glVertex3i( i, 0, 0);//Y e Z
        glVertex3i( i, 150, 0);
        glVertex3i( 0, i,0);
        glVertex3i( 150, i,0);
        glVertex3i( 0, 0, i);//X e Z
        glVertex3i( 150, 0, i);
        glVertex3i( i,0, 0);
        glVertex3i( i,0, 150);
    }
    glEnd();
}


//void OpenGLPanel::initializeMesh(int w, int h) {
//    int increment = this->height()/h;
//    QColor gray = Qt::lightGray;
//    cout << this->height() << "x";
//    glLineWidth(1);
//    for (int i = 0; i <= this->height() + increment* 5; i += increment) {
//        glBegin(GL_LINES);
//        glColor4f(gray.redF(), gray.greenF(), gray.blueF(), gray.alphaF());
//        glVertex2i(i, 0);
//        glVertex2i(i, this->height());
//        glEnd();
//    }

//    increment = this->width()/w;
//    cout << this->width() << endl;
//    for (int i = 0; i <= this->width() + increment* 5; i += increment) {
//        glBegin((GL_LINES));
//        glColor4f(gray.redF(), gray.greenF(), gray.blueF(), gray.alphaF());
//        glVertex2i(0, i);
//        glVertex2i(this->width(), i);
//        glEnd();
//    }

//    //glFlush();
//    //update();
//}

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

void OpenGLPanel::drawTriangle() {
    glBegin(GL_TRIANGLES);
    glVertex3f(0.5,1,0.5);
    glVertex3f(1,0,0);
    glVertex3f(0,0,0);

    glVertex3f(0.5,1,0.5);
    glVertex3f(0,0,1);
    glVertex3f(0,0,0);

    glVertex3f(0.5,1,0.5);
    glVertex3f(1,0,1);
    glVertex3f(0,0,1);

    glVertex3f(0.5,1,0.5);
    glVertex3f(1,0,1);
    glVertex3f(1,0,0);
    glEnd();
}


