#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "transformationtype.h"

class Transformation
{
    double data1, data2, data3;
    TransformationType type;

public:
    Transformation(TransformationType type, double data1, double data2,
                   double data3 = 0);
    virtual ~Transformation();

    double getData1() const noexcept {
        return this->data1;
    }
    double getData2() const noexcept {
        return this->data2;
    }
    double getData3() const noexcept {
        return this->data3;
    }

    TransformationType getType() const noexcept {
        return this->type;
    }

};

#endif // TRANSFORMATION_H
