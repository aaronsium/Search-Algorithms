//
// Created by aharon on 14/01/2020.
//
#include "General.h"

template<class P, class S>
bool FileCacheManager<P, S>::inCache(P problem) {
  if (this->mapPointers.find(problem)!=mapPointers.end()) {
    return true;
  } else {
    return false;
  }
}

template<class P, class S>
void FileCacheManager<P, S>::intoCache(string problem, S soulution) {
  if (this->name=="") {
    this->name = soulution.class_name;
  }
  bool found = inCache(problem);
  bool exist = inCache(problem);
  // if it doesn't exist both in file and cash
  if (!found && !exist) {
    ////
    lru(problem);
    wFile(problem + this->name, soulution);
  } else if (found) {
    cacheList.erase(mapPointers[problem]);
    wFile(problem + this->name, soulution);

  } else if (exist) {
    S oldObject = getSolution(problem);
  }
  cacheList.push_front(make_pair(problem, soulution));
  mapPointers[problem] = cacheList.begin();

}

template<class P, class S>
S FileCacheManager<P, S>::getSolution(string problem) {
  bool found = inCache(problem);
  string check = problem + this->name;
  bool exist = inCache(check);
  // if it doesn't exist both in file and cash
  if (!found & !exist) {
    throw "an error";
    // if it exist only in cache
  } else if (found) {
    S obj = (mapPointers[problem])->second;
    cacheList.erase(mapPointers[problem]);
    cacheList.push_front(make_pair(problem, obj));
    mapPointers[problem] = cacheList.begin();
    return mapPointers[problem]->second;
  } else {
    S object = rFile((check));
    wFile(check, object);
    //if the cash is full
    if (cacheList.size()==this->capacity) {
      auto least = cacheList.back();
      cacheList.pop_back();
      mapPointers.erase(least.first);
    }
    cacheList.push_front(make_pair(problem, object));
    mapPointers[problem] = cacheList.begin();
    return object;
  }

}

template<class P, class S>
void FileCacheManager<P, S>::lru(string key) {
  // if cash is full
  if (cacheList.size()==this->capacity) {
    auto least = cacheList.back();
    cacheList.pop_back();
    mapPointers.erase(least.first);
    //if   exist
  } else {
    mapPointers.erase(key);
  }
}

template<class P, class S>
void FileCacheManager<P, S>::wFile(string problem, S solution) {
  ofstream output_file{problem, ios::binary};
  if (!output_file.is_open()) {
    cout << "error while opening file";
  } else {
    output_file.write((char *) &solution, sizeof(S));
    output_file.close();
  }
}

template<class P, class S>
S FileCacheManager<P, S>::rFile(string problem) {
  ifstream in_file(problem, ios::binary);
  S object;
  if (!in_file.is_open()) {
    throw "error while opening file";
  } else {
    in_file.read((char *) &object, sizeof(S));
    in_file.close();
    return object;
  }
  return object;
}