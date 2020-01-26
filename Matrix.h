//
// Created by aharon on 24/01/2020.
//

#ifndef EX4__MATRIX_H_
#define EX4__MATRIX_H_
#include "Searchable.h"
#include "Point.h"
#include "State.h"

typedef vector<vector<int>> matrix;

class Matrix : public Searchable<Point> {
 private:
  matrix field;
  State<Point> initial;
  State<Point> goal;

 public:
  ~Matrix() override {};

  //////////////////////////////////////////////////////////////
  Matrix(){}
  Matrix(matrix f):
      field(f),
      initial(State<Point> (Point(f[0][f[0].size()-2], f[1][f[1].size()-2]), NULL, 0)),
      goal(State<Point> (Point(f[0][f[0].size()-1], f[1][f[1].size()-1]), NULL, 0))
  {}

  State<Point> getInitialState() {
    return this->initial;
  }

  bool isGoalState(State<Point> current) {
    return (this->goal).equals(current);
  }


  list<State<Point>> getAllPossibleStates(State<Point>* current) {
    list<State<Point>> possibleState;

      if((current->getStatus().getX() - 1) >= 0) {
          Point p1(current->getStatus().getX() - 1, current->getStatus().getY());
          if(pointCost(p1) != -1){
              State<Point> o1(p1, current, current->GetCost() + pointCost(p1));
              possibleState.push_back(o1);
          }
      }

      if((current->getStatus().getX() + 1) < this->field.size()) {
          Point p2(current->getStatus().getX() + 1, current->getStatus().getY());
          if(pointCost(p2) != -1){
              State<Point> o2(Point(p2), current, current->GetCost() + pointCost(p2));
              possibleState.push_back(o2);
          }
      }

      if((current->getStatus().getY() - 1) >= 0) {
          Point p3(current->getStatus().getX(), current->getStatus().getY() - 1);
          if(pointCost(p3) != -1) {
              State<Point> o3(p3, current, current->GetCost() + pointCost(p3));
              possibleState.push_back(o3);
          }
      }

      if((current->getStatus().getY() + 1)< this-> field[0].size()) {
          Point p4(current->getStatus().getX(), current->getStatus().getY() + 1);
          if(pointCost(p4) != -1) {
              State<Point> o4(Point(p4), current, current->GetCost() + pointCost(p4));
              possibleState.push_back(o4);
          }
      }

      return possibleState;
  }

  int pointCost(Point current) {
    return field[current.getX()][current.getY()];
  }

  vector<string> adaptSolution(vector<State<Point>> stateVector) {
    vector<string> strVector;
    for (int i = 0; i < (stateVector.size() - 1); i++) {
      string str = direction(stateVector[i], stateVector[i + 1]);
      strVector.push_back(str);
    }
    return strVector;

  }

  string direction(State<Point> s1, State<Point> s2) {

    double x1 = s1.getStatus().getX();
    double y1 = s1.getStatus().getY();
    double x2 = s2.getStatus().getX();
    double y2 = s2.getStatus().getY();

    if (x2 > x1) {
      return "right";
    }
    if (x2 < x1) {
      return "left";
    }
    if (y2 > y1) {
      return "down";
    }
    if (y2 < y1) {
      return "up";
    }
  }

  int NodesEvaluated() {///////סתם מימוש
    return 1;
  }




};

#endif //EX4__MATRIX_H_
