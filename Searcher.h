//
// Created by omer on 1/24/20.
//

#ifndef EX4_SEARCHER_H
#define EX4_SEARCHER_H

#include "Searcher.h"
#include "Searchable.h"

template<class T, class S>

class Searcher {
protected:
    int evaluatedNodes;

public:
    Searcher();
    virtual S search(Searchable<T>* searchable) = 0;
    int NodesEvaluated();
    virtual ~Searcher() = default;
    void SetEvaluatedNodes(int evaluated_nodes);
};

#endif //EX4_SEARCHER_H
