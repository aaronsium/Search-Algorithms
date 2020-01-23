//
// Created by omer on 1/24/20.
//

#ifndef EX4_OA_H
#define EX4_OA_H

#include "OA.h"
#include "Solver.h"
#include "Searcher.h"

template<class P, class S, class T>
class OA : public Solver<P, S> {

private:
    Searcher<T, S>* searcher;
public:
    OA(Searcher<T, S>* searcher1);
    S solve(P problem);
    virtual ~OA() = default;
};

#endif //EX4_OA_H
