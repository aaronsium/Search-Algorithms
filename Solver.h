//
// Created by omer on 1/24/20.
//

#ifndef EX4_SOLVER_H
#define EX4_SOLVER_H

/**
 * Solver Interface
 */

template<class P, class S>
class Solver {

public:
    virtual S solve(P problem) = 0;
    virtual ~Solver() {}
};

#endif //EX4_SOLVER_H
