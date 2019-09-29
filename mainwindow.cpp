#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    panel = ui->panel;
    doubleSpinBoxRadius = ui->doubleSpinBoxRadius;
    spinBoxSides = ui->spinBoxSides;
    colorsCombo = ui->colorsCombo;
    spinBoxSides->setValue(3);
    this->colorBtn = this->ui->colorBtn;
    doubleSpinBoxRadius->setValue(2.0);

    //events
    connect(colorsCombo, SIGNAL(activated(int)), panel,
            SLOT(changeColors(int)));
    connect(doubleSpinBoxRadius, SIGNAL(valueChanged(double)), panel,
            SLOT(changeRadius(double)));
    connect(spinBoxSides, SIGNAL(valueChanged(int)), this,
            SLOT(changeSides(int)));
    connect(this->colorBtn, SIGNAL(clicked()), this,
            SLOT(changeColorSlot()));
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


