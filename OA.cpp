//
// Created by aharon on 18/01/2020.
//
#include "General.h"

template<class P, class S, class T>
 OA<P, S, T>::OA(Searcher<P,S>* searcher1) {
 this->searcher=searcher1;
}

template<class P, class S, class T>
S OA<P, S, T>:: solve(P problem) { // P is a matrix in our case
 S solution = this->searcher->search(problem);// solving the problem by search -> store the solution
 return solution;// adapt the solution to the problem's type
}

