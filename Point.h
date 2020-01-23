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
    Point();
    Point(double x, double y);
    double getX();
    double getY();
    bool equals(Point other) const;
    Point& operator=(const Point& s1 ) ;

};

#endif //EX4_POINT_H
