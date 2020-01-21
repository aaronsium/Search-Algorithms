//
// Created by aharon on 17/01/2020.
//

#include "General.h"

template<class T, class S>
S BestFirstSearch<T, S>::search(Searchable<T> searchable) {
  priority_queue<State<T>> openList;
  openList.push(searchable.getInitialState());
  closed = new unordered_set<State<T>>;////////
  while (openList > 0) {
    State<T> n = openList.top();
    this->openList.pop();
    closed.insert(n);
    if (searchable.isGoalState(n)) {
      this->SetEvaluatedNodes(this->evaluatedNodes + 1);

        //אתה מחזיר פה רשימה אבל לא צריך להמיר את זה דרך adaptSolution שבמטריצה ומקבל וקטור?
      return backTrace();
    }
    list<State<T>> options = searchable.getAllPossibleStates(n);
    typename std::list<State<T>>::iterator opt;
    for (opt = options.begin(); opt!=options.end(); ++opt) {
      bool isOpenContain = (find(options.begin(), options.end(), opt)!=options.end());
      bool isCloseContain = (find(options.begin(), options.end(), opt)!=options.end());
      if ((!isCloseContain) && (!isOpenContain)) {
        opt->SetCameFrom(n);
        openList.push(opt);
      } else if (opt->GetCost() < n.GetCost()/*n צריך להיות c שהגיע מ-a ונמצא ב open*/) {
        n.SetCost(opt->GetCost());
        //popping and pushing again(for the priority process)
        State<T> temp = n;
        openList.pop();
        openList.push(temp);
      }
    }
  }

}
//overloading comparator


template<class T, class S>
S BestFirstSearch<T, S>::backTrace() {
  typename std::list<State<T>>::iterator element;
  list<State<T>> trace;
  for (element = closed.begin(); element!=closed.end(); ++element) {
    trace.push_back(element);
  }
  return trace;
}


