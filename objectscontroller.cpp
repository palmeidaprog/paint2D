#include "objectscontroller.h"

ObjectsController::ObjectsController() : obj_index(0), selected(nullptr),
    lastId(0), selectedId(-1) {

}

ObjectsController::~ObjectsController()  {
    for (auto obj : this->objects) {
        delete obj;
    }
    this->objects.clear();
}

void ObjectsController::selectByIndex(size_t index)
{
    if (index < this->objects.size()) {
        this->selected = this->objects[index];
    }
}

void ObjectsController::updateSelected(unsigned newSelectedId)
{
    this->selectedId = newSelectedId;
    for (auto obj : this->objects) {
        if (obj->getId() == this->selectedId) {
            this->selected = obj;
            break;
        }
    }
}

void ObjectsController::deleteSelected()
{
    bool found = false;
    cout << "entrou del " << endl;
    for (size_t i = 0; i < this->objects.size(); i++) {
        if (this->objects[i]->getId() == this->selected->getId()) {
            cout << "achou " << endl;
            this->objects.erase(this->objects.begin() + i);
            found = true;
            break;
        }
    }
    if (found) {
        size_t last = this->objects.size() - 1;
        this->selected = (last >= 0) ? this->objects[last] : nullptr;
    }
}

ObjectsController &ObjectsController::addObject(PaintObject *obj)
{
    cout << "adicionado" << endl;
    this->selectedId = this->lastId;
    obj->setId(this->lastId++);
    this->selected = obj;
    this->objects.push_back(obj);
    return *this;
}

void ObjectsController::addTranslation(double x, double y, double z)
{
    this->selected->addTranslation(x, y, z);
}

void ObjectsController::addRotation(double angle, double axis)
{
    this->selected->addRotation(angle, axis);
}

void ObjectsController::addScale(double x, double y, double z)
{
    this->selected->addScale(x, y, z);
}

void ObjectsController::addReflection(double x, double y)
{
    this->selected->addReflection(x, y);
}

void ObjectsController::addShear(double b, double a)
{
    this->selected->addShear(b, a);
}

PaintObject *ObjectsController::getNextObject()
{
    if (this->obj_index == this->objects.size()) {
        this->obj_index++;
        return selected;
    } else {
        auto returnObj = this->objects[this->obj_index++];
        return (returnObj->getId() != this->selectedId) ? returnObj :
              this->getNextObject();
    }
}

bool ObjectsController::hasNextObject()
{
    size_t s = static_cast<size_t>(this->obj_index),
            s2 = this->objects.size();
    cout << s << "> "  << s2;
    return static_cast<size_t>(this->obj_index) <= this->objects.size();
}

void ObjectsController::setColor(const QColor &color)
{
    if (this->selected != nullptr) {
        this->selected->setColor(color);
    }
}

QStringList ObjectsController::getList()
{
    QStringList list;
    for (auto obj : this->objects) {
        std::stringstream s;
        s << obj->getId() << " - " << obj->numberOfSides() << " sides";
        list << QString::fromStdString(s.str());
    }
    return list;
}

ObjectsController &ObjectsController::getInstance() {
    static ObjectsController instance;
    return instance;
}
