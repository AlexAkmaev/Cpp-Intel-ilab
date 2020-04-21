#pragma once

#include <iostream>
#include <sstream>
#include <unordered_map>
#include <list>

#define TPASTE(x, y) x ## y
#define TPASTE2(x, y) TPASTE(x, y)
#define foreach(i, list) typedef typeof(list) TPASTE2(T,__LINE__); \
                    for(TPASTE2(T,__LINE__)::iterator i = list.begin(); i != list.end(); i++)

class Oper_t { // abstract
protected:
    Oper_t() {}
public:
    virtual ~Oper_t() {}
    virtual void print(int indent=0) = 0;
    virtual int Evaluate() = 0;
};

class Expr_t { // abstract
protected:
    Expr_t() {}
public:
    virtual ~Expr_t() {}
    virtual void print() = 0;
    virtual int Evaluate() = 0;
};


class Block : public Oper_t {
    std::list<Oper_t*> ops;
    void append(Oper_t* op) {
        Block* b = dynamic_cast<Block*>(op);
        if(b) {
            ops.splice(ops.end(), b->ops, b->ops.begin(), b->ops.end());
            delete b;
        }
        else
            ops.push_back(op);
    }
public:
    //int* coun;
    Block* prev_block = nullptr;
    Block() = default;
    explicit Block(Oper_t* op, Block* pbl) { append(op); prev_block = pbl; }
    explicit Block(Oper_t* op1, Oper_t* op2, Block* pbl) { append(op1); append(op2); prev_block = pbl;}
    std::unordered_map<std::string, int> names;
    int size() { return ops.size(); }
    virtual void print(int indent=0) {
        foreach(i, ops) {
            std::cout << std::string(indent, '\t');
            (*i)->print(indent);
        }
    }

    virtual int Evaluate() {
        //names.clear();
        foreach(i, ops) {

            //if ((i) == prev(ops.end()))
              //  names.clear();
            (*i)->Evaluate();
            //std::cout << "i: "  << names.size()<< " \n";
              //std::cout << "i: "  << 17 << " \n";
        }
        std::cout << "size: "  << names.size()<< " \n";
//        for(auto& i : names) {
//            std::cout << "i: " << i.first << "=" << i.second << " ";
//        }
//        std::cout << "|\n";
        clear();
        return 1;
    }

    bool find(std::string id) {
        auto it = names.find(id);
        if(it == names.end())
            return false;
        return true;
    }

    void clear() {
        names.clear();
        ops.clear();
    }

    virtual ~Block() { foreach(i, ops) delete *i; }
};

//bool operator==( Block*& r,  Block*& l) {
//  if (r->names.size() != l->names.size())
//    return false;
//  for(auto& i : r->names){
//    if (i.second != l->names.at(i.first))
//        return false;
//  }
//  return true;
//}


class Exprop : public Oper_t {
    Expr_t* expr = nullptr;
public:
    Exprop() = default;
    explicit Exprop(Expr_t* expr) : expr(expr) {}
    virtual void print(int indent=0) {
        expr->print();
        std::cout << ";" << std::endl;
    }
    virtual int Evaluate() {
        if(!expr)
            return 0;
        return expr->Evaluate();
    }
    virtual ~Exprop() { delete expr; }
};


class Printop : public Oper_t {
    Expr_t* expr;
public:
    explicit Printop(Expr_t* expr) : expr(expr) {}

    virtual void print(int indent=0) {
        std::cout << "print ";
        expr->print();
        std::cout << ";" << std::endl;
    }

    virtual int Evaluate() {
        std::cout << expr->Evaluate() << '\n';
        return 1;
    }

    virtual ~Printop() { delete expr; }
};


class Ifop : public Oper_t {
    Expr_t* cond;
    Block* thenops, *elseops;
    //std::vector<Block*> scopes;
public:
//    explicit Ifop(Expr_t* cond, Oper_t* thenops, Oper_t* elseops) :// std::vector<Block*>& scs) :
//    explicit Ifop(Expr_t* cond, const Block& thenops, const Block& elseops) :// std::vector<Block*>& scs) :
    explicit Ifop(Expr_t* cond, Block* thenops, Block* elseops) :// std::vector<Block*>& scs) :
            cond(cond), thenops(thenops), elseops(elseops) {}
//    virtual void print(int indent=0) {
//        std::cout << "if "; cond->print();  std::cout << " {" << std::endl;
//        thenops.print(indent + 1);
//        if (elseops.size()) {
//            std::cout << std::string(indent, '\t') << "} else {" << std::endl;
//            elseops.print(indent+1);
//        }
//        std::cout << std::string(indent, '\t') << "}" << std::endl;
//    }
//
//    virtual int Evaluate() {
//        if (cond->Evaluate()) {
//            //std::cout << " thenops:" << ((thenops.names.begin())->first) << "\n";
//            int res = thenops.Evaluate();
//            thenops.names.clear();
//            //std::cout << "GG" << thenops.names.size() << "\n";
//            return res;
//        } else {
//            if (elseops.size()) {
//                //std::cout << " c:" << (elseops.coun) << "\n";
//                int res = elseops.Evaluate();
//                elseops.names.clear();
//                return res;
//            }
//        }
//        return 1;
//    }

   virtual void print(int indent=0) {
        std::cout << "if "; cond->print();  std::cout << " {" << std::endl;
        thenops->print(indent + 1);
        if (elseops->size()) {
            std::cout << std::string(indent, '\t') << "} else {" << std::endl;
            elseops->print(indent+1);
        }
        std::cout << std::string(indent, '\t') << "}" << std::endl;
    }

    virtual int Evaluate() {
        if (cond->Evaluate()) {
            int res = thenops->Evaluate();
            thenops->clear();
            return res;
        } else {
            if (elseops->size()) {
                int res = elseops->Evaluate();
                elseops->clear();
                return res;
            }
        }
        return 1;
    }

    virtual ~Ifop() { delete cond; }
};

class Whileop : public Oper_t {
    Expr_t* cond;
    Block* ops;
public:
    explicit Whileop(Expr_t* cond, Block* ops) : cond(cond), ops(ops) {}
    virtual void print(int indent=0) {
        std::cout << "while "; cond->print();  std::cout << " {" << std::endl;
        ops->print(indent + 1);
        std::cout << std::string(indent, '\t') << "}" << std::endl;
    }

    virtual int Evaluate() {
        while (cond->Evaluate()) {
            ops->Evaluate();
        }
        return 1;
    }

    virtual ~Whileop() { delete cond; }
};

//class Whileop : public Oper_t {
//    Expr_t* cond;
//    Block ops;
//public:
//    explicit Whileop(Expr_t* cond, Oper_t* ops) : cond(cond), ops(ops) {}
//    virtual void print(int indent=0) {
//        std::cout << "while "; cond->print();  std::cout << " {" << std::endl;
//        ops.print(indent + 1);
//        std::cout << std::string(indent, '\t') << "}" << std::endl;
//    }
//
//    virtual int Evaluate() {
//        while (cond->Evaluate()) {
//            ops.Evaluate();
//        }
//        return 1;
//    }
//
//    virtual ~Whileop() { delete cond; }
//};


class Binary_expr : public Expr_t {
    const std::string op;
    Expr_t *arg1, *arg2;
public:
    explicit Binary_expr(const char* op, Expr_t *arg1, Expr_t *arg2) :
            op(op), arg1(arg1), arg2(arg2) {}
    virtual void print() {
        std::cout << "(";
        arg1->print();
        std::cout << op;
        arg2->print();
        std::cout << ")";
    }

    virtual int Evaluate() {
        if (op == "==") {
            return arg1->Evaluate() == arg2->Evaluate();
        } else if (op == "<=") {
            return arg1->Evaluate() <= arg2->Evaluate();
        } else if (op == ">=") {
            return arg1->Evaluate() >= arg2->Evaluate();
        } else if (op == "!=") {
            return arg1->Evaluate() != arg2->Evaluate();
        } else if (op == "<") {
            return arg1->Evaluate() < arg2->Evaluate();
        } else if (op == ">") {
            return arg1->Evaluate() > arg2->Evaluate();
        } else if (op == "||") {
            return arg1->Evaluate() || arg2->Evaluate();
        } else if (op == "&&") {
            return arg1->Evaluate() && arg2->Evaluate();
        } else if (op == "+") {
            return arg1->Evaluate() + arg2->Evaluate();
        } else if (op == "-") {
            return arg1->Evaluate() - arg2->Evaluate();
        } else if (op == "*") {
            return arg1->Evaluate() * arg2->Evaluate();
        } else if (op == "/") {
            return arg1->Evaluate() / arg2->Evaluate();
        } else {
            return 0;
        }
    }

    virtual ~Binary_expr() { delete arg1; delete arg2; }
};


class Assign : public Expr_t {
    std::string name;
    Expr_t* value;
    Block*& scope;
public:
    explicit Assign(const std::string& name, Expr_t* value, Block*& sc) :
            name(name), value(value), scope(sc) {}
    virtual void print() { std::cout << name << " = "; value->print(); }
    virtual int Evaluate() {
        int res = value->Evaluate();
        scope->names[name] = res;
        return scope->names[name];
    }
    virtual ~Assign() { delete value; }
};


class Scanfop : public Expr_t {
    std::string name;
    Block*& scope;
public:
    explicit Scanfop(const std::string& name, Block*& sc) :
            name(name), scope(sc) {}
    virtual void print() { std::cout << name << " = ?"; }
    virtual int Evaluate() {
        int value = -17;
        std::cin >> value;
        scope->names[name] = value;
        return value;
    }
};


class Unary_expr : public Expr_t {
    const char* op;
    Expr_t* arg;
public:
    explicit Unary_expr(const char* op, Expr_t* arg) : op(op), arg(arg) {}
    virtual void print() { std::cout << op; arg->print(); }

    virtual int Evaluate() {
        if (op == "-") {
            return -arg->Evaluate();
        } else if (op == "!") {
            return !arg->Evaluate();
        }
        return 0;
    }
    virtual ~Unary_expr() { delete arg; }
};


class Number : public Expr_t {
    int num;
public:
    explicit Number(int val) : num(val) {}
    virtual void print() { std::cout << num; }
    virtual int Evaluate() {
        return num;
    }
};


class Value : public Expr_t {
    std::string id;
    Block*& scope;
    //bool defined;
public:
    explicit Value(const std::string& text, Block*& sc) : id(text), scope(sc) {}
    virtual void print() { std::cout << id; }
    virtual int Evaluate() {
        //defined = scope->find(id);
        return scope->names[id];
    }
};
