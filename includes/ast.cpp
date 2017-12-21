#include <iostream>
#include <typeinfo>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include "ast.h"
#include "tableManager.h"

const Literal* IdentNode::eval() const {
  TableManager& tm = TableManager::getInstance();
  int scope = tm.getCurrentScope();
  while (tm.getCurrentScope() >= 0) {
    if (tm.checkSymbol(ident)) {
      const Literal* val = tm.getSymbol(ident);
      tm.setCurrentScope(scope);
      return val;
    }
    else {
      if (tm.getCurrentScope() == 0) {
        tm.setCurrentScope(scope);
        std::cout << "NameError: name '" << ident << "' is not defined" << std::endl;
        return NULL;
      }
      else {
        tm.popScope();
      }
    }
  }
  return NULL;
}

const Literal* SuiteNode::eval() const {
  const Literal* result = NULL;
  for (const Node* n : stmts) {
    if (n) {
      if (TableManager::getInstance().getReturned()) {
        break;
      }
      result = n->eval();
      const ReturnNode* ptr = dynamic_cast<const ReturnNode*>(n);
      if (ptr) {
        TableManager::getInstance().setReturned(true);
        break;
      }
    }
  }
  return result;
}

const Literal* FuncNode::eval() const {
  TableManager& tm = TableManager::getInstance();
  tm.insertFunction(ident, parameter, suite);
  return NULL;
}

const Literal* ParaNode::eval() const {
  return NULL;
}

const Literal* CallNode::eval() const {
  TableManager& tm = TableManager::getInstance();
  const Literal* result = NULL;
  if (tm.checkFuncName(ident)) {
    std::vector<Node*> paramVec;
    const SuiteNode *st = static_cast<const SuiteNode*> (tm.getSuite(ident));
    if ( tm.getParam(ident) ) {
      paramVec = static_cast<const ParaNode*>(tm.getParam(ident))->getValue();
      std::vector<Node*> argVec;
      if (argNode ) {
        argVec = static_cast<const ArgNode*>(argNode)->getValue();
      }
      std::vector<const Literal*> argVal;
      for (unsigned int i = 0; i < paramVec.size(); i++) {
        argVal.push_back(argVec[i]->eval());
      }
      tm.pushScope(ident);
      for (unsigned int i = 0; i < paramVec.size(); i++) {
        const std::string n = static_cast<IdentNode*>(paramVec[i])->getIdent();
        TableManager::getInstance().insertSymbol(n, argVal[i]);
      }
    }
    result = st->eval();
    tm.setReturned(false);
    tm.popScope();
  }
  return result;
}

const Literal* ArgNode::eval() const {
  return NULL;
}

const Literal* PrintNode::eval() const {
  const Literal* temp = NULL;
  if (node) {
    temp = node->eval();
  }
  if (temp) {
    temp->print();
  }
  else {
    std::cout << "None" << std::endl;
  }
  return NULL;
}

const Literal* IfNode::eval() const {
  int testFlag;
  const IntLiteral* ptr = dynamic_cast<const IntLiteral*>(test->eval());
  
  if (ptr) {
    testFlag = ptr->getValue();
  }
  else {
    const FloatLiteral* fptr = static_cast<const FloatLiteral*>(test->eval());
    testFlag = static_cast<int>(fptr->getValue());
  }
  const Literal* res = nullptr;

  if (testFlag) {
    res = suite->eval();
  }
  else {
    res = elseSuite->eval();
  }

  return res;
}

const Literal* ReturnNode::eval() const {
  if (result == NULL) {
    return NULL;
  }
  else {
    return result->eval();
  }
}

const Literal* MinusUnaryNode::eval() const {
  if (!right) {
    throw std::string("error");
  }
  const Literal* x = right->eval();
  const Literal* zero = new IntLiteral(0);
  return *zero-(*x);
}

const Literal* TildeUnaryNode::eval() const {
  if (!right) {
    throw std::string("error");
  }
  const Literal* x = right->eval();
  const Literal* minusOne = new IntLiteral(-1);
  return *minusOne-(*x);
}

AsgBinaryNode::AsgBinaryNode(Node* left, Node* right) :
  BinaryNode(left, right) {}

const Literal* AsgBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("error");
  }
  const Literal* res = right->eval();
  const std::string n = static_cast<IdentNode*>(left)->getIdent();
  TableManager::getInstance().insertSymbol(n, res);
  return res;
}

const Literal* AddBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("error");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return (*x+*y);
}

const Literal* SubBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("error");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return ((*x)-(*y));
}

const Literal* MulBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("error");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return ((*x)*(*y));
}

const Literal* DivBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("error");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return ((*x)/(*y));
}

const Literal* ModBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("error");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return ((*x)%(*y));
}

const Literal* FlrDivBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("error");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return x->floorDivide(*y);
}

const Literal* PowBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("error");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return x->pow(*y);
}

const Literal* LShiftBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("error");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return (*x)<<(*y);
}

const Literal* RShiftBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("error");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return (*x)>>(*y);
}

const Literal* EqEqualBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("error");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return (*x)==(*y);
}

const Literal* LessBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("error");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return (*x)<(*y);
}

const Literal* GreaterBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("error");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return (*x)>(*y);
}

const Literal* LessEqualBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("error");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return (*x)<=(*y);
}

const Literal* GreaterEqualBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("error");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return (*x)>=(*y);
}

const Literal* NotEqualBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("error");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return (*x)!=(*y);
}
