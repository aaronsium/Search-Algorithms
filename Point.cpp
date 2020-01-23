//
// Created by aharon on 16/01/2020.
//

#include "General.h"

Point::Point(double x1, double y1) {
  this->x = x1;
  this->y = y1;
}

double Point:: getX(){
  return this->x;
}

double Point:: getY(){
  return this->y;
}

bool Point::equals(Point other) const {
  return (this->x == other.getX())&&(this->y == other.getY());
}

Point& Point::operator=(const Point& s1 ) {
  this->x = s1.x;
  this->y = s1.y;
  return (*this);
}