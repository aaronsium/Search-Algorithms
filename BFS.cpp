//
// Created by aharon on 18/01/2020.
//

#include "General.h"

template<class T, class S>
vector<State<T>> BFS<T, S>::search(Searchable<T> *searchable) {
  State<T> start = searchable->getInitialState();
  queue<State<T>> q;
  q.push(start);
  visited.push_back(start);
  while (!q.empty()) {
    State<T> current = q.front();
    q.pop();
    this->SetEvaluatedNodes(this->evaluatedNodes + 1);// add 1 to node's counter
    if (searchable->isGoalState(current)) {
      return visited;
    }
    list<State<T>> options = searchable->getAllPossibleStates(current);
    typename std::list<State<T>>::iterator opt;
    for (opt = options.begin(); opt!=options.end(); ++opt) {
      if ((!std::count(visited.begin(), visited.end(), opt))) {
        visited.push_back(*opt);
        q.push(*opt);
      }
    }
  }
}

template<class T, class S>
list<State<T>> BFS<T, S>::backTrace() {
  return visited;
}

void TemporaryFunction (){
  BFS<Point,vector<string>> x;
}