//
// Created by aharon on 17/01/2020.
//

#include "General.h"

SolutionMatrix::SolutionMatrix(State<Point> stateVec1) {
  this->stateVec = stateVec1;
}

vector<string> SolutionMatrix::toMatrix(State<Point> s1, State<Point> s2) {
  double x1 = s1.GetStatus().GetX();
  double y1 = s1.GetStatus().GetY();
  double x2 = s2.GetStatus().GetX();
  double y2 = s2.GetStatus().GetY();

  bool right = false, left = false, up = false, down = false;

  if (x2 > x1) {
    strVec.push_back("right");
  }
  if (x2 < x1) {
    strVec.push_back("left");
  }
  if (y2 > y1) {
    strVec.push_back("up");
  }
  if (y2 > y1) {
    strVec.push_back("down");

  }

}