//
// Created by wzj on 2021/12/3.
// Modified by Yifei Ma on 2023/10/25.
//

#ifndef FINAL_SRC_HPP
#define FINAL_SRC_HPP

#include <string>
#include <vector>

// If the two following commands bother you, you may comment them and write
// std::vector and std::string instead.
using std::string;
using std::vector;

struct LinkedHashMap;
struct Node {
  Node* next = nullptr;
  Node* timePre = nullptr;
  Node* timeNext = nullptr;

  int key = 0;
  string value;
};

struct Data {
  int key;
  string value;
};

vector<Data> traverseByTime(const LinkedHashMap& obj);
vector<Data> traverseByIndex(const LinkedHashMap& obj);

struct LinkedHashMap {
  // You can modify beg, cur and related parts in the constructor as you wish.
  // 你可以根据自己写链表的习惯修改或删除头尾节点并修改构造函数。

  int len;
  Node** array;
  Node* beg;
  Node* cur;
  // TODO: define a function pointer named "forEachMethod"
  // to be pointed to one of the functions "traverseByTime" or "traverseByDict".
  // 定义一个名为 forEachMethod 的函数指针，用于指向 travelByTime 或
  // travelByDict 函数。
  vector<Data> (*forEachMethod)(const LinkedHashMap&);

  void init(int len_, bool forEachByTime) {
    len = len_;
    beg = new Node();
    cur = beg;
    array = new Node*[len];
    for (int i = 0; i < len; i++) {
      array[i] = nullptr;
    }
    if (forEachByTime)
      forEachMethod = traverseByTime;
    else
      forEachMethod = traverseByIndex;
  }

  void clearMemory() {
    // TODO
    Node* p = beg;
    while (p != nullptr) {
      Node* next = p->timeNext;
      delete p;
      p = next;
    }
    delete[] array;
  }

  void insert(int key, string value) {
    // TODO
    Node* newNode = new Node();
    newNode->key = key;
    newNode->value = value;
    
    newNode->next = array[key];
    array[key] = newNode;
    
    cur->timeNext = newNode;
    newNode->timePre = cur;
    cur = newNode;
  }

  void remove(int key, string value) {
    // TODO
    Node* p = array[key];
    Node* prev = nullptr;
    while (p != nullptr) {
      if (p->value == value) {
        if (prev == nullptr) {
          array[key] = p->next;
        } else {
          prev->next = p->next;
        }
        
        if (p->timePre != nullptr) {
          p->timePre->timeNext = p->timeNext;
        }
        if (p->timeNext != nullptr) {
          p->timeNext->timePre = p->timePre;
        } else {
          cur = p->timePre;
        }
        
        Node* toDelete = p;
        p = p->next;
        delete toDelete;
      } else {
        prev = p;
        p = p->next;
      }
    }
  }

  vector<string> ask(int key) const {
    // TODO
    vector<string> res;
    Node* p = array[key];
    while (p != nullptr) {
      res.push_back(p->value);
      p = p->next;
    }
    return res;
  }

  vector<Data> forEach() const { return forEachMethod(*this); }
};

vector<Data> traverseByTime(const LinkedHashMap& obj) {
  // TODO
  vector<Data> res;
  Node* p = obj.beg->timeNext;
  while (p != nullptr) {
    Data d;
    d.key = p->key;
    d.value = p->value;
    res.push_back(d);
    p = p->timeNext;
  }
  return res;
}

vector<Data> traverseByIndex(const LinkedHashMap& obj) {
  // TODO
  vector<Data> res;
  for (int i = 0; i < obj.len; i++) {
    Node* p = obj.array[i];
    while (p != nullptr) {
      Data d;
      d.key = p->key;
      d.value = p->value;
      res.push_back(d);
      p = p->next;
    }
  }
  return res;
}

#endif  // FINAL_SRC_HPP