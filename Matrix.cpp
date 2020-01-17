//
// Created by omer on 1/17/20.
//

Matrix:: Matrix(matrix f, State ini, State g): field(f), initial(ini), goal(g){}

State Matrix:: getInitialState(){
    return this->initial;
}

bool Matrix:: isGoalState(State current){
    return (this->goal).compare(current);
}

vector<State> Matrix:: getAllPossibleState(State current){
    vector<State> possibleState;
    possibleState.push_back(new State(new Point(current.getX -1, current.getY)));
    possibleState.push_back(new State(new Point(current.getX +1, current.getY)));
    possibleState.push_back(new State(new Point(current.getX, current.getY -1)));
    possibleState.push_back(new State(new Point(current.getX, current.getY +1)));

    return possibleState.push_back;
}

int Matrix:: getCost(Point current){
    return matrix[current.getX][current.getY];
}