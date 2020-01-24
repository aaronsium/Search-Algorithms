//
// Created by omer on 1/23/20.
//

#ifndef EX4_STRINGREVERSER_H
#define EX4_STRINGREVERSER_H

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
#include "Solver.h"

using namespace std;
using namespace std::literals::chrono_literals;
typedef vector<vector<int>> matrix;
typedef vector<string> strVector;


class StringReverser : public Solver<string, string> {

public:
    virtual string solve (string problem){
        string solution = " ";
        for(int i = problem.length()-1; i >= 0; i++){
            solution += problem[i];
        }
        return problem;
    }

    ~StringReverser() override {}
};

#endif //EX4_STRINGREVERSER_H
