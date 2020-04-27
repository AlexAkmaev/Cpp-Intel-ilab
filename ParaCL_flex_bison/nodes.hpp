#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>

class Oper_t { // abstract
protected:
    Oper_t() {}
public:
    virtual ~Oper_t() {}
    virtual void print(int indent = 0) const noexcept = 0;
    virtual int Evaluate() = 0;
};

class Expr_t { // abstract
protected:
    Expr_t() {}
public:
    virtual ~Expr_t() {}
    virtual void print() const noexcept = 0;
    virtual int Evaluate() = 0;
};


class Block final : public Oper_t {
    std::vector<Oper_t*> ops;
public:
    std::unordered_map<std::string, int> names;

    void append(Oper_t* op) {
        Block* b = dynamic_cast<Block*>(op);
        if(b) {
            ops.insert(ops.end(), b->ops.begin(), b->ops.end());
        }
        else
            ops.push_back(op);
    }

    Block* prev_block = nullptr;
    explicit Block(Block*& prev) : prev_block(prev) {};
    explicit Block(Oper_t* op, Block* pbl) { append(op); prev_block = pbl; }
    explicit Block(Oper_t* op1, Oper_t* op2, Block* pbl) { append(op1); append(op2); prev_block = pbl;}
    explicit Block(Oper_t* op1, Oper_t* op2) { append(op1); append(op2); }
    int size() const noexcept{ return ops.size(); }
    void print(int indent=0) const noexcept override{
        for(auto i = ops.begin(), it_end = ops.end(); i != it_end; ++i) {
            std::cout << std::string(indent, '\t');
            (*i)->print(indent);
        }
    }

    int Evaluate() override{
        for(auto i = ops.begin(), it_end = ops.end(); i != it_end; ++i) {
            (*i)->Evaluate();
        }
        return 1;
    }

    bool find(const std::string& id) const noexcept{
        auto it = names.find(id);
        if(it == names.end())
            return false;
        return true;
    }

    Block* find_block(const std::string& id) noexcept{
        Block* res = this;
        bool found = false;
        while(!found && res != nullptr) {
            if(!find(id)) {
                res = res->prev_block;
            }
            else
                found = true;
        }
        if(found)
            return res;
        return this;
    }

    void clear() {
        names.clear();
        ops.clear();
    }

     ~Block() {
        for(auto i = ops.begin(), it_end = ops.end(); i != it_end; ++i)
            delete *i;
    }
};


class Exprop final : public Oper_t {
    Expr_t* expr = nullptr;
public:
    Exprop() = default;
    explicit Exprop(Expr_t* expr) : expr(expr) {}
    void print(int indent = 0) const noexcept override{
        expr->print();
        std::cout << ";" << std::endl;
    }
    int Evaluate() override{
        if(!expr)
            return 0;
        return expr->Evaluate();
    }
     ~Exprop() { delete expr; }
};


class Printop final : public Oper_t {
    Expr_t* expr;
public:
    explicit Printop(Expr_t* expr) : expr(expr) {}

    void print(int indent=0) const noexcept override{
        std::cout << "print ";
        expr->print();
        std::cout << ";" << std::endl;
    }

    int Evaluate() override{
        std::cout << expr->Evaluate() << '\n';
        return 1;
    }

     ~Printop() { delete expr; }
};


class Ifop final : public Oper_t {
    Expr_t* cond;
    Block* thenops, *elseops;
public:
    explicit Ifop(Expr_t* cond, Block* thenops, Block* elseops) :
            cond(cond), thenops(thenops), elseops(elseops) {}

    void print(int indent = 0) const noexcept override{
        std::cout << "if "; cond->print();  std::cout << " {" << std::endl;
        thenops->print(indent + 1);
        if (elseops->size()) {
            std::cout << std::string(indent, '\t') << "} else {" << std::endl;
            elseops->print(indent+1);
        }
        std::cout << std::string(indent, '\t') << "}" << std::endl;
    }

    int Evaluate() override{
        if (cond->Evaluate()) {
            int res = thenops->Evaluate();
            return res;
        }
//        else {
//            if (elseops->size()) {
//                int res = elseops->Evaluate();
//                //elseops->clear();
//                return res;
//            }
//        }
        return 1;
    }

     ~Ifop() { delete cond; }
};

class Whileop final : public Oper_t {
    Expr_t* cond;
    Block* ops;
public:
    explicit Whileop(Expr_t* cond, Block* ops) : cond(cond), ops(ops) {}
    void print(int indent = 0) const noexcept override{
        std::cout << "while "; cond->print();  std::cout << " {" << std::endl;
        ops->print(indent + 1);
        std::cout << std::string(indent, '\t') << "}" << std::endl;
    }

    int Evaluate() override{
        while (cond->Evaluate()) {
            ops->Evaluate();
        }
        return 1;
    }

     ~Whileop() { delete cond; }
};


class Binary_expr final : public Expr_t {
    const std::string op;
    Expr_t *arg1, *arg2;
public:
    explicit Binary_expr(const char* op, Expr_t *arg1, Expr_t *arg2) :
            op(op), arg1(arg1), arg2(arg2) {}
    void print() const noexcept override{
        std::cout << "(";
        arg1->print();
        std::cout << op;
        arg2->print();
        std::cout << ")";
    }

    int Evaluate() override{
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

     ~Binary_expr() { delete arg1; delete arg2; }
};


class Assign final : public Expr_t {
    std::string name;
    Expr_t* value;
    Block*& scope;
public:
    explicit Assign(const std::string& name, Expr_t* value, Block*& sc) :
            name(name), value(value), scope(sc) {}
    void print() const noexcept override{
        std::cout << name << " = "; value->print();
    }
    int Evaluate() override{
        Block* cur_scope = scope->find_block(name);
        int res = value->Evaluate();
        cur_scope->names[name] = res;
        return res;
    }
     ~Assign() { delete value; }
};


class Scanfop final : public Expr_t {
    std::string id;
    Block*& scope;
public:
    explicit Scanfop(const std::string& name, Block*& sc) :
            id(name), scope(sc) {}
    void print() const noexcept override{
        std::cout << id << " = ?";
    }
    int Evaluate() override{
        Block* cur_scope = scope->find_block(id);
        int value = -1;
        std::cin >> value;
        cur_scope->names[id] = value;
        return value;
    }
};


class Unary_expr final : public Expr_t {
    const char* op;
    Expr_t* arg;
public:
    explicit Unary_expr(const char* op, Expr_t* arg) : op(op), arg(arg) {}
    void print() const noexcept override{
        std::cout << op; arg->print();
    }

    int Evaluate() override{
        if (op == "-") {
            return -arg->Evaluate();
        } else if (op == "!") {
            return !arg->Evaluate();
        }
        return 0;
    }
     ~Unary_expr() { delete arg; }
};


class Number final : public Expr_t {
    int num;
public:
    explicit Number(int val) : num(val) {}
    void print() const noexcept override{ std::cout << num; }
    int Evaluate() override{
        return num;
    }
};


class Value final : public Expr_t {
    std::string id;
    Block*& scope;
    const unsigned line;
public:
    explicit Value(const std::string& text, Block*& sc, unsigned lloc) : id(text), scope(sc), line(lloc) {}  //&
    void print() const noexcept override{ std::cout << id; }
    int Evaluate()  override{
        Block* cur_scope = scope->find_block(id);
        if(!cur_scope->find(id)) {
            std::cerr << "Error. Line:" << line << ": " << id << " is undeclared value\n";
        }
        return cur_scope->names[id];
    }
};
