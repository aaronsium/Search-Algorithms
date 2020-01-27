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

      list<State<T>> PossibleStates = s->getAllPossibleStates(state.copy());
      typename std::list<State<T>>::iterator option;
      State<T> tempOption;
      State<T> tempInclose;
      State<T> tempOpen;
      if (!PossibleStates.empty()){
        for (option = PossibleStates.begin(); option!=PossibleStates.end(); ++option) {
          tempOption = (*option);
          //iterator to check if option in opened
          typename std::list<State<T>>::iterator inOpen;
          if (!opened.empty()) {

            for (inOpen = this->opened.begin(); inOpen!=this->opened.end(); ++inOpen) {
              tempOpen = (*inOpen);
              if (tempOpen.equals(tempOption)) {
                break;
              }
            }
          }
          //iterator to check if option in closed
          typename std::list<State<T>>::iterator inClosed;
          if (!closed.empty()) {
            for (inClosed = this->closed.begin(); inClosed!=this->closed.end(); ++inClosed) {
              tempInclose = (*inClosed);
              if (tempInclose.equals(tempOption)) {
                break;
              }
            }
          }
          if (!opened.empty() && inOpen!=opened.end()) {
            if (tempOption.GetCost() < tempOpen.GetCost()) {
              opened.remove(tempOpen);
              opened.push_back(tempOption);
            }
          } else if (!closed.empty() && inClosed!=closed.end()) {
            cout << tempOption.GetCost() << endl;
            cout << tempOpen.GetCost() << endl;
            if (tempOption.GetCost() < tempOpen.GetCost()) {}
            closed.remove(tempInclose);
            this->opened.push_back(tempOption);
          } else {
            this->opened.push_back(tempOption);
          }
        }
    }


      closed.push_back(state);
    }
  }

  list<State<T>> backTrace(State<T>) {
    typename std::list<State < T>>::iterator element;
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
