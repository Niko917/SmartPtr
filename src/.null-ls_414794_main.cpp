#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include "../include/WeakPtr.hpp"
#include "../include/SharedPtr.hpp"
#include "../include/UniquePtr.hpp"


class Resource {
public:
    Resource(const std::string& name, int value) : name_(name), value_(value) {
        std::cout << "Resource " << name_ << " created with value " << value_ << std::endl;
    }

    ~Resource() {
        std::cout << "Resource " << name_ << " destroyed" << std::endl;
    }

    void print() const {
        std::cout << "Resource " << name_ << " has value " << value_ << std::endl;
    }

private:
    std::string name_;
    int value_;
};

void sharedPtrMenu() {
    SharedPtr<Resource> sharedPtr;
    std::string name;
    int value;

    while (true) {
        std::cout << "\nSharedPtr Menu:\n";
        std::cout << "1. Create SharedPtr\n";
        std::cout << "2. Get Resource\n";
        std::cout << "3. Use Count\n";
        std::cout << "4. Reset\n";
        std::cout << "5. Back to Main Menu\n";
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        if (choice == 1) {
            std::cout << "Enter resource name: ";
            std::cin >> name;
            std::cout << "Enter resource value: ";
            std::cin >> value;
            sharedPtr.reset(new Resource(name, value));
        } else if (choice == 2) {
            if (sharedPtr) {
                sharedPtr->print();
            } else {
                std::cout << "No resource managed by SharedPtr\n";
            }
        } else if (choice == 3) {
            std::cout << "Use count: " << sharedPtr.use_count() << std::endl;
        } else if (choice == 4) {
            sharedPtr.reset();
            std::cout << "SharedPtr reset\n";
        } else if (choice == 5) {
            break;
        } else {
            std::cout << "Invalid choice\n";
        }
    }
}

void weakPtrMenu() {
    SharedPtr<Resource> sharedPtr;
    WeakPtr<Resource> weakPtr;
    std::string name;
    int value;

    while (true) {
        std::cout << "\nWeakPtr Menu:\n";
        std::cout << "1. Create SharedPtr\n";
        std::cout << "2. Create WeakPtr from SharedPtr\n";
        std::cout << "3. Lock WeakPtr\n";
        std::cout << "4. Use Count\n";
        std::cout << "5. Expired\n";
        std::cout << "6. Back to Main Menu\n";
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        if (choice == 1) {
            std::cout << "Enter resource name: ";
            std::cin >> name;
            std::cout << "Enter resource value: ";
            std::cin >> value;
            sharedPtr.reset(new Resource(name, value));
        } else if (choice == 2) {
            if (sharedPtr) {
                weakPtr = sharedPtr;
                std::cout << "WeakPtr created from SharedPtr\n";
            } else {
                std::cout << "No resource managed by SharedPtr\n";
            }
        } else if (choice == 3) {
            SharedPtr<Resource> lockedPtr = weakPtr.lock();
            if (lockedPtr) {
                lockedPtr->print();
            } else {
                std::cout << "WeakPtr expired\n";
            }
        } else if (choice == 4) {
            std::cout << "Use count: " << weakPtr.use_count() << std::endl;
        } else if (choice == 5) {
            std::cout << "Expired: " << (weakPtr.expired() ? "Yes" : "No") << std::endl;
        } else if (choice == 6) {
            break;
        } else {
            std::cout << "Invalid choice\n";
        }
    }
}

void uniquePtrMenu() {
    UniquePtr<Resource> uniquePtr;
    std::string name;
    int value;

    while (true) {
        std::cout << "\nUniquePtr Menu:\n";
        std::cout << "1. Create UniquePtr\n";
        std::cout << "2. Get Resource\n";
        std::cout << "3. Release\n";
        std::cout << "4. Reset\n";
        std::cout << "5. Back to Main Menu\n";
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        if (choice == 1) {
            std::cout << "Enter resource name: ";
            std::cin >> name;
            std::cout << "Enter resource value: ";
            std::cin >> value;
            uniquePtr.reset(new Resource(name, value));
        } else if (choice == 2) {
            if (uniquePtr.get()) {
                uniquePtr->print();
            } else {
                std::cout << "No resource managed by UniquePtr\n";
            }
        } else if (choice == 3) {
            Resource* ptr = uniquePtr.release();
            if (ptr) {
                std::cout << "Resource released\n";
            } else {
                std::cout << "No resource managed by UniquePtr\n";
            }
        } else if (choice == 4) {
            uniquePtr.reset();
            std::cout << "UniquePtr reset\n";
        } else if (choice == 5) {
            break;
        } else {
            std::cout << "Invalid choice\n";
        }
    }
}

int main() {
    while (true) {
        std::cout << "\nMain Menu:\n";
        std::cout << "1. SharedPtr Menu\n";
        std::cout << "2. WeakPtr Menu\n";
        std::cout << "3. UniquePtr Menu\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        if (choice == 1) {
            sharedPtrMenu();
        } else if (choice == 2) {
            weakPtrMenu();
        } else if (choice == 3) {
            uniquePtrMenu();
        } else if (choice == 4) {
            break;
        } else {
            std::cout << "Invalid choice\n";
        }
    }

    return 0;
}
