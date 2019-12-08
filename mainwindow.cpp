#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    panel = ui->panel;
    //doubleSpinBoxRadius = ui->doubleSpinBoxRadius;
    spinBoxSides = ui->spinBoxSides;
    //colorsCombo = ui->colorsCombo;
    spinBoxSides->setValue(3);
    //scaleSlider = ui->scaleSlider;
    this->colorBtn = this->ui->colorBtn;
    //doubleSpinBoxRadius->setValue(2.0);
    dialRotation = ui->dialRotation;
    this->angleRotEdit = ui->angleRotEdit;
    this->rotateBtn = ui->rotateBtn;
    this->makeConeBtn = ui->makeConeBtn;
    this->makeCubeBtn = ui->makeCubeBtn;
    this->makeCylinderBtn = ui->makeCylinderBtn;
    this->makeSphereBtn = ui->makeSphereBtn;
    this->makePyramidBtn = ui->makePyramidBtn;
    this->xEdit = ui->xEdit;
    this->yEdit = ui->yEdit;
    this->goTransBtn = ui->goTransBtn;
    this->upBtn = ui->upBtn;
    this->downBtn = ui->downBtn;
    this->leftBtn = ui->leftBtn;
    this->rightBtn = ui->rigthBtn;


    //events
    connect(spinBoxSides, SIGNAL(valueChanged(int)), this,
            SLOT(changeSides(int)));
    connect(this->colorBtn, SIGNAL(clicked()), this,
            SLOT(changeColorSlot()));
    connect(this->dialRotation, SIGNAL(sliderMoved(int)), panel,
            SLOT(rotationChanged(int)));
    connect(this->rotateBtn, SIGNAL(clicked(bool)), this,
            SLOT(rotateEvent(void)));

    connect(this->makeConeBtn, SIGNAL(clicked(bool)), this,
            SLOT(coneClicked()));
    connect(this->makeCubeBtn, SIGNAL(clicked(bool)), this,
            SLOT(cubeClicked()));
    connect(this->makeCylinderBtn, SIGNAL(clicked(bool)), this,
            SLOT(cylinderClicked()));
    connect(this->makeSphereBtn, SIGNAL(clicked(bool)), this,
            SLOT(sphereClicked()));


    // translate
    connect(this->goTransBtn, SIGNAL(clicked(bool)), this,
            SLOT(goTranslateClicked()));
    connect(this->upBtn, SIGNAL(clicked(bool)), this,
            SLOT(topTranslate()));
    connect(this->downBtn, SIGNAL(clicked(bool)), this,
            SLOT(bottomTranslate()));
    connect(this->leftBtn, SIGNAL(clicked(bool)), this,
            SLOT(leftTranslate()));
    connect(this->rightBtn, SIGNAL(clicked(bool)), this,
            SLOT(rightTranslate()));

    // zoom
    this->zoomInBtn = ui->zoomInBtn;
    this->zoomOutBtn = ui->zoomOutBtn;
    connect(this->zoomInBtn, SIGNAL(clicked(bool)), this,
            SLOT(zoomIn()));
    connect(this->zoomOutBtn, SIGNAL(clicked(bool)), this,
            SLOT(zoomOut()));

    // QListView and Model
    this->view = ui->listView;
    this->model = new QStringListModel(this);
    this->model->setStringList(ObjectsController::getInstance().getList());
    this->view->setModel(this->model);
    connect(this->view, SIGNAL(pressed(QModelIndex)), this,
            SLOT(selectObject(QModelIndex)));

    // QListView buttons
    this->openBtn = ui->openBtn;
    this->saveBtn = ui->saveBtn;
    this->deleteAllBtn = ui->deleteAllBtn;
    this->delSelectedBtn = ui->delSelectedBtn;
    connect(this->saveBtn, SIGNAL(clicked(bool)), this,
            SLOT(saveObject()));
    connect(this->openBtn, SIGNAL(clicked(bool)), this,
            SLOT(openObject()));
    connect(this->delSelectedBtn, SIGNAL(clicked(bool)), this,
            SLOT(deleteSelectedClicked()));
    connect(this->deleteAllBtn, SIGNAL(clicked(bool)), this,
            SLOT(deleteAllClicked()));
    //this->view->selectionMode();

    this->scaleDownBtn = ui->scaleDownBtn;
    this->scaleUpBtn = ui->scaleUpBtn;
    connect(this->scaleDownBtn, SIGNAL(clicked(bool)), this,
            SLOT(scaleDown()));
    connect(this->scaleUpBtn, SIGNAL(clicked(bool)), this,
            SLOT(scaleUp()));

    this->meshBtn = ui->meshBtn;
    connect(this->meshBtn, SIGNAL(clicked(bool)), this,
            SLOT(updateMesh()));

    this->aEdit = ui->aEdit;
    this->bEdit = ui->bEdit;
    this->shearBtn = ui->shearBtn;
    connect(this->shearBtn, SIGNAL(clicked(bool)), this,
            SLOT(shear()));

    this->xCheck = ui->xCheck;
    this->yCheck = ui->yCheck;
    this->reflectBtn = ui->reflectBtn;
    connect(this->reflectBtn, SIGNAL(clicked(bool)), this,
            SLOT(reflection()));
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::changeSides(int i) {
    cout << "i: " << i;
    panel->changeNumSides(i);
    cout << " value: " << panel->getSides() << endl;
    spinBoxSides->setValue(panel->getSides());

}

void MainWindow::changeColorSlot() {
    QColor lastColor = this->panel->getColor();
    this->panel->updateColor(
                QColorDialog::getColor(lastColor, this));
}

void MainWindow::sliderChange(int i0, int i1) {
    double value = this->doubleSpinBoxRadius->value() + (i1-i0)/100.0;
    cout << value << endl;
    this->doubleSpinBoxRadius->setValue(value);
    //panel->changeRadius(value);
}

void MainWindow::rotateEvent() {
    this->panel->rotate(this->angleRotEdit->text().toFloat());
}

void MainWindow::pyramidClicked()
{
    panel->drawObject(3);
    this->createListEntry();
}

void MainWindow::cubeClicked()
{
    panel->drawObject(4);
    this->createListEntry();
}

void MainWindow::cylinderClicked()
{
    panel->drawObject(5);
    this->createListEntry();
}


void MainWindow::sphereClicked()
{
    panel->drawObject(this->spinBoxSides->text().toInt());
    this->createListEntry();
}

void MainWindow::goTranslateClicked()
{
    this->panel->translate(this->xEdit->text().toDouble(),
                           this->yEdit->text().toDouble());
}

void MainWindow::rightTranslate()
{
    this->panel->translate(1,0);
}

void MainWindow::topTranslate()
{
    this->panel->translate(0,1);
}

void MainWindow::bottomTranslate()
{
    this->panel->translate(0,-1);
}

void MainWindow::leftTranslate()
{
    this->panel->translate(-1, 0);
}

void MainWindow::zoomIn()
{
    this->panel->setZoom(1.1);
}

void MainWindow::zoomOut()
{
    this->panel->setZoom(0.9);
}

void MainWindow::shear()
{
    this->panel->shear(bEdit->text().toDouble(), aEdit->text().toDouble());
}

void MainWindow::reflection()
{
    this->panel->reflection(this->xCheck->isChecked() ? -1 : 1,
                            this->yCheck->isChecked() ? -1 : 1);
}

void MainWindow::openObject()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setDefaultSuffix(".obj");
    QStringList filename;
    if(dialog.exec()) {
        filename = dialog.selectedFiles();
    }

    if(filename.size() > 0 && filename[0] != "") {
        for (QString file : filename) {
            PaintObject *obj;
            std::ifstream x;
            x.open(file.toStdString(), std::ios::in);
            if (!x.is_open()) {
                continue;
            }
            x.read(reinterpret_cast<char *>(obj), sizeof(PaintObject));
            x.close();
            QMessageBox m;
            m.setWindowTitle("Sucess!");
            m.setText("Object loaded with sucess!");
            m.exec();
        }
    }
}



void MainWindow::saveObject()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setDefaultSuffix(".obj");
    QString filename = QFileDialog::getSaveFileName(this,
        tr("Save Paint Object in a File"), "object_name.obj",
        tr("Paint Object File (*.OBJ)"));
    if(filename != "") {
        auto obj = ObjectsController::getInstance().getSelected();
        if (obj != nullptr) {
            std::ofstream x(filename.toStdString(), std::ios::binary);
            x.write(reinterpret_cast<char*>(obj), sizeof(*obj));
            x.close();
            QMessageBox m;
            m.setWindowTitle("Sucess!");
            m.setText("Object saved in file " + filename);
            m.exec();
        }
    }
}

void MainWindow::deleteSelectedClicked()
{
    //ObjectsController::getInstance().deleteSelected();

    QModelIndexList indexes = this->view->selectionModel()->selectedRows();
    for(QModelIndex i : indexes) {
        ObjectsController::getInstance().deleteSelected();
        this->model->removeRow(i.row());
    }
    int row = this->model->rowCount();
    if (row > 0) {
        cout << "deletando vazio";
        auto index = this->model->index(row - 1);
        this->view->setCurrentIndex(index);
    }
    this->panel->update();
}

void MainWindow::deleteAllClicked()
{
    while (this->model->rowCount() > 0) {
        this->deleteSelectedClicked();
    }
}

void MainWindow::scaleUp()
{
    this->panel->scale(1.1, 1.1);
}

void MainWindow::scaleDown()
{
    this->panel->scale(0.9, 0.9);
}

void MainWindow::updateMesh()
{
    QMessageBox mb;
    QLabel txt;
    QLineEdit le, le2;
    QPushButton bt;
    cout << "x";
    txt.setText(QString("Mesh Size"));
    mb.layout()->addWidget(&txt);
    mb.layout()->addWidget(&le2);
    mb.layout()->addWidget(&le);
    mb.layout()->addWidget(&bt);
    mb.exec();
    this->panel->meshSize(le.text().toInt(), le2.text().toInt());
}

void MainWindow::selectObject(QModelIndex index) {
    ObjectsController::getInstance().selectByIndex(index.row());
    this->panel->update();
}

void MainWindow::createListEntry() {
    int row = this->model->rowCount();
    this->model->insertRow(row);
    auto index = this->model->index(row);
    this->view->setCurrentIndex(index);
    this->view->edit(index);
}



