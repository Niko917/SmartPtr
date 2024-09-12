#include <iostream>
#include "../include/UniquePtr.hpp"

int main() {
    UniquePtr<int> ptr(new int(42));
    std::cout << "Value: " << *ptr << std::endl;
    return 0;
}
