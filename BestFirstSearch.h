//
// Created by aharon on 23/01/2020.
//

#ifndef EX4__BESTFIRSTSEARCH_H_
#define EX4__BESTFIRSTSEARCH_H_
#include "Searcher.h"
#include "State.h"


template<class T, class S>
class BestFirstSearch : public Searcher<T, S> {

 private:
  priority_queue<State<T>> openList;
  list<State<T>> opened;
  list<State<T>> closed;

 public:
  virtual S search(Searchable<T> *searchable);
  vector<State<T>> backTrace();
  virtual ~BestFirstSearch() = default;

  ///////////////////////////////////////////////

  vector<State<T>> backTrace() {
    typename std::list<State < T>>
    ::iterator element;
    vector<State<T>> trace;
    for (element = closed.begin(); element!=closed.end(); ++element) {
      trace.push_back(*element);
    }
    return trace;
  }

  void TemporaryFunction2() {
    BestFirstSearch<Point, vector < string>>
    x;
  }

};

#endif //EX4__BESTFIRSTSEARCH_H_
