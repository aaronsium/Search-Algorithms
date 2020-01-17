//
// Created by aharon on 17/01/2020.
//

#include "General.h"

template<class T, class S>
S BestFirstSearch<T, S>::search(Searchable<T> searchable) {
  this->openList.push(searchable.getInitialState());
  closed = new unordered_set<State<T>>;////////
  while (this->openList > 0) {
    State<T> n = this->openList.top();
    this->openList.pop();
    closed.insert(n);
    if (searchable.isGoalState(n)) {
      return backTrace();
    }
    list<State<T>> options = searchable.getAllPossibleStates(n);
    typename std::list<State<T>>::iterator opt;
    for (opt = options.begin(); opt!=options.end(); ++opt) {
      bool isOpenContain = (find(options.begin(), options.end(), opt)!=options.end());
      bool isCloseContain = (find(options.begin(), options.end(), opt)!=options.end());
      if ((!isCloseContain) && (!isOpenContain)) {
        opt->SetCameFrom(n);
        this->openList.push(opt);
      } else if (opt->GetCost() < n.GetCost()) {
        n.SetCost(opt->GetCost());
        //popping and pushing again(for the priority process)
        State<T> temp =n;
        this->openList.pop();
        this->openList.push(temp);
      }
    }
  }

}
//overloading comparator
template<class T, class S>
bool BestFirstSearch<T, S>::operator<(const State<T> &s1){
  return this->GetCost() < s1->GetCost();
}

template<class T, class S>
S BestFirstSearch<T, S>::backTrace(){
  typename std::list<State<T>>::iterator element;
  list<State<T>> trace;
  for (element = closed.begin(); element!=closed.end(); ++element) {
    trace.push_back(element);
  }
    return trace;
}


