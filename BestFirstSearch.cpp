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

        //אתה מחזיר פה רשימה אבל לא צריך להמיר את זה דרך adaptSolution שבמטריצה שמקבל וקטור?
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
      } else if (opt->GetCost() < n.GetCost()/* ם n צריך להיות c שהגיע מ-a ונמצא ב open*/) {
          //יכול גם להיות מהתנאי הקודם שהוא נמצא ב-closed ולא ב-opened, או שהוא נמצא בשניהם.
        n.SetCost(opt->GetCost());
        //popping and pushing again(for the priority process)
        State<T> temp = n;
        openList.pop();
        openList.push(temp);
      }
    }
      //שמתי פה הצעה למימוש במקום מה שנמצא בתוך ה-for אם תרצה להציץ...
      //כשמורידים את התיחום רואים את ההערות בעברית משולבת אנגלית בצורה לא מבולגנת. מתנצלת מראש אם יש שגיאות חח

     /*
      ***********************************************
      //iterator to check if option in opened
      MyQueue<>::iterator inOpen = openList.find(option); //להגדיר קודם את openList ל-MyQueue
      //iterator to check if option in closed
      std::list<State<T>>::iterator inClosed;
      for (inClosed = closed.begin(); inClosed != closed.end(); ++inClosed){
          if(inClosed->equals.option) {
              break;
          }
      }

      if((inOpen == NULL) && (inClosed == closed.end)){
          opt->SetCameFrom(n);
          openList.push(opt);
      } else if(inClosed != closed.end){//באלגוריתם של אלי אם b קורה והסעיף הראשון בתוכו לא, זה אומר שהסטייט בcloesd.(אם כבר עברנו עליו בעבר אבל הוא לא בopen)
        if(opt->GetCost() < inClosed->GetCost()){
          if (inOpen != NULL) {//יכול להיות שהסעיף השני כן קורה ואז הוא נמצא גם ב-opened וגם ב-closed
            //popping and pushing again(for the priority process)
            openList.pop(*inOpen);
          }
          openList.push(opt);
          closed.pop(*inClosed);
        }
      } else {// אם הוא לא ב- closed אז הוא חייב להיות ב-opened
           if(opt->GetCost() < inOpen->GetCost()) {
             openList.pop(*inOpen);
             openList.push(opt);
        }
      }

    ***********************************************
            */
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


