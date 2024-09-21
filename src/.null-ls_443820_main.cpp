#include <ftxui/component/component_base.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/dom/elements.hpp>
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

std::vector<SharedPtr<Resource>> sharedPtrs;

void sharedPtrMenu() {
    std::string name;
    int value;

    while (true) {
        std::cout << "\nSharedPtr Menu:\n";
        std::cout << "1. Create SharedPtr\n";
        std::cout << "2. Create SharedPtr to Existing Resource\n";
        std::cout << "3. Get Resource\n";
        std::cout << "4. Use Count\n";
        std::cout << "5. Reset\n";
        std::cout << "6. List All SharedPtrs\n";
        std::cout << "7. Back to Main Menu\n";
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        if (choice == 1) {
            std::cout << "Enter resource name: ";
            std::cin >> name;
            std::cout << "Enter resource value: ";
            std::cin >> value;
            sharedPtrs.push_back(SharedPtr<Resource>(new Resource(name, value)));
        } else if (choice == 2) {
            if (!sharedPtrs.empty()) {
                std::cout << "Enter index of existing SharedPtr (0-" << sharedPtrs.size() - 1 << "): ";
                int index;
                std::cin >> index;
                if (index >= 0 && index < sharedPtrs.size()) {
                    sharedPtrs.push_back(sharedPtrs[index]);
                    std::cout << "SharedPtr created to existing resource\n";
                } else {
                    std::cout << "Invalid index\n";
                }
            } else {
                std::cout << "No existing SharedPtrs\n";
            }
        } else if (choice == 3) {
            if (!sharedPtrs.empty()) {
                std::cout << "Enter index of SharedPtr (0-" << sharedPtrs.size() - 1 << "): ";
                int index;
                std::cin >> index;
                if (index >= 0 && index < sharedPtrs.size()) {
                    if (sharedPtrs[index]) {
                        sharedPtrs[index]->print();
                    } else {
                        std::cout << "No resource managed by SharedPtr\n";
                    }
                } else {
                    std::cout << "Invalid index\n";
                }
            } else {
                std::cout << "No SharedPtrs\n";
            }
        } else if (choice == 4) {
            if (!sharedPtrs.empty()) {
                std::cout << "Enter index of SharedPtr (0-" << sharedPtrs.size() - 1 << "): ";
                int index;
                std::cin >> index;
                if (index >= 0 && index < sharedPtrs.size()) {
                    std::cout << "Use count: " << sharedPtrs[index].use_count() << std::endl;
                } else {
                    std::cout << "Invalid index\n";
                }
            } else {
                std::cout << "No SharedPtrs\n";
            }
        } else if (choice == 5) {
            if (!sharedPtrs.empty()) {
                std::cout << "Enter index of SharedPtr to reset (0-" << sharedPtrs.size() - 1 << "): ";
                int index;
                std::cin >> index;
                if (index >= 0 && index < sharedPtrs.size()) {
                    sharedPtrs[index].reset();
                    std::cout << "SharedPtr reset\n";
                } else {
                    std::cout << "Invalid index\n";
                }
            } else {
                std::cout << "No SharedPtrs\n";
            }
        } else if (choice == 6) {
            if (!sharedPtrs.empty()) {
                for (size_t i = 0; i < sharedPtrs.size(); ++i) {

                    std::cout << "SharedPtr " << i << ": ";
                    if (sharedPtrs[i]) {
                        sharedPtrs[i]->print();
                    } else {
                        std::cout << "No resource managed by SharedPtr\n";
                    }
                }
            } else {
                std::cout << "No SharedPtrs\n";
            }
        } else if (choice == 7) {
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
