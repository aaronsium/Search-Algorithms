//
// Created by aharon on 16/01/2020.
//

#include "General.h"
template<class T, class S>
Searcher<T, S>::Searcher() {
  evaluatedNodes = 0;
}

//template<class T, class S>
//
//int Searcher<T, S>::listSize() {
//  return openList.size();
//}

template<class T, class S>
int Searcher<T, S>::NodesEvaluated() {
  return evaluatedNodes;
}
//template<class T, class S>
//const priority_queue<State<T>> &Searcher<T, S>::GetOpenList() const {
//  return openList;
//}
//template<class T, class S>
//void Searcher<T, S>::SetOpenList(const priority_queue<State<T>> &open_list) {
//  openList = open_list;
//}

template<class T, class S>
void Searcher<T, S>::SetEvaluatedNodes(int evaluated_nodes) {
  evaluatedNodes = evaluated_nodes;
}

