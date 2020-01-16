//
// Created by aharon on 16/01/2020.
//

#include "General.h"
template<class T, class S>
Searcher<T,S>::Searcher() {
  openList = new priority_queue<State<T>>;
  evaluatedNodes=0;
}

template<class T, class S>
int Searcher<T, S>::listSize() {
  return openList.size();
}

template<class T, class S>
int Searcher<T,S>::NodesEvaluated() {
  return evaluatedNodes;
}

