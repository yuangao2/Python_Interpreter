#include "node.h"
#include "poolOfNodes.h"
#include "tableManager.h"
#include <cmath>
#include <iomanip>

class IntLiteral;

class Literal : public Node {
public:
  virtual ~Literal() {}

  virtual const Literal* operator+(const Literal& rhs) const =0;
  virtual const Literal* opPlus(long double) const =0;
  virtual const Literal* opPlus(int) const =0;

  virtual const Literal* operator*(const Literal& rhs) const =0;
  virtual const Literal* opMult(long double) const =0;
  virtual const Literal* opMult(int) const =0;

  virtual const Literal* operator-(const Literal& rhs) const =0;
  virtual const Literal* opSubt(long double) const =0;
  virtual const Literal* opSubt(int) const =0;

  virtual const Literal* operator/(const Literal& rhs) const =0;
  virtual const Literal* opDiv(long double) const =0;
  virtual const Literal* opDiv(int) const =0;

  virtual const Literal* operator%(const Literal& rhs) const =0;
  virtual const Literal* opMod(long double) const =0;
  virtual const Literal* opMod(int) const =0;

  virtual const Literal* floorDivide(const Literal& rhs) const =0;
  virtual const Literal* opFlrDiv(long double) const =0;
  virtual const Literal* opFlrDiv(int) const =0;

  virtual const Literal* pow(const Literal& rhs) const =0;
  virtual const Literal* opPow(long double) const =0;
  virtual const Literal* opPow(int) const =0;

  virtual const Literal* operator<<(const Literal& rhs) const =0;
  virtual const Literal* opLshift(long double) const =0;
  virtual const Literal* opLshift(int) const =0;

  virtual const Literal* operator>>(const Literal& rhs) const =0;
  virtual const Literal* opRshift(long double) const =0;
  virtual const Literal* opRshift(int) const =0;

  virtual const Literal* operator==(const Literal& rhs) const =0;
  virtual const Literal* opEqEqual(long double) const =0;
  virtual const Literal* opEqEqual(int) const =0;

  virtual const Literal* operator<(const Literal& rhs) const =0;
  virtual const Literal* opLess(long double) const =0;
  virtual const Literal* opLess(int) const =0;

  virtual const Literal* operator>(const Literal& rhs) const =0;
  virtual const Literal* opGreater(long double) const =0;
  virtual const Literal* opGreater(int) const =0;

  virtual const Literal* operator<=(const Literal& rhs) const =0;
  virtual const Literal* opLessEqual(long double) const =0;
  virtual const Literal* opLessEqual(int) const =0;

  virtual const Literal* operator>=(const Literal& rhs) const =0;
  virtual const Literal* opGreaterEqual(long double) const =0;
  virtual const Literal* opGreaterEqual(int) const =0;

  virtual const Literal* operator!=(const Literal& rhs) const =0;
  virtual const Literal* opNotEqual(long double) const =0;
  virtual const Literal* opNotEqual(int) const =0;

  virtual const Literal* eval() const = 0;
  virtual void print() const {
    std::cout << "No Way" << std::endl;
  }
};

class FloatLiteral: public Literal {
public:
  FloatLiteral(long double _val): val(_val) {}

  virtual const Literal* operator+(const Literal& rhs) const  {
    return rhs.opPlus(val);
  }
  virtual const Literal* opPlus(long double lhs) const  {
    const Literal* node = new FloatLiteral(lhs + val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opPlus(int lhs) const  {
    const Literal* node = new FloatLiteral(lhs + val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* operator-(const Literal& rhs) const  {
    return rhs.opSubt(val);
  }
  virtual const Literal* opSubt(long double lhs) const  {
    const Literal* node = new FloatLiteral(lhs - val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opSubt(int lhs) const  {
    const Literal* node = new FloatLiteral(lhs - val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* operator*(const Literal& rhs) const  {
    return rhs.opMult(val);
  }
  virtual const Literal* opMult(long double lhs) const  {
    const Literal* node = new FloatLiteral(lhs * val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opMult(int lhs) const  {
    const Literal* node = new FloatLiteral(static_cast<long double>(lhs) * val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* operator/(const Literal& rhs) const  {
    return rhs.opDiv(val);
  }
  virtual const Literal* opDiv(long double lhs) const  {
    if ( val == 0 ) throw std::string("Zero Division Error");
    const Literal* node = new FloatLiteral(lhs / val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opDiv(int lhs) const  {
    if ( val == 0 ) throw std::string("Zero Division Error");
    const Literal* node = new FloatLiteral(lhs / val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* operator%(const Literal& rhs) const {
    return rhs.opMod(val);
  }
  virtual const Literal* opMod(long double lhs) const {
    if ( val == 0 ) throw std::string("Zero Division Error");
    const Literal* node = new FloatLiteral(std::fmod(std::fmod(lhs, val) + val, val));
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opMod(int lhs) const {
    if ( val == 0 ) throw std::string("Zero Division Error");
    const Literal* node = new FloatLiteral(std::fmod(std::fmod(lhs, val) + val, val));
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* floorDivide(const Literal& rhs) const {
    return rhs.opFlrDiv(val);
  }
  virtual const Literal* opFlrDiv(long double lhs) const {
    if ( val == 0) throw std::string("Zero Division Error");
    const Literal* node = new FloatLiteral(std::floor(lhs / val));
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opFlrDiv(int lhs) const {
    if ( val == 0) throw std::string("Zero Division Error");
    const Literal* node = new FloatLiteral(std::floor(lhs / val));
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* pow(const Literal& rhs) const {
    return rhs.opPow(val);
  }
  virtual const Literal* opPow(long double lhs) const {
    const Literal* node = new FloatLiteral(std::pow(lhs, val));
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opPow(int lhs) const {
    const Literal* node = new FloatLiteral(std::pow(lhs, val));
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* operator<<(const Literal& rhs) const {
    return rhs.opLshift(val);
  }
  virtual const Literal* opLshift(long double lhs) const {
    std::cout << "TypeError: unsupported operand type(s) for <<: 'float' and 'float'" << std::endl;
    return NULL;
  }
  virtual const Literal* opLshift(int lhs) const {
    std::cout << "TypeError: unsupported operand type(s) for <<: 'int' and 'float'" << std::endl;
    return NULL;
  }

  virtual const Literal* operator>>(const Literal& rhs) const {
    return rhs.opRshift(val);
  }
  virtual const Literal* opRshift(long double lhs) const {
    std::cout << "TypeError: unsupported operand type(s) for <<: 'float' and 'float'" << std::endl;
    return NULL;
  }
  virtual const Literal* opRshift(int lhs) const {
    std::cout << "TypeError: unsupported operand type(s) for <<: 'int' and 'float'" << std::endl;
    return NULL;
  }

  virtual const Literal* operator==(const Literal& rhs) const {
    return rhs.opEqEqual(val);
  }
  virtual const Literal* opEqEqual(long double lhs) const {
    int equalFlag = 0;
    if (std::abs(lhs - val) < 1e-6) {
      equalFlag = 1;
    }
    const Literal* node = new FloatLiteral(equalFlag);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opEqEqual(int lhs) const {
    const Literal* node = new FloatLiteral(std::floor(val) == lhs);
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* operator<(const Literal& rhs) const {
    return rhs.opLess(val);
  }
  virtual const Literal* opLess(long double lhs) const {
    const Literal* node = new FloatLiteral(lhs < val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opLess(int lhs) const {
    const Literal* node = new FloatLiteral(lhs < val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* operator>(const Literal& rhs) const {
    return rhs.opGreater(val);
  }
  virtual const Literal* opGreater(long double lhs) const {
    const Literal* node = new FloatLiteral(lhs > val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opGreater(int lhs) const {
    const Literal* node = new FloatLiteral(lhs > val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* operator<=(const Literal& rhs) const {
    return rhs.opLessEqual(val);
  }
  virtual const Literal* opLessEqual(long double lhs) const {
    const Literal* node = new FloatLiteral(lhs <= val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opLessEqual(int lhs) const {
    const Literal* node = new FloatLiteral(lhs <= val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* operator>=(const Literal& rhs) const {
    return rhs.opGreaterEqual(val);
  }
  virtual const Literal* opGreaterEqual(long double lhs) const {
    const Literal* node = new FloatLiteral(lhs >= val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opGreaterEqual(int lhs) const {
    const Literal* node = new FloatLiteral(lhs >= val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* operator!=(const Literal& rhs) const {
    return rhs.opNotEqual(val);
  }
  virtual const Literal* opNotEqual(long double lhs) const {
    const Literal* node = new FloatLiteral(lhs > val || lhs < val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opNotEqual(int lhs) const {
    const Literal* node = new FloatLiteral(std::floor(lhs) != val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* eval() const { return this; }
  virtual void print() const {
    if (std::abs(std::floor(val) - val) < 1e-6 && val < 1e+16) {
      std::cout << val << ".0" << std::endl;
    }
    else {
      std::cout << std::setprecision(12) << val << std::endl;
    }
  }
  long double getValue() const { return val; }
private:
  long double val;
};


class IntLiteral: public Literal {
public:
  IntLiteral(int _val): val(_val) {}

  virtual const Literal* operator+(const Literal& rhs) const  {
    return rhs.opPlus(val);
  }
  virtual const Literal* opPlus(long double lhs) const  {
    const Literal* node = new FloatLiteral(static_cast<long double>(val) + lhs);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opPlus(int lhs) const  {
    const Literal* node = new IntLiteral(lhs + val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* operator-(const Literal& rhs) const  {
    return rhs.opSubt(val);
  }
  virtual const Literal* opSubt(long double lhs) const  {
    const Literal* node = new FloatLiteral(lhs - val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opSubt(int lhs) const  {
    const Literal* node = new IntLiteral(lhs - val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* operator*(const Literal& rhs) const  {
    return rhs.opMult(val);
  }
  virtual const Literal* opMult(long double lhs) const  {
    const Literal* node = new FloatLiteral(lhs * val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opMult(int lhs) const  {
    const Literal* node = new IntLiteral(lhs * val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* operator/(const Literal& rhs) const  {
    return rhs.opDiv(val);
  }
  virtual const Literal* opDiv(long double lhs) const  {
    if ( val == 0 ) throw std::string("Zero Division Error");
    const Literal* node = new FloatLiteral(lhs / val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opDiv(int lhs) const  {
    if ( val == 0 ) throw std::string("Zero Division Error");
    int res = lhs / val;
    if (lhs * val < 0) {
      if (lhs % val != 0) {
        res--;
      }
    }
    const Literal* node = new IntLiteral(res);
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* operator%(const Literal& rhs) const {
    return rhs.opMod(val);
  }
  virtual const Literal* opMod(long double lhs) const {
    if ( val == 0 ) throw std::string("Zero Division Error");
    const Literal* node = new FloatLiteral(std::fmod(std::fmod(lhs, val) + val, val));
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opMod(int lhs) const {
    if ( val == 0 ) throw std::string("Zero Division Error");
    const Literal* node = new IntLiteral((lhs % val + val) % val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* floorDivide(const Literal& rhs) const {
    return rhs.opFlrDiv(val);
  }
  virtual const Literal* opFlrDiv(long double lhs) const {
    if ( val == 0) throw std::string("Zero Division Error");
    const Literal* node = new FloatLiteral(std::floor(lhs / val));
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opFlrDiv(int lhs) const {
    return opDiv(lhs);
  }

  virtual const Literal* pow(const Literal& rhs) const {
    return rhs.opPow(val);
  }
  virtual const Literal* opPow(long double lhs) const {
    const Literal* node = new FloatLiteral(std::pow(lhs, val));
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opPow(int lhs) const {
    const Literal* node = new IntLiteral(std::pow(lhs, val));
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* operator<<(const Literal& rhs) const {
    return rhs.opLshift(val);
  }
  virtual const Literal* opLshift(long double lhs) const {
    std::cout << "TypeError: unsupported operand type(s) for <<: 'float' and 'int'" << std::endl;
    return NULL;
  }
  virtual const Literal* opLshift(int lhs) const {
    const Literal* node = new IntLiteral(lhs * std::pow(2, val));
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* operator>>(const Literal& rhs) const {
    return rhs.opRshift(val);
  }
  virtual const Literal* opRshift(long double lhs) const {
    std::cout << "TypeError: unsupported operand type(s) for <<: 'float' and 'int'" << std::endl;
    return NULL;
  }
  virtual const Literal* opRshift(int lhs) const {
    const Literal* node = new IntLiteral(lhs / std::pow(2, val));
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* operator==(const Literal& rhs) const {
    return rhs.opEqEqual(val);
  }
  virtual const Literal* opEqEqual(long double lhs) const {
    int equalFlag = 0;
    if (std::abs(lhs - val) < 1e-6) {
      equalFlag = 1;
    }
    const Literal* node = new IntLiteral(equalFlag);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opEqEqual(int lhs) const {
    const Literal* node = new IntLiteral(lhs == val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* operator<(const Literal& rhs) const {
    return rhs.opLess(val);
  }
  virtual const Literal* opLess(long double lhs) const {
    const Literal* node = new IntLiteral(lhs < val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opLess(int lhs) const {
    const Literal* node = new IntLiteral(lhs < val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* operator>(const Literal& rhs) const {
    return rhs.opGreater(val);
  }
  virtual const Literal* opGreater(long double lhs) const {
    const Literal* node = new IntLiteral(lhs > val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opGreater(int lhs) const {
    const Literal* node = new IntLiteral(lhs > val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* operator<=(const Literal& rhs) const {
    return rhs.opLessEqual(val);
  }
  virtual const Literal* opLessEqual(long double lhs) const {
    const Literal* node = new IntLiteral(lhs <= val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opLessEqual(int lhs) const {
    const Literal* node = new IntLiteral(lhs <= val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* operator>=(const Literal& rhs) const {
    return rhs.opGreaterEqual(val);
  }
  virtual const Literal* opGreaterEqual(long double lhs) const {
    const Literal* node = new IntLiteral(lhs >= val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opGreaterEqual(int lhs) const {
    const Literal* node = new IntLiteral(lhs >= val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* operator!=(const Literal& rhs) const {
    return rhs.opNotEqual(val);
  }
  virtual const Literal* opNotEqual(long double lhs) const {
    const Literal* node = new IntLiteral(std::floor(lhs) != val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opNotEqual(int lhs) const {
    const Literal* node = new IntLiteral(lhs != val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* eval() const { return this; }
  virtual void print() const {
    // std::cout << "The result is: " << val << std::endl;
    std::cout << val << std::endl;
  }
  int getValue() const { return val; }
private:
  int val;
};
