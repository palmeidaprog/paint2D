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
    QToolButton *colorBtn, *rotateBtn, *makeTriangleBtn, *makeSquareBtn,
    *makePolygonBtn, *upBtn, *downBtn, *rightBtn, *leftBtn, *zoomInBtn,
    *zoomOutBtn, *scaleUpBtn, *scaleDownBtn, *meshBtn;
    QSlider *scaleSlider;
    QDial *dialRotation;
    QLineEdit *angleRotEdit, *xEdit, *yEdit;
    QPushButton *goTransBtn, *delSelectedBtn, *deleteAllBtn, *openBtn,
    *saveBtn;
    QStringListModel *model;
    QListView *view;

    QColor getColor(const QColor &startigColor);

public slots:
    void changeSides(int i);
    void changeColorSlot();
    void sliderChange(int i0, int i1);
    void rotateEvent();
    void triangleClicked();
    void squareClicked();
    void polygonClicked();
    void goTranslateClicked();
    void rightTranslate();
    void topTranslate();
    void bottomTranslate();
    void leftTranslate();
    void zoomIn();
    void zoomOut();

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
