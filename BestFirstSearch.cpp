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

        //אתה מחזיר פה רשימה אבל לא צריך להמיר את זה דרך adaptSolution שבמטריצה שמקבל וקטור?
      return backTrace();
    }

    while (!openList.empty()){
      opened.push_back(openList.top);
      openList.pop;
    }

    list<State<T>> options = searchable.getAllPossibleStates(n);
    typename std::list<State<T>>::iterator opt;
    for (opt = options.begin(); opt!=options.end(); ++opt) {
      this->SetEvaluatedNodes(this->evaluatedNodes + 1);
      //iterator to check if option in opened
      typename list<State<T>>::iterator inOpen;
      for (inOpen = opened.begin(); inOpen != opened.end(); ++inOpen){
        if(inOpen->equals.option) {
          break;
        }
      }

      //iterator to check if option in closed
      typename list<State<T>>::iterator inClosed;
      for (inClosed = closed.begin(); inClosed != closed.end(); ++inClosed){
        if(inClosed->equals.option) {
          break;
        }
      }

      if((inOpen == opened.end) && (inClosed == closed.end)){
        opt->SetCameFrom(n);
        openList.push(opt);
      } else if(inClosed != closed.end){//באלגוריתם של אלי אם b קורה והסעיף הראשון בתוכו לא, זה אומר שהסטייט בcloesd.(אם כבר עברנו עליו בעבר אבל הוא לא בopen)
        if(opt->GetCost() < inClosed->GetCost()){
          if (inOpen != opened.end) {//יכול להיות שהסעיף השני כן קורה ואז הוא נמצא גם ב-opened וגם ב-closed
            //popping and pushing again(for the priority process)
            openList.pop(*inOpen);
          }
          openList.push_back(opt);
          closed.pop(*inClosed);
        }
      } else {// אם הוא לא ב- closed אז הוא חייב להיות ב-opened
        if(opt->GetCost() < inOpen->GetCost()) {
          openList.pop(*inOpen);
          openList.push_back(opt);
        }
      }
    }

    while (!opened.empty()){
      openList.push(opened.top);
      opened.pop_front();
    }
  }
}
//overloading comparator


template<class T, class S>
list<State<T>> BestFirstSearch<T, S>::backTrace() {
  typename std::list<State<T>>::iterator element;
  list<State<T>> trace;
  for (element = closed.begin(); element!=closed.end(); ++element) {
    trace.push_back(element);
  }
  return trace;
}


