#include "shapes.h"

// SHAPE CLASS CODE

Shape::Shape() : shapeID(0) {}

Shape::Shape(int id) : shapeID(id) {}

Shape::Shape(const Shape &copy)
{ shapeID = copy.getID(); }

Shape::~Shape() {}

int Shape::getID() const
{ return shapeID; }

void Shape::setID(int num)
{ shapeID = num; }
