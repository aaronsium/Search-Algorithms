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
  State() {}
  State(T status1, State<T> *came_from, double c) :
      status(status1),
      cameFrom(came_from),
      cost(c) {}

  State<T> *copy() {
    return new State<T>(this->getStatus(), this->getPrevious(), this->GetCost());
  }

  T getStatus() const {
    return this->status;
  }

  bool equals(State<T> s) const {
    return status.equals(s.getStatus());
  }

  void SetCameFrom(State<T> *came_from) {
    cameFrom = came_from;
  }

  double GetCost() const {
    return cost;
  }

  void SetCost(double c) {
    this->cost = c;
  }

  State<T> *getPrevious() {
    return this->cameFrom;
  }

  bool operator<(const State<T> &s1) const {
    return (this->GetCost() < s1.GetCost());
  }

  bool operator==(const State<T> &s1) const {
    return status.equals(s1.getStatus());
  }

  State<T> &operator=(const State<T> &s1) {
    this->status = s1.status;
    this->cameFrom = s1.cameFrom;
    this->cost = s1.cost;
    return (*this);
  }
};

#endif //EX4_STATE_H
