//
// Created by omer on 1/24/20.
//

#ifndef EX4_POINT_H
#define EX4_POINT_H

class Point {

 private:
  double x;
  double y;

 public:
  Point() {};
  Point(double x1, double y1) {
    this->x = x1;
    this->y = y1;
  }

  Point *copy() {
    return new Point(this->x, this->y);
  }

  double getX() {
    return this->x;
  }

  double getY() {
    return this->y;
  }

  bool equals(Point other) const {
    return (this->x==other.getX()) && (this->y==other.getY());
  }

  Point &operator=(const Point &s1) {
    this->x = s1.x;
    this->y = s1.y;
    return (*this);
  }
};

#endif //EX4_POINT_H
