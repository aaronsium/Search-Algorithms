//
// Created by aharon on 17/01/2020.
//

#include "State.h"
template<class T>
State<T>::State(T status1, State<T>* came_from, double c) {
  this->status = status1;
  this->cameFrom = came_from;
  this->cost = c;
}

template<class T>
 T State<T>:: getStatus() const{
  return this->status;
}
template<class T>
bool State<T>::equals(State<T> s) const {
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
template<class T>
bool State<T>::operator<(const State<T>& s1)  const{
  return (this->GetCost() < s1.GetCost());
}
template<class T>
bool State<T>::operator==(const State<T>& s1)  const{
  return status.equals(s1.getStatus());
}

template<class T>
State<T>& State<T>::operator=(const State<T>& s1 ) {
  this->status = s1.status;
  this->cameFrom = s1.cameFrom;
  this->cost = s1.cost;
return (*this);
}


namespace std {

template<class T>
struct hash<State<T>> {
  size_t operator ()(State<T> value) const {
    return static_cast<size_t>(value);
  }
};
}