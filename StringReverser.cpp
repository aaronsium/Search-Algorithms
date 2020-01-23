//
// Created by yaffa on 1/15/20.
//

#include "StringReverser.h"

string StringReverser:: solve (string problem){
    string solution = " ";
    for(int i = problem.length()-1; i >= 0; i++){
        solution += problem[i];
    }
    return problem;
}
