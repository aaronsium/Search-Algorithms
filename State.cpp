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
  return status.Equals(s.status);
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
template<typename T>
T State<T>::GetStatus() const {
  return status;
}
