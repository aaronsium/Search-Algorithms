//
// Created by aharon on 17/01/2020.
//

#include "General.h"
template<class T>
State<T>::State(T status1) {
  this->status = status1;
  this->cameFrom =status1;
}

template<class T>
T State<T>:: getStatus(){
  return this->status;
}
template<class T>
bool State<T>::equals(State<T> s) {
  return status.equals(s.getStatus());
}
template<typename T>
void State<T>::SetCameFrom(const State<T> &came_from) {
  cameFrom = came_from;
}
template<typename T>
double State<T>::GetCost() const {
  return cost;
}
template<typename T>
void State<T>::SetCost(double cost) {
  State::cost = cost;
}
