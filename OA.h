//
// Created by omer on 1/24/20.
//

#ifndef EX4_OA_H
#define EX4_OA_H

#include "OA.h"
#include "Solver.h"
#include "Searcher.h"
#include "Matrix.h"



template<class P, class S, class T>
class OA : public Solver<P, S> {

private:
    Searcher<T, S>* searcher;
public:
    OA(Searcher<T,S>* searcher1) {
        this->searcher=searcher1;
    }

    S solve(P problem) { // P is a matrix in our case

        Searchable<Point> *able;
        able = new Matrix(problem);

        S solution = this->searcher->search(able);// solving the problem by search -> store the solution
        return solution;// adapt the solution to the problem's type
    }

    virtual ~OA() = default;
};

#endif //EX4_OA_H
