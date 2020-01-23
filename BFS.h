//
// Created by aharon on 24/01/2020.
//

#ifndef EX4__BFS_H_
#define EX4__BFS_H_

#include "Searcher.h"
#include "State.h"
#include "searchable.h"
#include <vector>



template<class T, class S>
class BFS : public Searcher<T, vector<State<T>>> {

private:
vector<State<T>> visited;
public:
virtual ~BFS() = default;
////////////////////////////////////////////////////////////////////////////////
vector<State<T>> search(Searchable<T> *searchable) {
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
      if ((!std::count(visited.begin(), visited.end(), (*opt)))) {
        visited.push_back(*opt);
        q.push(*opt);
      }
    }
  }
}

vector<State<T>>backTrace() {
  return visited;
}

void TemporaryFunction3 (){
  BFS<Point,vector<string>> x;
}




};



#endif //EX4__BFS_H_
