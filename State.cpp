//
// Created by aharon on 17/01/2020.
//

#include "General.h"
template<class T>
State<T>::State(T status1) {
  this->status = status1;
}

template<class T>
T State<T>:: getStatus(){
  return this->status;
}

template<class T>
bool State<T>::equals(State<T> s) {
  return state.equals(s.getStatus());
}