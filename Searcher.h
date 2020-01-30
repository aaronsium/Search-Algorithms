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
  double evaluatedNodes;

 public:
  Searcher() {
    evaluatedNodes = 0;
  }

  virtual S search(Searchable<T> *searchable) = 0;
  double NodesEvaluated() {
    return evaluatedNodes;
  }

  void SetEvaluatedNodes(double evaluated_nodes) {
    evaluatedNodes = evaluated_nodes;
  }

  virtual ~Searcher() = default;
};

#endif //EX4_SEARCHER_H
