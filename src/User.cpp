#include "User.h"

#include <iostream>

User::User(const std::string& name) : name(name) {}

std::string User::getName() const {
    return name;
}

void User::display() const {
    std::cout << getRole() << " | " << name << std::endl;
}

Admin::Admin(const std::string& name) : User(name) {}

std::string Admin::getRole() const {
    return "管理員";
}

Customer::Customer(const std::string& name) : User(name) {}

std::string Customer::getRole() const {
    return "顧客";
}
