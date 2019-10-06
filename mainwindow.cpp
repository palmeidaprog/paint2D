#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    panel = ui->panel;
    doubleSpinBoxRadius = ui->doubleSpinBoxRadius;
    spinBoxSides = ui->spinBoxSides;
    //colorsCombo = ui->colorsCombo;
    spinBoxSides->setValue(3);
    scaleSlider = ui->scaleSlider;
    this->colorBtn = this->ui->colorBtn;
    doubleSpinBoxRadius->setValue(2.0);
    dialRotation = ui->dialRotation;

    //events
//    connect(colorsCombo, SIGNAL(activated(int)), panel,
//            SLOT(changeColors(int)));
    connect(doubleSpinBoxRadius, SIGNAL(valueChanged(double)), panel,
            SLOT(changeRadius(double)));
    connect(spinBoxSides, SIGNAL(valueChanged(int)), this,
            SLOT(changeSides(int)));
    connect(this->colorBtn, SIGNAL(clicked()), this,
            SLOT(changeColorSlot()));
    connect(this->scaleSlider, SIGNAL(rangeChanged(int,int)), this,
            SLOT(sliderChange(int, int)));

    connect(this->dialRotation, SIGNAL(sliderMoved(int)), panel,
            SLOT(rotationChanged(int)));
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



