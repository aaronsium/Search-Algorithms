//
// Created by aharon on 17/01/2020.
//

#include "General.h"
template<class T>
State<T>::State(T status1, State<T>* came_from, double c) {
  this->status = status1;
  this->cameFrom = came_from;
  this->cost = c;
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
void State<T>::SetCameFrom(State<T>* came_from) {
  cameFrom = came_from;
}
template<typename T>
double State<T>::GetCost() const {
  return cost;
}
template<typename T>
void State<T>::SetCost(double c) {
  this->cost = c;
}

template<typename T>
State<T>* State<T>:: getPrevious(){
  return this->cameFrom;
}
template<typename T>
bool State<T>::operator<(State<T>* s1) {
  return this->GetCost() < s1->GetCost();
}