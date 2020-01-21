//
// Created by yaffa on 1/17/20.
//
#include "General.h"

template<class T, class S>
S DFS<T, S>::search(Searchable<T> s){
    this->myStack.push(s.getInitialState());
    int flag = 0;

    while(!(this->myStack).empty){
        State<T> state = myStack.top;
        myStack.pop;
        closed.insert(state);

        if (s.isGoalState(state)) {
            list<State<T>> t = backTrace();
            int traceSize = t.size();
            if(flag == 0){
                this-> trace = t;
                flag = 1;
            } else {
                if(this->trace.size > traceSize){
                    this-> trace = t;
                }
            }
        }

        list<State<T>> PossibleStates = s.getAllPossibleStates();
        while(!PossibleStates.empty){
            int inClosed = 0;
            State<T> option = PossibleStates.front();
            PossibleStates.pop_front();

          typename  std::list<State<T>>::iterator it;
            for (it = closed.begin(); it != closed.end(); ++it){
                if(it->equals.option) {
                    inClosed = 1;
                }
            }
            if(!inClosed){
                this->myStack.push(option);
            }
        }
    }

    vector<State<T>> traceVector;
    while(!this->trace.empty()){
        traceVector.push_back(this->trace.back());
        this->trace.pop_back();
    }

    return s.adaptSolution(traceVector);
}


template<class T, class S>
list<State<T>> DFS<T, S>::backTrace(State<T> state){
    list<State<T>> trace;
    trace.push_back(state);
    State<T> previous = state.getPrevious;

    while(previous != NULL){
        trace.push_back(previous);
        previous = previous.getPrevious;
        this->SetEvaluatedNodes(this->evaluatedNodes + 1);
    }

    return trace;
}