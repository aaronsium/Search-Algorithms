//
// Created by aharon on 23/01/2020.
//

#ifndef EX4__BESTFIRSTSEARCH_H_
#define EX4__BESTFIRSTSEARCH_H_
#include "Searcher.h"
#include "State.h"
#include "Searchable.h"


template<class T, class S>
class BestFirstSearch : public Searcher<T, S> {

 private:
  priority_queue<State<T>> openList;
  list<State<T>> opened;
  list<State<T>> closed;

 public:
  virtual ~BestFirstSearch() = default;
  ///////////////////////////////////////////////
  S search(Searchable<T>* searchable) {
    priority_queue<State<T>> openList;
    openList.push(searchable->getInitialState());
    while (!openList.empty()) {
      State<T> n = openList.top();
      this->openList.pop();
      closed.push_back(n);
      if (searchable->isGoalState(n)) {
        return searchable->adaptSolution(backTrace());
      }

      while (!openList.empty()){
        opened.push_back(openList.top());
        openList.pop();
      }

      list<State<T>> options = searchable->getAllPossibleStates(n);
      typename std::list<State<T>>::iterator opt;
      for (opt = options.begin(); opt!=options.end(); ++opt) {
        this->SetEvaluatedNodes(this->evaluatedNodes + 1);
        //iterator to check if option in opened
        typename list<State<T>>::iterator inOpen;
        for (inOpen = opened.begin(); inOpen != opened.end(); ++inOpen){
          if(inOpen->equals(*opt)) {
            break;
          }
        }

        //iterator to check if option in closed
//      for (std::list<T>::iterator it = mylist.begin(); it != mylist.end(); ++it)
        typename list<State<T>>::iterator inClosed;
        for (inClosed = closed.begin(); inClosed != closed.end(); ++inClosed){
          if(inClosed->equals(*opt)) {
            break;
          }
        }

        if((inOpen == opened.end()) && (inClosed == closed.end())){
          opt->SetCameFrom(&n);
          openList.push(*opt);
        } else if(inClosed != closed.end()){
          if(opt->GetCost() < inClosed->GetCost()){
            if (inOpen != opened.end()) {
              //popping and pushing again(for the priority process)
              opened.remove(*inOpen);
            }
            openList.push(*opt);
            closed.remove(*inClosed);
          }
        } else {
          if(opt->GetCost() < inOpen->GetCost()) {
            opened.remove(*inOpen);
            opened.push_back(*opt);
          }
        }
      }

      while (!opened.empty()){
        openList.push(opened.front());
        opened.pop_front();
      }
    }
  }

  vector<State<T>> backTrace() {
    typename std::list<State < T>>
    ::iterator element;
    vector<State<T>> trace;
    for (element = closed.begin(); element!=closed.end(); ++element) {
      trace.push_back(*element);
    }
    return trace;
  }

//  void TemporaryFunction2() {
//    BestFirstSearch<Point, vector < string>>
//    x;
//  }

};

#endif //EX4__BESTFIRSTSEARCH_H_
