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
// comparator for min priority_queue<
template<class T, class S>
class AStar : public Searcher<T, S> {

 private:
  list<State<T>> closed;
  priority_queue<State<T>, vector<State<T>>, compare<T>> openList;
  list<State<T>> trace;
  list<State<T>> opened;

 public:
  virtual ~AStar() = default;

  /////////////////////////////////////////////////////////////////////////
  S search(Searchable<T> *s) {
    this->openList.push(s->getInitialState());

    while (!this->openList.empty()) {
      State<T> state = this->openList.top();
      this->openList.pop();

      if (s->isGoalState(state)) {
        vector<State<T>> traceVector;
        while (!this->trace.empty()) {
          traceVector.push_back(this->trace.back());
          this->trace.pop_back();
        }
        return s->adaptSolution(traceVector);
      }

      while (!openList.empty()) {
        opened.push_back(openList.top());
        openList.pop();
      }

      list<State<T>> PossibleStates = s->getAllPossibleStates(state);
      while (!PossibleStates.empty()) {
        State<T> option = PossibleStates.front();
        PossibleStates.pop_front();

        //iterator to check if option in open
        typename list<State < T>>
        ::iterator inOpen;
        for (inOpen = opened.begin(); inOpen!=opened.end(); ++inOpen) {
          if (inOpen->equals(option)) {
            break;
          }
        }
        //iterator to check if option in closed
        typename list<State < T>>
        ::iterator inClosed;
        for (inClosed = closed.begin(); inClosed!=closed.end(); ++inClosed) {
          if (inClosed->equals(option)) {
            break;
          }
        }

        if (inOpen!=opened.end()) {
          if (option.GetCost() <= inOpen->GetCost()) {
            opened.remove(*inOpen);
            opened.push_back(option);
          }
        } else if (inClosed!=closed.end()) {
          if (option.GetCost() <= inClosed->GetCost()) {}
          closed.remove(*inClosed);
          this->openList.push(option);
        } else {
          this->openList.push(option);
        }
      }
      while (!opened.empty()) {
        openList.push(opened.front());
        opened.pop_front();
      }

      closed.push_back(state);
    }
  }

  list<State<T>> backTrace(State<T>) {
    typename std::list<State < T>>
    ::iterator element;
    list<State<T>> trace;
    for (element = closed.begin(); element!=closed.end(); ++element) {
      trace.push_back(*element);
      this->SetEvaluatedNodes(this->evaluatedNodes + 1);
    }
    this->trace = trace;
    return trace;
  }

  void TemporaryFunction1() {
    AStar<Point, vector < string>>
    x;
  }
};
#endif //EX4__ASTAR_H_
