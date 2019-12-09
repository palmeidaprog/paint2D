#include "openglpanel.h"


OpenGLPanel::OpenGLPanel(QWidget *parent) : QOpenGLWidget(parent),
    objects(ObjectsController::getInstance()), meshX(40), meshY(40),sides(3),
    z(-1), radius(0.3f), toRotate(false), toTranslate(false), toScale(false),
    toReflect(false), toSheer(false), toggleLightning(true),
    color(Qt::cyan), smallerX(0), biggerX(10),
    smallerY(0), biggerY(10), angleRot(0.0), zoom(1.0),
    camera(new Camera()) {
    //this->initializeGL();
    //glEnable (GL_NORMALIZE);
}

OpenGLPanel::~OpenGLPanel()
{
    delete camera;
}

void OpenGLPanel::resizeGL(int w, int h) {
    this->smallerX = 0, this->biggerX = 10, this->smallerY = 0, this->biggerY = 10;
    glViewport(0, 0, (GLint)w, (GLint)h);
    //GLfloat fAspect = 4.0f/3.0f;
    GLfloat fAspect = (GLint)w/(GLint)h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (w > h) {
        h = h?h:1;
        double novaLargura = (biggerX - smallerX) * w / h;
        double difLargura = novaLargura - (biggerX - smallerX);
        smallerX = 0.0 - difLargura / 2.0;
        biggerX = 10 + difLargura / 2.0;
    } else {
        w = w?w:1;
        double novaAltura = (biggerY - smallerY) * h / w;
        double difAltura = novaAltura - (biggerY - smallerY);
        smallerY = 0.0 - difAltura / 2.0;
        biggerY = 10 + difAltura / 2.0;
    }
    //glOrtho(smallerX, biggerX, smallerY, biggerY,100,-100);\

    if (this->toggleLightning)
        this->lightning();

//    Vector3 eye = camera->getEye();
//    Vector3 target = camera->getTarget();
//    Vector3 upDir = camera->getUpDir();
//    this->lookAtGL(eye, target, upDir);
    gluPerspective(this->camera->getFOV(),fAspect,0.1f,500.0f);
    gluLookAt(this->camera->getX1(),
              this->camera->getY1(),
              this->camera->getZ1(),
              this->camera->getX2(),
              this->camera->getY2(),
              this->camera->getZ2(),0,1,0);
    glFrustum(smallerX, biggerX, smallerY, biggerY,1,1);
    //glFrustum(0, w, 0, h, -5, 5);
    //this->perspectiveGL(45.0f,fAspect,0.1,500);

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
    cout << "eye: " << eye[0] << "," << eye[1] << "," << eye[2] << endl;


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

void OpenGLPanel::lightning() {
    GLfloat specLight[4]={1.0, 1.0, 1.0, 1.0};
    GLfloat positionLight[4]={0.0, 50.0, 50.0, 1.0};
    GLfloat ambientLight[4]={0.2,0.2,0.2,1.0};
    GLfloat difLight[4]={0.7,0.7,0.7,1.0};
    GLfloat spec[4]={1.0,1.0,1.0,1.0};
    GLint specMaterial = 60;
    //glEnable (GL_NORMALIZE);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    //glClearDepthf(1.0f);
    glShadeModel(GL_SMOOTH);
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
}


void OpenGLPanel::initializeGL() {
    initializeOpenGLFunctions();
    glShadeModel(GL_SMOOTH);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
//    glDepthFunc(GL_LEQUAL);
//    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
//    glShadeModel(GL_SMOOTH);
//    glClearColor(1.0, 1, 1, 1);
//    glEnable(GL_DEPTH_TEST);
//    glDepthFunc(GL_LEQUAL);
//    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    //update();
}

void OpenGLPanel::paintGL() {
    this->resizeGL(this->width(), this->height());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    glEnable(GL_NORMALIZE);
    //this->lightning();
    //glTranslated(.01,.01,0.0);

    //this->lookAtGL(eye, target, upDir);
//    gluLookAt(this->camera->getX1(),
//              this->camera->getY1(),
//              this->camera->getZ1(),
//              this->camera->getX2(),
//              this->camera->getY2(),
//              this->camera->getZ2(),0,1,0);
    this->initializeMesh(meshX, meshY);

//    size_t size = this->objects.size();
//    for (size_t i = 0; i < size; i++) {
//        auto obj = *this->objects[i];
//        if (obj.getId() == this->selected) {
//            std::swap(this->objects[size-1], this->objects[i]);
//            obj = *this->objects[i];
//        }

    //cout << "update"<< endl; // @debug

    this->objects.resetIndexing();
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
                double d2 = transformation.getData2();
                glRotatef(transformation.getData1(), d2==1?1:0, d2==2?1:0,
                          d2==3?1:0);
                glTranslatef(-(this->width()/2.0), -(this->height()/2.0), 0);
            } else if (transformation.getType() ==
                       TransformationType::TRANSLATE) {
                glTranslatef(transformation.getData1(),
                             transformation.getData2(),
                             transformation.getData3());
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

void OpenGLPanel::rotate(float angle, float axis) {
    this->objects.addRotation(angle, axis);
    update();
}
void OpenGLPanel::translate(double x, double y, double z)
{
    this->objects.getSelected()->addTranslation(x, y, z);
    update();
}

void OpenGLPanel::cameraMovement(double value, Coordinate coord)
{
    double v = 0;
    switch(coord) {
    case Coordinate::Y:
        v = 2*value*M_PI/180;
        value += this->camera->getY1();
        this->camera->setY1(value);
        this->camera->setPOV(value);
        this->camera->setX1(this->camera->getDistance()*cos(v));
        this->camera->setZ1(this->camera->getDistance()*sin(v));
        break;
    case Coordinate::E:
        this->camera->setY1(this->camera->getY1() + value);
        break;
    case Coordinate::DISTANCE:
        v = 2*this->camera->getPOV()*M_PI/180;
        value += this->camera->getDistance();
        this->camera->setDistance(value);
        this->camera->setX1(value*cos(v));
        this->camera->setZ1(value*sin(v));
        break;
    case Coordinate::Z:
        this->camera->addToFOV(value);
    default:
        break;
    }
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
    cout << "Sides: " << sides << endl;
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

void OpenGLPanel::drawCube() {
    glBegin(GL_POLYGON);

    glColor3f( 1.0, 0.0, 0.0 );
    glVertex3f(  0.5, -0.5, -0.5 );
    glColor3f( 0.0, 1.0, 0.0 );
    glVertex3f(  0.5,  0.5, -0.5 );
    glColor3f( 0.0, 0.0, 1.0 );
    glVertex3f( -0.5,  0.5, -0.5 );
    glColor3f( 1.0, 0.0, 1.0 );
    glVertex3f( -0.5, -0.5, -0.5 );

    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(   1.0,  1.0, 1.0 );
    glVertex3f(  0.5, -0.5, 0.5 );
    glVertex3f(  0.5,  0.5, 0.5 );
    glVertex3f( -0.5,  0.5, 0.5 );
    glVertex3f( -0.5, -0.5, 0.5 );
    glEnd();

    // purple right
    glBegin(GL_POLYGON);
    glColor3f(  1.0,  0.0,  1.0 );
    glVertex3f( 0.5, -0.5, -0.5 );
    glVertex3f( 0.5,  0.5, -0.5 );
    glVertex3f( 0.5,  0.5,  0.5 );
    glVertex3f( 0.5, -0.5,  0.5 );
    glEnd();

    // green left
    glBegin(GL_POLYGON);
    glColor3f(   0.0,  1.0,  0.0 );
    glVertex3f( -0.5, -0.5,  0.5 );
    glVertex3f( -0.5,  0.5,  0.5 );
    glVertex3f( -0.5,  0.5, -0.5 );
    glVertex3f( -0.5, -0.5, -0.5 );
    glEnd();

    // blue top
    glBegin(GL_POLYGON);
    glColor3f(   0.0,  0.0,  1.0 );
    glVertex3f(  0.5,  0.5,  0.5 );
    glVertex3f(  0.5,  0.5, -0.5 );
    glVertex3f( -0.5,  0.5, -0.5 );
    glVertex3f( -0.5,  0.5,  0.5 );
    glEnd();

    // red bottom
    glBegin(GL_POLYGON);
    glColor3f(   1.0,  0.0,  0.0 );
    glVertex3f(  0.5, -0.5, -0.5 );
    glVertex3f(  0.5, -0.5,  0.5 );
    glVertex3f( -0.5, -0.5,  0.5 );
    glVertex3f( -0.5, -0.5, -0.5 );
    glEnd();

    glFlush();
}

//void OpenGLPanel::drawCube() {
//    glBegin(GL_QUADS);
//    ////glColor3ub(red[j],green[j],blue[j]);
//    glVertex3f( 1.0f, 1.0f, -1.0f);
//    glVertex3f(-1.0f, 1.0f, -1.0f);
//    glVertex3f(-1.0f, 1.0f,  1.0f);
//    glVertex3f( 1.0f, 1.0f,  1.0f);

//    //glColor3ub(red[j],green[j],blue[j]);
//    glVertex3f( 1.0f, -1.0f,  1.0f);
//    glVertex3f(-1.0f, -1.0f,  1.0f);
//    glVertex3f(-1.0f, -1.0f, -1.0f);
//    glVertex3f( 1.0f, -1.0f, -1.0f);

//    //glColor3ub(red[j],green[j],blue[j]);
//    glVertex3f( 1.0f,  1.0f, 1.0f);
//    glVertex3f(-1.0f,  1.0f, 1.0f);
//    glVertex3f(-1.0f, -1.0f, 1.0f);
//    glVertex3f( 1.0f, -1.0f, 1.0f);

//    //glColor3ub(red[j],green[j],blue[j]);
//    glVertex3f( 1.0f, -1.0f, -1.0f);
//    glVertex3f(-1.0f, -1.0f, -1.0f);
//    glVertex3f(-1.0f,  1.0f, -1.0f);
//    glVertex3f( 1.0f,  1.0f, -1.0f);

//    //glColor3ub(red[j],green[j],blue[j]);
//    glVertex3f(-1.0f,  1.0f,  1.0f);
//    glVertex3f(-1.0f,  1.0f, -1.0f);
//    glVertex3f(-1.0f, -1.0f, -1.0f);
//    glVertex3f(-1.0f, -1.0f,  1.0f);

//    //glColor3ub(red[j],green[j],blue[j]);
//    glVertex3f(1.0f,  1.0f, -1.0f);
//    glVertex3f(1.0f,  1.0f,  1.0f);
//    glVertex3f(1.0f, -1.0f,  1.0f);
//    glVertex3f(1.0f, -1.0f, -1.0f);
//    glEnd();
//    glColor3f(1,0,0);
//    glBegin(GL_LINES);
//    glVertex3f(this->radius,0,0);
//    glVertex3f(0,0,0);
//    glEnd();

//    glColor3f(0,1,0);
//    glBegin(GL_LINES);
//    glVertex3f(0,this->radius,0);
//    glVertex3f(0,0,0);
//    glEnd();

//    glColor3f(0,0,1);
//    glBegin(GL_LINES);
//    glVertex3f(0,0,this->radius);
//    glVertex3f(0,0,0);
//    glEnd();
//}


void OpenGLPanel::drawPrimitives(const PaintObject &obj)
{
    glLineWidth(2);
    //cout << "Printa primitivos" << endl; // @debug
    glColor4f(obj.getColor().redF(), obj.getColor().greenF(),
              obj.getColor().blueF(), obj.getColor().alphaF());
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    switch (obj.numberOfSides()) {
    case 2:
        this->drawCone();
        break;
    case 3:
        this->drawPyramid();
        break;
    case 4:
        this->drawCube();
        break;
    case 5:
        this->drawCylinder();
        break;
    case 6:
        this->drawSphere();
        break;
    default:
        break;
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


void OpenGLPanel::initializeMesh(int w, int h) {
    glColor4f(.3,.3,.3, 1.0f);
//    glPushMatrix();
//    glTranslatef(-1, 0, -1);
//    glRotatef(-45, 1, 0, 0); // If you want it to be rotated in Y
//    glRotatef(15, 0, 1, 0); // If you want it to be rotated in Y
//    glRotatef(0, 0, 0, 1); // If you want it to be rotated in Y


    glBegin(GL_QUADS);
    glVertex3f( 0,-0.001, 0);
    glVertex3f( 0,-0.001,10);
    glVertex3f(10,-0.001,10);
    glVertex3f(10,-0.001, 0);
    glEnd();

    glBegin(GL_LINES);
    for(int i=0;i<=w;i++) {

        if (i==0) { glColor3f(.6,.3,.3); } else { glColor3f(.25,.25,.25); };
        glVertex3f(i,0,0);
        glVertex3f(i,0,10);
        if (i==0) { glColor3f(.3,.3,.6); } else { glColor3f(.25,.25,.25); };
        glVertex3f(0,0,i);
        glVertex3f(10,0,i);
    }
    glEnd();

    glPopMatrix();
}

//void OpenGLPanel::initializeMesh(int w, int h) {
//    double height = biggerY - smallerY;
//    double increment = height/h;
//    QColor gray = Qt::lightGray;
//    glPushMatrix();
//    glLineWidth(1);
//    for (double i = smallerY; i <= height; i += increment) {
//        glLineStipple(2, 0xAAAA);
//        glEnable(GL_LINE_STIPPLE);
//        glBegin(GL_LINES);
//        glColor4f(gray.redF(), gray.greenF(), gray.blueF(), gray.alphaF());
//        glVertex2i(i, 0);
//        glVertex2i(i, this->height());
//        glEnd();
//    }

//    double width = biggerX - smallerX;
//    increment = width/w;
//    for (double i = smallerX; i <= width; i += increment) {
//        glLineStipple(2, 0xAAAA);
//        glEnable(GL_LINE_STIPPLE);

//        glBegin((GL_LINES));
//        glColor4f(gray.redF(), gray.greenF(), gray.blueF(), gray.alphaF());
//        glVertex2i(0, i);
//        glVertex2i(this->width(), i);
//        glEnd();
//    }


//    glRotatef(60, 0, 1, 0); // If you want it to be rotated in Y
//    glPopMatrix();
//    glFlush();
//    //update();
//}

//vj
//void OpenGLPanel::initializeMesh(int w, int h) {
//    glColor3f(0,0,0);
//    glLineWidth(0.5);
//    glLineStipple(2, 0xAAAA);
//    glEnable(GL_LINE_STIPPLE);
//    glBegin(GL_LINES);
//    glPushMatrix();
//    for(int i = 0; i <= 8; i++){
//        // x and y
//        glVertex3i(0, i, 0);
//        glVertex3i( 0, i, 8);
//        glVertex3i( 0, 0, i);
//        glVertex3i( 0, 8, i);

//        // y and z
//        glVertex3i( i, 0, 0);
//        glVertex3i( i, 8, 0);
//        glVertex3i( 0, i,0);
//        glVertex3i( 8, i,0);

//        // x and z
//        glVertex3i( 0, 0, i);
//        glVertex3i( 8, 0, i);
//        glVertex3i( i,0, 0);
//        glVertex3i( i,0, 8);
//    }
//    glEnd();

//    glRotatef(60, 0, 1, 0); // If you want it to be rotated in Y
//    glPopMatrix();

//}



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

void OpenGLPanel::drawPyramid()
{
//    glTranslated(eixoX[j], eixoY[j], eixoZ[j]);
//    glRotated(anguloX[j], 1, 0, 0);
//    glRotated(anguloY[j], 0, 1, 0);
//    glRotated(anguloZ[j], 0, 0, 1);
//    glScaled(escalaX[j], escalaY[j], escalaZ[j]);
    glBegin(GL_TRIANGLES);
    //glColor3ub(red[j],green[j],blue[j]);
    glVertex3f( 0.0f, 1.0f, 0.0f);
    //glColor3ub(red[j],green[j],blue[j]);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    //glColor3ub(red[j],green[j],blue[j]);
    glVertex3f(1.0f, -1.0f, 1.0f);

    //glColor3ub(red[j],green[j],blue[j]);
    glVertex3f(0.0f, 1.0f, 0.0f);
    //glColor3ub(red[j],green[j],blue[j]);
    glVertex3f(1.0f, -1.0f, 1.0f);
    //glColor3ub(red[j],green[j],blue[j]);
    glVertex3f(1.0f, -1.0f, -1.0f);

    //glColor3ub(red[j],green[j],blue[j]);
    glVertex3f(0.0f, 1.0f, 0.0f);
    //glColor3ub(red[j],green[j],blue[j]);
    glVertex3f(1.0f, -1.0f, -1.0f);
    //glColor3ub(red[j],green[j],blue[j]);
    glVertex3f(-1.0f, -1.0f, -1.0f);

    //glColor3ub(red[j],green[j],blue[j]);
    glVertex3f( 0.0f, 1.0f, 0.0f);
    //glColor3ub(red[j],green[j],blue[j]);
    glVertex3f(-1.0f,-1.0f,-1.0f);
    //glColor3ub(red[j],green[j],blue[j]);
    glVertex3f(-1.0f,-1.0f, 1.0f);
    glLineWidth(2);

    glEnd();
    glColor3f(1,0,0);
    glBegin(GL_LINES);
    glVertex3f(this->radius,0,0);
    glVertex3f(0,0,0);
    glEnd();

    glColor3f(0,1,0);
    glBegin(GL_LINES);
    glVertex3f(0,this->radius,0);
    glVertex3f(0,0,0);
    glEnd();

    glColor3f(0,0,1);
    glBegin(GL_LINES);
    glVertex3f(0,0,this->radius);
    glVertex3f(0,0,0);
    glEnd();
}

void OpenGLPanel::drawCylinder() {
    glBegin(GL_QUAD_STRIP);
    for (int l=0;l<=360;l+=5) {
        //glColor3ub(red[j],green[j],blue[j]);

        glVertex3f(cos(M_PI/180*l), 1, sin(M_PI/180*l));
        //glColor3ub(red[j],green[j],blue[j]);
        glVertex3f(cos(M_PI/180*l),-1,sin(M_PI/180*l));
    }
    glEnd();


    for (int i=1;i>=-1;i-=2) {
        glBegin(GL_TRIANGLE_FAN);
        //glColor3ub(red[j],green[j],blue[j]);
        glVertex3f(0,i,0);
        for (int k=0;k<=360;k+=5) {
            //glColor3ub(red[j],green[j],blue[j]);
            glVertex3f(i*cos(M_PI/180*k),i,sin(M_PI/180*k));
        }
        glEnd();
    }


    glColor3f(1,0,0);
    glBegin(GL_LINES);
    glVertex3f(this->radius,0,0);
    glVertex3f(0,0,0);
    glEnd();

    glColor3f(0,1,0);
    glBegin(GL_LINES);
    glVertex3f(0,this->radius,0);
    glVertex3f(0,0,0);
    glEnd();

    glColor3f(0,0,1);
    glBegin(GL_LINES);
    glVertex3f(0,0,this->radius);
    glVertex3f(0,0,0);
    glEnd();
}


void OpenGLPanel::drawSphere() {
    for (int ph2=-90;ph2<90;ph2+=5) {
        glBegin(GL_QUAD_STRIP);
        for (int th2=0;th2<=360;th2+=10) {
            //glColor3ub(red[j],green[j],blue[j]);
            double x1 = sin(M_PI/180*th2)*cos(M_PI/180*ph2);
            double y1 = cos(M_PI/180*th2)*cos(M_PI/180*ph2);
            double z1 = sin(M_PI/180*ph2);
            glVertex3d(x1,y1,z1);
            //lColor3ub(red[j],green[j],blue[j]);
            double x2 = sin(M_PI/180*th2)*cos(M_PI/180*(ph2+5));
            double y2 = cos(M_PI/180*th2)*cos(M_PI/180*(ph2+5));
            double z2 = sin(M_PI/180*(ph2+5));
            glVertex3d(x2,y2,z2);
        }
        glEnd();
    }

    glColor3f(1,0,0);
    glBegin(GL_LINES);
    glVertex3f(this->radius,0,0);
    glVertex3f(0,0,0);
    glEnd();

    glColor3f(0,1,0);
    glBegin(GL_LINES);
    glVertex3f(0,this->radius,0);
    glVertex3f(0,0,0);
    glEnd();

    glColor3f(0,0,1);
    glBegin(GL_LINES);
    glVertex3f(0,0,this->radius);
    glVertex3f(0,0,0);
    glEnd();
}

void OpenGLPanel::drawCone() {
    glBegin(GL_TRIANGLES);
    for (int k=0;k<=360;k+=5){
        //glColor3ub(red[j],green[j],blue[j]);
        glVertex3f(0,0,1);
        //glColor3ub(red[j],green[j],blue[j]);
        glVertex3f(cos(M_PI/180*k),sin(M_PI/180*k),0);
        //glColor3ub(red[j],green[j],blue[j]);
        glVertex3f(cos(M_PI/180*(k+5)),sin(M_PI/180*(k+5)),0);
    }
    glEnd();


    glRotated(90,1,0,0);
    glBegin(GL_TRIANGLES);
    for (int k=0;k<=360;k+=5) {
        //glColor3ub(red[j],green[j],blue[j]);
        glVertex3f(0,0,0);
        //glColor3ub(red[j],green[j],blue[j]);
        glVertex3f(cos(M_PI/180*k),0,sin(M_PI/180*k));
        //glColor3ub(red[j],green[j],blue[j]);
        glVertex3f(cos(M_PI/180*(k+5)),0,sin(M_PI/180*(k+5)));
    }
    glEnd();

    glColor3f(1,0,0);
    glBegin(GL_LINES);
    glVertex3f(this->radius,0,0);
    glVertex3f(0,0,0);
    glEnd();

    glColor3f(0,1,0);
    glBegin(GL_LINES);
    glVertex3f(0,this->radius,0);
    glVertex3f(0,0,0);
    glEnd();

    glColor3f(0,0,1);
    glBegin(GL_LINES);
    glVertex3f(0,0,this->radius);
    glVertex3f(0,0,0);
    glEnd();
}

