/********************************************************************/
/*                        SHAPEMANIP.CPP                            */
/********************************************************************/
/* This source files contains class definitions for move() and      */
/* draw() since they are directly manipulaing the object from       */
/* within the 2D rendering program.  Class definitions are included */
/* in shapes.cpp                                                    */
/********************************************************************/

#include "shapes.h"

/******************** SHAPE CLASS CODE ********************/

void Shape::draw() const {}
void Shape::move() const {}


/******************** POLYSHAPE CLASS CODE ********************/

// No draw() or move() function definitions for this class.


/******************** ORIGINBASEDSHAPE CLASS CODE ********************/

// Draw() functions are defined by the individual shape classes
void OriginBasedShape::move() const {}

/******************** LINE CLASS CODE ********************/

void Line::draw() const {}
void Line::move() const {}


/******************** POLYLINE CLASS CODE ********************/

void Polyline::draw() const {}
void Polyline::move() const {}


/******************** POLYGON CLASS CODE ********************/

void Polygon::draw() const {}
void Polygon::move() const {}


/******************** RECTANGLE CLASS CODE ********************/

void Rectangle::draw() const {}
// Move() function is defined by OriginBasedShape


/******************** SQUARE CLASS CODE ********************/

// Square inherits Rectangle's move() and draw() functions.


/******************** ELLIPSE CLASS CODE ********************/

void Ellipse::draw() const {}
// Move() function is defined by OriginBasedShape


/******************** CIRCLE CLASS CODE ********************/

// Circle inherits Ellipse's move() and draw() functions.


/******************** TEXT CLASS CODE ********************/

void Text::draw() const {}
void Text::move() const {}
