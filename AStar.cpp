//
// Created by yaffa on 1/19/20.
//

template<class T, class S>
S AStar<T, S>::search(Searchable<T> s){
    this->openList.push(s.getInitialState());

    while (this->openList > 0) {
        State <T> state = this->openList.top();
        this->openList.pop();

        if (s.isGoalState(state)) {
            while(!this->trace.empty()){
                traceVector.push_back(this->trace.back());
                this->trace.pop_back();
            }
        }

        while (!openList.empty()){
            opened.push_back(openList.top);
            openList.pop;
        }

        list<State<T>> PossibleStates = s.getAllPossibleStates();
        while(!PossibleStates.empty){
            State<T> option = PossibleStates.front();
            PossibleStates.pop_front();

            //iterator to check if option in open
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

            if(inOpen != opened.end){
                if(option.GetCost <= inOpen->GetCost){
                    openList.pop(*inOpen);
                    openList.push_back(option);
                }
            } else if(inClosed != closed.end()){
                if(option.GetCost <= inClosed->GetCost){}
                    closed.pop(*inClosed);
                    this->openList.push_back(option);
            } else {
                this->openList.push_back(option);
            }
        }
        while (!opened.empty()){
            openList.push_back(opened.top);
            opened.pop_front();
        }

        closed.insert(state);
    }
}

template<class T, class S>
S AStar<T, S>::backTrace() {
    typename std::list<State<T>>::iterator element;
    list<State<T>> trace;
    for (element = closed.begin(); element!=closed.end(); ++element) {
        trace.push_back(element);
        this->SetEvaluatedNodes(this->evaluatedNodes + 1);
    }
    this->trace = trace;
    return trace;
}