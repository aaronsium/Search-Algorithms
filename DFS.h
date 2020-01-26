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
    vector<State<T>> visited;

 public:
  virtual ~DFS() = default;

  /////////////////////////////////////////////////////////////
  S search(Searchable<T>* searchable){
    this->myStack.push_front(searchable->getInitialState());

    while(!(this->myStack).empty()){
      State<T> state = this->myStack.front();
      this->myStack.pop_front();

        if (searchable->isGoalState(state)) {
            vector<State<T>> traceVector = backTrace(state);
            return searchable->adaptSolution(traceVector);
        }

        if ((!std::count(this->visited.begin(), this->visited.end(), (state)))) {
            if ((!std::count(this->myStack.begin(), this->myStack.end(), (state)))) {
                this->visited.push_back(state);
                list<State<T>> options = searchable->getAllPossibleStates(state.copy());
                typename std::list<State<T>>::iterator opt;
                for (opt = options.begin(); opt!=options.end(); ++opt){
                  this->myStack.push_front(*opt);
            }
          }
        }
      }
  }


    vector<State<T>>backTrace(State<T> state) {
      list<State<T>> trace;
      trace.push_back(state);
      State<T>* previous = state.getPrevious();

      while(previous != NULL){
        trace.push_back(*previous);
        previous = previous->getPrevious();
        this->SetEvaluatedNodes(this->evaluatedNodes + 1);
      }
        cout<< "DFS - evaluatedNodes : "<<this->evaluatedNodes <<endl;

      vector<State<T>> traceVector;
      while(!trace.empty()){
        traceVector.push_back(trace.back());
        trace.pop_back();
      }

      return traceVector;
    }

  void TemporaryFunction4 (){
    DFS<Point,vector<string>> x;
  }

};










#endif //EX4__DFS_H_
