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

        list<State<T>> PossibleStates = s.getAllPossibleStates();
        while(!PossibleStates.empty){
            State<T> option = PossibleStates.front();
            PossibleStates.pop_front();

            //iterator to check if option in open
            MyQueue<>::iterator inOpen = openList.find(option);
            //iterator to check if option in closed
            std::list<State<T>>::iterator inClosed;
            for (inClosed = closed.begin(); inClosed != closed.end(); ++inClosed){
                if(inClosed->equals.option) {
                    break;
                }
            }

            if(inOpen != NULL){
                if(option.GetCost <= inOpen->GetCost){
                    openList.pop(*inOpen);
                    openList.push(option);
                }
            } else if(inClosed != closed.end()){
                if(option.GetCost <= inClosed->GetCost){}
                    closed.pop(*inClosed);
                    this->openList.push(option);
            } else {
                this->openList.push(option);
            }
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