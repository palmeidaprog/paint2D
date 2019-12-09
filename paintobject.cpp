#include "paintobject.h"



PaintObject::PaintObject(int numberOfSides, const QColor &color, unsigned id)
    noexcept : id(id), sides(numberOfSides), transformation_index(-1),
    points_index(0), color(color) {

}

PaintObject::~PaintObject() noexcept {
    for (auto transformation : this->transformations) {
        delete transformation;
    }
}


bool PaintObject::hasNextTransformation()
{
    //cout << "trans: " << this->transformation_index << endl;
    return this->transformation_index >= 0;
}

Transformation &PaintObject::nextTransformation()
{
    if (!this->hasNextTransformation()) {
        this->transformation_index = this->transformations.size()-1;
    }
    return *this->transformations[this->transformation_index--];
}

void PaintObject::addTranslation(double x, double y, double z)
{
    this->transformations.push_back(new Transformation(
                                            TransformationType::TRANSLATE, x,
                                        y, z));
    this->resetIndexes();
}

void PaintObject::addShear(double b, double a)
{
    this->transformations.push_back(new Transformation(
                                        TransformationType::SHEAR, b, a));
    this->resetIndexes();

}

void PaintObject::addRotation(double angle, double axis)
{
    this->transformations.push_back(new Transformation(
                                            TransformationType::ROTATE, angle,
                                        axis));
    this->resetIndexes();
}

void PaintObject::addReflection(double x, double y)
{
    this->transformations.push_back(new Transformation(
                                        TransformationType::REFLECTION, x, y));
    this->resetIndexes();
}

void PaintObject::addScale(double x, double y)
{
    this->transformations.push_back(new Transformation(
                                        TransformationType::SCALE, x, y));
    this->resetIndexes();
}


void PaintObject::setColor(const QColor &color)
{
    this->color = color;
}

const QColor &PaintObject::getColor() const
{
    return this->color;
}

void PaintObject::resetIndexes()
{
    //this->points_index = 0;
    this->transformation_index = this->transformations.size()-1;
    //cout << "New trans:" << this->transformation_index << endl;
}

