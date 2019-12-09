#ifndef OBJECTSCONTROLLER_H
#define OBJECTSCONTROLLER_H

#include "paintobject.h"
#include <sstream>
#include <iostream>

using std::cout;
using std::endl;

class ObjectsController
{
    vector<PaintObject *> objects;
    ObjectsController();
    unsigned selectedId, lastId;
    PaintObject *selected;
    int obj_index;

public:
    ObjectsController(ObjectsController const&) = delete;
    void operator=(ObjectsController const&) = delete;
    static ObjectsController &getInstance();

    virtual ~ObjectsController();

    inline PaintObject *getSelected() const noexcept {
        return this->selected;
    }

    void selectByIndex(size_t index);

    void updateSelected(unsigned newSelectedId);
    void deleteSelected();
    ObjectsController &addObject(PaintObject *obj);
    void addTranslation(double x, double y, double z);
    void addRotation(double angle, double axis);
    void addScale(double x, double y);
    void addReflection(double x, double y);
    void addShear(double b, double a);
    PaintObject *getNextObject();
    bool hasNextObject();
    void setColor(const QColor &color);
    QStringList getList();
    void resetIndexing() {
        this->obj_index = 0;
    }

};

#endif // OBJECTSCONTROLLER_H
