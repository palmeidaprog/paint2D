#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "transformationtype.h"

class Transformation
{
    double data1, data2;
    TransformationType type;

public:
    Transformation(TransformationType type, double data1, double data2);
    virtual ~Transformation();

    double getData1() const noexcept {
        return this->data1;
    }
    double getData2() const noexcept {
        return this->data2;
    }

    TransformationType getType() const noexcept {
        return this->type;
    }

};

#endif // TRANSFORMATION_H
