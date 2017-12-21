#ifndef FUNCTIONTABLE__H
#define FUNCTIONTABLE__H

#include <iostream>
#include <string>
#include <map>

class Node;

class FunctionTable {
public:
  FunctionTable() : paramTable(), funcTable() {}
  bool found(const std::string& name) const;
  void insert(const std::string& name, const Node* suite);
  void insertParam(const std::string& name, const Node* params);
  const Node* getValue(const std::string& name) const;
  const Node* getParam(const std::string& name) const;
  void display() const;
private:
  std::map<std::string, const Node*> paramTable;
  std::map<std::string, const Node*> funcTable;
};

#endif
