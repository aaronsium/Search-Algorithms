//
// Created by aharon on 24/01/2020.
//

#ifndef EX4__DFS_H_
#define EX4__DFS_H_

#include "Searcher.h"
#include "State.h"
#include "Searchable.h"


template<class T, class S>
class DFS : public Searcher<T, S> {
 private:
    list<State<T>> myStack;
    list<State<T>> trace;
    list<State<T>> visited;

 public:
  virtual ~DFS() = default;

  /////////////////////////////////////////////////////////////
  S search(Searchable<T>* searchable){
    this->myStack.push_front(searchable->getInitialState());
      int flag = 0;

    while(!(this->myStack).empty()){
      State<T> state = this->myStack.front();
      this->myStack.pop_front();

        if (searchable->isGoalState(state)) {
            if (searchable->isGoalState(state)) {
                list<State<T>> t = backTrace(state);
                int traceSize = t.size();
                if(flag == 0){
                    this-> trace = t;
                    flag = 1;
                } else {
                    if(this->trace.size() > traceSize){
                        this-> trace = t;
                    }
                }
                cout<< "TempDFS - evaluatedNodes : "<<this->trace.size()<<endl;
            }
        }

        //iterator to check if option in visited
//      for (std::list<T>::iterator it = mylist.begin(); it != mylist.end(); ++it)
        typename list<State<T>>::iterator inVisited;
        for (inVisited = this->visited.begin(); inVisited!=this->visited.end(); ++inVisited) {
            if (inVisited->equals(state)) {
                break;
            }
        }
        //iterator to check if option in Stack
//      for (std::list<T>::iterator it = mylist.begin(); it != mylist.end(); ++it)
        typename list<State<T>>::iterator inStack;
        for (inStack = this->myStack.begin(); inVisited!=this->myStack.end(); ++inStack) {
            if (inStack->equals(state)) {
                break;
            }
        }

        if (inVisited == this->visited.end()) {
                this->visited.push_back(state);
                list<State<T>> options = searchable->getAllPossibleStates(state.copy());
                typename std::list<State<T>>::iterator opt;
                for (opt = options.begin(); opt!=options.end(); ++opt){
                  this->myStack.push_front(*opt);
          }
        } else{
            if(inVisited->GetCost() > state.GetCost()){
                this->visited.remove(*inVisited);
                this->myStack.push_front(state);

            }
        }
      }
      vector<State<T>> traceVector;
      while(!trace.empty()){
          traceVector.push_back(trace.back());
          trace.pop_back();
      }

      this->SetEvaluatedNodes(trace.size());

      cout<< "DFS - evaluatedNodes : "<<this->evaluatedNodes <<endl;
      return searchable->adaptSolution(traceVector);
  }


    list<State<T>>backTrace(State<T> state) {
      list<State<T>> trace;
      trace.push_back(state);
      State<T>* previous = state.getPrevious();

      return trace;
    }

  void TemporaryFunction4 (){
    DFS<Point,vector<string>> x;
  }

};










#endif //EX4__DFS_H_
