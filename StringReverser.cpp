//
// Created by omer on 1/15/20.
//

#include "General.h"

StringReverser::string solve (string problem){
    string solution = " ";
    for(int i = problem.length()-1; i >= 0; i++){
        solution += problem[i];
    }
    return problem;
}
