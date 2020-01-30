//
// Created by aharon on 24/01/2020.
//

#ifndef EX4__BFS_H_
#define EX4__BFS_H_

#include "Searcher.h"
#include "State.h"
#include "Searchable.h"
#include <vector>

template<class T, class S>
class BFS : public Searcher<T, S> {

 private:
  vector<State<T>> visited;
 public:
  virtual ~BFS() = default;
////////////////////////////////////////////////////////////////////////////////
  S search(Searchable<T> *searchable) {

    State<T> start = searchable->getInitialState();
    list<State<T>> q;
    q.push_back(start);
    int i = 0;
    while (!q.empty()) {
      i++;
      State<T> current = q.front();
      q.pop_front();
      visited.push_back(current);
      if (searchable->isGoalState(current)) {
        cout << "Cost:" << current.GetCost() << endl;
        vector<State<T>> traceVector = backTrace(current);
        return searchable->adaptSolution(traceVector);
      }
      list<State<T>> options = searchable->getAllPossibleStates(current.copy());
      typename std::list<State<T>>::iterator opt;
      for (opt = options.begin(); opt!=options.end(); ++opt) {
        if ((!std::count(visited.begin(), visited.end(), (*opt)))) {
          if ((!std::count(q.begin(), q.end(), (*opt)))) {
            q.push_back(*opt);
          }
        }
      }
    }
  }

  vector<State<T>> backTrace(State<T> state) {
    list<State<T>> trace;
    trace.push_back(state);
    State<T> *previous = state.getPrevious();

    while (previous!=NULL) {
      trace.push_back(*previous);
      previous = previous->getPrevious();
      this->SetEvaluatedNodes(this->evaluatedNodes + 1);
    }
    cout << "BFS - evaluatedNodes : " << this->evaluatedNodes << endl;
    cout << endl;

    vector<State<T>> traceVector;
    while (!trace.empty()) {
      traceVector.push_back(trace.back());
      trace.pop_back();
    }

    return traceVector;
  }

//void TemporaryFunction3 (){
//  BFS<Point,vector<string>> x;
//}




};

#endif //EX4__BFS_H_
