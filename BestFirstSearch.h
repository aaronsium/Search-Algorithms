//
// Created by aharon on 23/01/2020.
//

#ifndef EX4__BESTFIRSTSEARCH_H_
#define EX4__BESTFIRSTSEARCH_H_
#include "Searcher.h"
#include "State.h"
#include "Searchable.h"
using namespace std;
template<class T>
// comparator for min priority_queue<
struct compare {
  bool operator()(const State<T> &l, const State<T> &r) {
    return (l.GetCost() < r.GetCost());
  }
};

template<class T, class S>
class BestFirstSearch : public Searcher<T, S> {
 private:

  priority_queue<State<T>, vector<State<T>>, compare<T>> openList;
  list<State<T>> opened;
  list<State<T>> closed;

 public:
  virtual ~BestFirstSearch() = default;
  ///////////////////////////////////////////////
  S search(Searchable<T> *searchable) {
    this->openList.push(searchable->getInitialState());
    while (!this->openList.empty()) {
      State<T> n = this->openList.top();
      this->openList.pop();
      this->closed.push_back(n);
      if (searchable->isGoalState(n)) {
        return searchable->adaptSolution(backTrace());
      }

      while (!this->openList.empty()) {
        this->opened.push_back(this->openList.top());
        this->openList.pop();
      }

      list<State<T>> options = searchable->getAllPossibleStates(n.copy());
      typename std::list<State<T>>::iterator opt;
      for (opt = options.begin(); opt!=options.end(); ++opt) {
        this->SetEvaluatedNodes(this->evaluatedNodes + 1);
        //iterator to check if option in opened
        typename list<State<T>>::iterator inOpen;
        for (inOpen = this->opened.begin(); inOpen!=this->opened.end(); ++inOpen) {
          if (inOpen->equals(*opt)) {
            break;
          }
        }

        //iterator to check if option in closed
        typename list<State<T>>::iterator inClosed;
        for (inClosed = this->closed.begin(); inClosed!=this->closed.end(); ++inClosed) {
          if (inClosed->equals(*opt)) {
            break;
          }
        }

        if ((inOpen==this->opened.end()) && (inClosed==this->closed.end())) {
          this->opened.push_back(*opt);
        } else if (inClosed!=this->closed.end()) {
          if (opt->GetCost() < inClosed->GetCost()) {
            if (inOpen!=this->opened.end()) {
              //popping and pushing again(for the priority process)
              this->opened.remove(*inOpen);
            }
            this->opened.push_back(*opt);
            this->closed.remove(*inClosed);
          }
        } else {
          if (opt->GetCost() < inOpen->GetCost()) {
            this->opened.remove(*inOpen);
            this->opened.push_back(*opt);
          }
        }
      }

      while (!opened.empty()) {
        openList.push(opened.front());
        opened.pop_front();
      }
    }
  }

  vector<State<T>> backTrace() {
    typename std::list<State<T>>
    ::iterator element;
    vector<State<T>> trace;
    for (element = closed.begin(); element!=closed.end(); ++element) {
      trace.push_back(*element);
    }
    return trace;
  }

//  void TemporaryFunction2() {
//    BestFirstSearch<Point, vector < string>>
//    x;
//  }

};

#endif //EX4__BESTFIRSTSEARCH_H_
