//
// Created by omer on 1/17/20.
//

#include "General.h"
Matrix::Matrix(matrix f, State<Point> ini, State<Point> g) : field(f), initial(ini), goal(g) {}

State<Point> Matrix::getInitialState() {
  return this->initial;
}

bool Matrix::isGoalState(State<Point> current) {
  return (this->goal).compare(current);
}

vector<State<Point>> Matrix::getAllPossibleState(State<Point> current) {
  vector<State<Point>> possibleState;
  possibleState.push_back(new State<Point>(new Point(current.getX - 1, current.getY)));
  possibleState.push_back(new State<Point>(new Point(current.getX + 1, current.getY)));
  possibleState.push_back(new State<Point>(new Point(current.getX, current.getY - 1)));
  possibleState.push_back(new State<Point>(new Point(current.getX, current.getY + 1)));

  return possibleState.push_back;
}

int Matrix::getCost(State<Point> current) {
  return matrix[current.getX][current.getY];
}