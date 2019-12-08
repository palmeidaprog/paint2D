#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QComboBox>
#include <QLineEdit>
#include <QToolButton>
#include <QPushButton>
#include <QColorDialog>
#include <QSlider>
#include <QListView>
#include <QStringListModel>
#include <QDial>
#include <QFileDialog>
#include <QMessageBox>
#include "openglpanel.h"
#include <QCheckBox>
#include <fstream>

namespace Ui {
class MainWindow;
}
class OpenGLPanel;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    OpenGLPanel *panel;
    QSpinBox *spinBoxSides;
    QDoubleSpinBox *doubleSpinBoxRadius;
    QComboBox *colorsCombo;
    QCheckBox *xCheck, *yCheck;
    QToolButton *colorBtn, *rotateBtn, *makeConeBtn, *makeCubeBtn,
    *makeCylinderBtn, *makeSphereBtn, *makePyramidBtn, //*makePolygonBtn,
    *upBtn, *downBtn, *rightBtn, *leftBtn, *zoomInBtn,
    *zoomOutBtn, *scaleUpBtn, *scaleDownBtn, *meshBtn;
    QSlider *scaleSlider;
    QDial *dialRotation;
    QLineEdit *angleRotEdit, *xEdit, *yEdit, *aEdit, *bEdit;
    QPushButton *goTransBtn, *delSelectedBtn, *deleteAllBtn, *openBtn,
    *reflectBtn, *shearBtn, *saveBtn;
    QStringListModel *model;
    QListView *view;

    QColor getColor(const QColor &startigColor);

public slots:
    void changeSides(int i);
    void changeColorSlot();
    void sliderChange(int i0, int i1);
    void rotateEvent();
    void pyramidClicked();
    void cubeClicked();
    void cylinderClicked();
    void sphereClicked();
    void goTranslateClicked();
    void rightTranslate();
    void topTranslate();
    void bottomTranslate();
    void leftTranslate();
    void zoomIn();
    void zoomOut();
    void shear();
    void reflection();

    void openObject();
    void saveObject();
    void deleteSelectedClicked();
    void deleteAllClicked();
    void scaleUp();
    void scaleDown();
    void updateMesh();

    // list view
    void selectObject(QModelIndex index);
    void createListEntry();
};

#endif // MAINWINDOW_H
