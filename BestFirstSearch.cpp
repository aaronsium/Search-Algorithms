//
// Created by aharon on 17/01/2020.
//

#include "General.h"

template<class T, class S>
S BestFirstSearch<T, S>::search(Searchable<T>* searchable) {
  priority_queue<State<T>> openList;
  openList.push(searchable->getInitialState());
  while (!openList.empty()) {
    State<T> n = openList.top();
    this->openList.pop();
    closed.insert(n);
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
      typename unordered_set<State<T>>::iterator inClosed;
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
          closed.erase(*inClosed);
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
//overloading comparator


template<class T, class S>
vector<State<T>> BestFirstSearch<T, S>::backTrace() {
  typename std::unordered_set<State<T>>::iterator element;
  vector<State<T>> trace;
  for (element = closed.begin(); element!=closed.end(); ++element) {
    trace.push_back(*element);
  }
  return trace;
}


