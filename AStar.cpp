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
            this->SetEvaluatedNodes(this->evaluatedNodes + 1);
            return backTrace();
        }

        list<State<T>> PossibleStates = s.getAllPossibleStates();
        while(!PossibleStates.empty){
            State<T> option = PossibleStates.front();
            PossibleStates.pop_front();

            const_iterator inOpen = openList.find(option);
            if(inOpen != NULL){
                if(option.GetCost<= openList.find(option)){}
            } else if(closed(option) == closed.end()/*compare with "equals"*/){
                if(option.GetCost<= 5/* point at the state from closed and compare to it's cost*/){}
                    closed.pop(option);
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
    }
    return trace;
}