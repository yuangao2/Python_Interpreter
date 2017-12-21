#include <algorithm>
#include "symbolTable.h"
#include "literal.h"

bool SymbolTable::found(const std::string& name) const {
  std::map<std::string, const Literal*>::const_iterator it = symbolTable.find(name);
  return it != symbolTable.end();
}

const Literal* SymbolTable::getValue(const std::string& name) const {
  std::map<std::string, const Literal*>::const_iterator it = symbolTable.find(name);
  if (it == symbolTable.end()) throw name + std::string(" not found");
  return it->second;
}

void SymbolTable::insert(const std::string& name, const Literal* val) {
  symbolTable[name] = val;
}

void SymbolTable::display() const {
  std::cout << "SymbolTable: " << std::endl;
  std::map<std::string, const Literal*>::const_iterator it = symbolTable.begin();
  while (it != symbolTable.end()) {
    std::cout << it->first << std::endl;
    it++;
  }
}
