#pragma once

#include <iostream>
#include <string>

class Error {
    const std::string& message;
    unsigned line;
protected:
    virtual void error_message(const std::string&, unsigned) const = 0;
};

class Undeclared_value final : public Error {
    const std::string& id;
public:
    explicit Undeclared_value(const std::string& name, const std::string& mes, unsigned lloc) :
        id(name), message(mes), line(lloc) {}
    void error_message() const override{
      std::cerr << "Line:" << line << ": " << id << " is undeclared value\n";
    }
};
