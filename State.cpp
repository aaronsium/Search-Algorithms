//
// Created by aharon on 17/01/2020.
//

#include "General.h"
template<class T>
State<T>::State(T state1) {
  this->state = state1;
}

template<class T>
bool State<T>::Equals(State<T> s) {
  return state.Equals(s.state);
}