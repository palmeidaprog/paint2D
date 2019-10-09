#ifndef PAINTOBJECT_H
#define PAINTOBJECT_H

#include <vector>
#include <algorithm>
#include <QColor>
#include <iostream>
#include <memory>
#include "transformation.h"

using std::vector;
using std::pair;
using std::unique_ptr;
using std::cout;
using std::endl;

class PaintObject{
    unsigned id;
    vector<Transformation *> transformations;
    double sides;
    //vector<unique_ptr< pair<double, double>> > points;
    int transformation_index, points_index;
    QColor color;

public:
    PaintObject(int numberOfSides, const QColor &color, unsigned id = 0)
          noexcept;
    virtual ~PaintObject() noexcept;

    bool hasNextTransformation();
    Transformation &nextTransformation();
    void addTranslation(double x, double y);
    void addShear(double b, double a);
    void addRotation(double angle);
    void addReflection(double x, double y);
    void addScale(double x, double y);
    PaintObject &setSelected();
    void setColor(const QColor &color);
    const QColor &getColor() const;
    void resetIndexes();

    inline void setId(unsigned id) {
        this->id = id;
    }

    inline unsigned getId() const {
        return this->id;
    }

    inline int numberOfSides() const {
        return this->sides;
    }
};

#endif // PAINTOBJECT_H
