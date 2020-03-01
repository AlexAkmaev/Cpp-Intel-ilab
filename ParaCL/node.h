#pragma once

#include <memory>
#include <map>
#include <stack>
#include <string>
#include "token.h"
using namespace std;

class Node {
public:
  virtual int Evaluate() const = 0;
};

class Variable : public Node {
public:
  explicit Variable(int x);

  int Evaluate() const override;

private:
  int _x;
};

class Op : public Node {
public:
  explicit Op(string val);

  const uint8_t precedence;

  int Evaluate() const override;

  void SetLeft(shared_ptr<Node> node);
  void SetRight(shared_ptr<Node> node);

private:
  string _op;
  shared_ptr<const Node> _left, _right;
};
