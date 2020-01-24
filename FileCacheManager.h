//
// Created by aharon on 24/01/2020.
//

#ifndef EX4__FILECACHEMANAGER_H_
#define EX4__FILECACHEMANAGER_H_
#include "CacheManager.h"
#include <string>
#include <list>
#include <map>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


template<class S>
class FileCacheManager : public CacheManager<string, S> {
 private:
  list<pair<string, S>> cacheList;
  map<string, typename list<pair<string, S>>::iterator> mapPointers;
  unsigned int capacity = 5;

 public:
  FileCacheManager(){};
  ~FileCacheManager()  {} ;

  ////////////////////////////////////////////////////////
  string hashing(string problem) {
    hash<string> myHash;
    // Using operator() to get hash value
    return to_string(myHash(problem));
  }

  bool inCache(string problem) {
    if (this->mapPointers.find(problem)!=mapPointers.end()) {
      return true;
    } else {
      return false;
    }
  }

  void intoCache(string problem, S solution) {
    string key = hashing(problem);
    bool found = inCache(key);
    bool exist = inCache(key);
    // if it doesn't exist both in file and cash
    if (!found && !exist) {
      ////
      lru(key);
      wFile(key, solution);
    } else if (found) {
      cacheList.erase(mapPointers[key]);
      wFile(key, solution);

    } else if (exist) {
      S oldObject = getSolution(key);
    }
    cacheList.push_front(make_pair(key, solution));
    mapPointers[key] = cacheList.begin();

  }

  S getSolution(string problem) {
    string key = hashing(problem);
    bool found = inCache(key);
    string check = key;
    bool exist = inCache(check);
    // if it doesn't exist both in file and cash
    if (!found & !exist) {
      throw "an error";
      // if it exist only in cache
    } else if (found) {
      S obj = (mapPointers[key])->second;
      cacheList.erase(mapPointers[key]);
      cacheList.push_front(make_pair(key, obj));
      mapPointers[key] = cacheList.begin();
      return mapPointers[key]->second;
    } else {
      S object = rFile((check));
      wFile(check, object);
      //if the cash is full
      if (cacheList.size()==this->capacity) {
        auto least = cacheList.back();
        cacheList.pop_back();
        mapPointers.erase(least.first);
      }
      cacheList.push_front(make_pair(key, object));
      mapPointers[key] = cacheList.begin();
      return object;
    }

  }

  void lru(string key) {
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

  void wFile(string key, S solution) {
    ofstream output_file{key, ios::binary};
    if (!output_file.is_open()) {
      cout << "error while opening file";
    } else {
      output_file.write((char *) &solution, sizeof(S));
      output_file.close();
    }
  }

  S rFile(string key) {
    ifstream in_file(key, ios::binary);
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

  string Convertstr(size_t sz) {
    char buf[24];
    sprintf(buf, "%u", sz);
    string newStr(buf);
    return newStr;
  }
  void TemporaryFunction5 (){
    FileCacheManager<vector<string>> x;
  }
};

#endif //EX4__FILECACHEMANAGER_H_
