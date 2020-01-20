//
// Created by yaffa on 1/17/20.
//

#include "General.h"
Matrix::Matrix(matrix f, State<Point> ini, State<Point> g) : field(f), initial(ini), goal(g) {}

State<Point> Matrix::getInitialState() {
  return this->initial;
}

bool Matrix::isGoalState(State<Point> current) {
  return (this->goal).equals(current);
}


vector<State<Point>> Matrix::getAllPossibleState(State<Point> current) {
    vector<State<Point>> possibleState;

  State<Point> t5(Point(current.getStatus().getX() - 1, current.getStatus().getY()),
                  current, current.GetCost() + pointCost(t5));




    State<Point> o1 = new State<Point>(new Point(current.getStatus().getX() - 1, current.getStatus().getY()),
                                current, current.GetCost() + pointCost(o1));
    possibleState.push_back(o1);

    State<Point> o2 = new State(new Point(current.getStatus().getX() + 1, current.getStatus().getY()),
                                current, current.GetCost() + pointCost(o1));
    possibleState.push_back(o1);

    State<Point> o3 = new State(new Point(current.getStatus().getX(), current.getStatus().getY() - 1),
                                current, current.GetCost() + pointCost(o1));
    possibleState.push_back(o1);

    State<Point> o4 = new State(new Point(current.getStatus().getX(), current.getStatus().getY() + 1),
                                current, current.GetCost() + pointCost(o1));
    possibleState.push_back(o1);

    return possibleState;
}

int Matrix::pointCost(State<Point> current) {
  return field[current.getStatus().getX()][current.getStatus().getY()];
}

vector<string> Matrix::adaptSolution(vector<State<Point>> stateVector) {
  vector<string> strVector;
  for (int i = 0; i < (stateVector.size() - 1); i++) {
    string str = direction(stateVector[i], stateVector[i + 1]);
    strVector.push_back(str);
  }
  return strVector;

}

string Matrix::direction(State<Point> s1, State<Point> s2) {

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
        return "up";
    }
    if (y2 < y1) {
        return "down";
    }
}