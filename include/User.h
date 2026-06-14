#ifndef USER_H
#define USER_H

#include <string>

class User {
protected:
    std::string name;

public:
    explicit User(const std::string& name);
    virtual ~User() = default;

    std::string getName() const;
    virtual std::string getRole() const = 0;
    void display() const;
};

class Admin : public User {
public:
    explicit Admin(const std::string& name);
    std::string getRole() const override;
};

class Customer : public User {
public:
    explicit Customer(const std::string& name);
    std::string getRole() const override;
};

#endif
