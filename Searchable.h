//
// Created by omer on 1/24/20.
//

#ifndef EX4_SEARCHABLE_H
#define EX4_SEARCHABLE_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <bits/stdc++.h>
#include <arpa/inet.h>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <chrono>
#include <thread>
#include <mutex>
#include <cstddef>
#include <stdlib.h>
#include <string>
#include <functional>
#include "Searchable.h"
#include "Point.h"
#include "State.h"
using namespace std;
using namespace std::literals::chrono_literals;
typedef vector<vector<int>> matrix;
typedef vector<string> strVector;


template<class T>
class Searchable {
protected:
    State<Point> initial;
    State<Point> goal;
public:
    Searchable();
    virtual State<T> getInitialState() = 0;
    virtual bool isGoalState(State<T>) = 0;
    virtual list<State<T>> getAllPossibleStates(State<T> current) = 0;
    virtual int NodesEvaluated() = 0;
    virtual vector<string> adaptSolution(vector<State<Point>> stateVector)=0;
    virtual ~Searchable() = default;
};

#endif //EX4_SEARCHABLE_H
