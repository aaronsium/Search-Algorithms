//
// Created by omer on 1/23/20.
//

#ifndef EX4_STATE_H
#define EX4_STATE_H

template<class T>
class State {

private:
    T status;
    double cost;
    State<T> *cameFrom;

public:
    State();
    State(T state, State<T>* came_from, double cost);
    bool equals(State<T> s) const;
    void SetCameFrom(State<T>* came_from);
    double GetCost() const;
    void SetCost(double cost);
    State<T>* getPrevious();
    bool operator<(const State<T>& s1)const ;
    State<T>& operator=(const State<T> &s1 ) ;
    bool operator==(const State<T> &s1 ) const;
    T getStatus() const;
};

#endif //EX4_STATE_H
