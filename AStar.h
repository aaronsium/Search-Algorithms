//
// Created by aharon on 23/01/2020.
//

#ifndef EX4__ASTAR_H_
#define EX4__ASTAR_H_

#include "Searcher.h"
#include "State.h"
#include "Searchable.h"
#include <list>
#include <vector>
using namespace std;
template<class T>
struct comparator {
    comparator(State<T> g) { this->goal = g; }
    State<T> goal;
    bool operator()(const State<T> &l, const State<T> &r) {
        int x = l.getStatus().getX() - goal.getStatus().getX();
        int y = l.getStatus().getY() - goal.getStatus().getY();
        if(x < 0){
            y *= -1;
        }
        if(x < 0){
            x *= -1;
        }
        int l_heuristic = y-x;

        x = r.getStatus().getX() - goal.getStatus().getX();
        y = r.getStatus().getY() - goal.getStatus().getY();
        if(x < 0){
            y *= -1;
        }
        if(x < 0){
            x *= -1;
        }
        int r_heuristic = y-x;

        int fn1 = l.GetCost() + l_heuristic;
        int fn2 = r.GetCost() + r_heuristic;
        return (fn1 > fn2);
    }
};

template<class T, class S>
class AStar : public Searcher<T, S> {

private:
    list<State<T>> closed;

public:

    virtual ~AStar() = default;

    S search(Searchable<T> *s) {
        priority_queue<State<T>, vector<State<T>>, comparator<T>> openList(comparator<T>(s->getGoalState()));


        openList.push(s->getInitialState());
        while (!openList.empty()) {
            State<T> state = openList.top();
            openList.pop();
            this->closed.push_back(state);

            if (s->isGoalState(state)) {
                return s->adaptSolution(backTrace());
            }


            list<State<T>> options = s->getAllPossibleStates(state.copy());
            typename std::list<State<T>>::iterator opt;
            for (opt = options.begin(); opt!=options.end(); ++opt) {
                //iterator to check if option in closed
                typename list<State<T>>::iterator inClosed;
                if ((!std::count(closed.begin(), closed.end(), (*opt)))){
                    openList.push(*opt);
                }
            }

        }
    }

    vector<State<T>> backTrace() {
        typename std::list<State<T>> ::iterator element;
        vector<State<T>> trace;
        for (element = closed.begin(); element!=closed.end(); ++element) {
            this->SetEvaluatedNodes(this->evaluatedNodes + 1);
            trace.push_back(*element);
        }

        cout<< "A* - evaluatedNodes : "<<this->evaluatedNodes <<endl;
        return trace;
    }
};

#endif //EX4__ASTAR_H_