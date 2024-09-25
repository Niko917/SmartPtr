#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <chrono>
#include "../include/WeakPtr.hpp"
#include "../include/SharedPtr.hpp"
#include "../include/UniquePtr.hpp"


class ResourceInt {
public:
    ResourceInt(const std::string& name, int value) : name_(name), value_(value) {
        std::cout << "\nResource " << name_ << " created with value " << value_ << std::endl;
    }

    ~ResourceInt() {
        std::cout << "\nResource " << name_ << " destroyed" << std::endl;
    }

    void print() const {
        std::cout << "\nResource " << name_ << " has value " << value_ << std::endl;
    }

private:
    std::string name_;
    int value_;
};

class ResourceString {
public:
    ResourceString(const std::string& name, const std::string& value) : name_(name), value_(value) {
        std::cout << "\nResource " << name_ << " created with value " << value_ << std::endl;
    }

    ~ResourceString() {
        std::cout << "\nResource " << name_ << " destroyed" << std::endl;
    }

    void print() const {
        std::cout << "\nResource " << name_ << " has value " << value_ << std::endl;
    }

private:
    std::string name_;
    std::string value_;
};

class ResourceVectorInt {
public:
    ResourceVectorInt(const std::string& name, const std::vector<int>& value) : name_(name), value_(value) {
        std::cout << "\nResource " << name_ << " created with value ";
        for (int v : value_) std::cout << v << " ";
        std::cout << std::endl;
    }

    ~ResourceVectorInt() {
        std::cout << "\nResource " << name_ << " destroyed" << std::endl;
    }

    void print() const {
        std::cout << "\nResource " << name_ << " has value ";
        for (int v : value_) std::cout << v << " ";
        std::cout << std::endl;
    }

private:
    std::string name_;
    std::vector<int> value_;
};

std::vector<SharedPtr<ResourceInt>> sharedPtrsInt;
std::vector<SharedPtr<ResourceString>> sharedPtrsString;
std::vector<SharedPtr<ResourceVectorInt>> sharedPtrsVectorInt;

void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void sharedPtrMenu() {
    std::string name;
    int type;
    int count;
    size_t originalSizeInt = sharedPtrsInt.size();
    size_t originalSizeString = sharedPtrsString.size();
    size_t originalSizeVectorInt = sharedPtrsVectorInt.size();

    while (true) {
        std::cout << "\nSharedPtr Menu:\n";
        std::cout << "\n1.  ➤   Create SharedPtr\n";
        std::cout << "\n2.  ➤   Create SharedPtr to Existing Resource\n";
        std::cout << "\n3.  ➤   Get Resource\n";
        std::cout << "\n4.  ➤   Use Count\n";
        std::cout << "\n5.  ➤   Reset\n";
        std::cout << "\n6.  ➤   List All SharedPtrs\n";
        std::cout << "\n7.  ➤   Remove SharedPtr\n";
        std::cout << "\n8.  ➤   Create Multiple SharedPtrs\n";
        std::cout << "\n9.  ➤   Remove Created SharedPtrs\n";
        std::cout << "\n10. ➤   Back to Main Menu\n";
        std::cout << "\nEnter your choice: ";

        int choice;
        std::cin >> choice;
        clearInputBuffer();

        if (choice == 1) {
            std::cout << "\nEnter resource type (1 - int, 2 - string, 3 - vector<int>): ";
            std::cin >> type;
            clearInputBuffer();

            std::cout << "\nEnter resource name: ";
            std::cin >> name;
            clearInputBuffer();

            if (type == 1) {
                int value;
                std::cout << "\nEnter resource value: ";
                std::cin >> value;
                clearInputBuffer();
                sharedPtrsInt.push_back(SharedPtr<ResourceInt>(new ResourceInt(name, value)));
            } else if (type == 2) {
                std::string value;
                std::cout << "\nEnter resource value: ";
                std::cin >> value;
                clearInputBuffer();
                sharedPtrsString.push_back(SharedPtr<ResourceString>(new ResourceString(name, value)));
            } else if (type == 3) {
                std::vector<int> value;
                std::cout << "\nEnter resource value (comma-separated integers): ";
                std::string input;
                std::cin >> input;
                clearInputBuffer();
                std::stringstream ss(input);
                int val;
                while (ss >> val) {
                    value.push_back(val);
                    if (ss.peek() == ',') ss.ignore();
                }
                sharedPtrsVectorInt.push_back(SharedPtr<ResourceVectorInt>(new ResourceVectorInt(name, value)));
            } else {
                std::cout << "\nInvalid type\n";
            }
        } else if (choice == 2) {
            std::cout << "\nEnter resource type (1 - int, 2 - string, 3 - vector<int>): ";
            std::cin >> type;
            clearInputBuffer();

            if (type == 1 && !sharedPtrsInt.empty()) {
                std::cout << "\nEnter index of existing SharedPtr (0-" << sharedPtrsInt.size() - 1 << "): ";
                int index;
                std::cin >> index;
                clearInputBuffer();
                if (index >= 0 && index < sharedPtrsInt.size()) {
                    sharedPtrsInt.push_back(sharedPtrsInt[index]);
                    std::cout << "\nSharedPtr created to existing resource\n";
                } else {
                    std::cout << "\nInvalid index\n";
                }
            } else if (type == 2 && !sharedPtrsString.empty()) {
                std::cout << "\nEnter index of existing SharedPtr (0-" << sharedPtrsString.size() - 1 << "): ";
                int index;
                std::cin >> index;
                clearInputBuffer();
                if (index >= 0 && index < sharedPtrsString.size()) {
                    sharedPtrsString.push_back(sharedPtrsString[index]);
                    std::cout << "\nSharedPtr created to existing resource\n";
                } else {
                    std::cout << "\nInvalid index\n";
                }
            } else if (type == 3 && !sharedPtrsVectorInt.empty()) {
                std::cout << "\nEnter index of existing SharedPtr (0-" << sharedPtrsVectorInt.size() - 1 << "): ";
                int index;
                std::cin >> index;
                clearInputBuffer();
                if (index >= 0 && index < sharedPtrsVectorInt.size()) {
                    sharedPtrsVectorInt.push_back(sharedPtrsVectorInt[index]);
                    std::cout << "\nSharedPtr created to existing resource\n";
                } else {
                    std::cout << "\nInvalid index\n";
                }
            } else {
                std::cout << "\nNo existing SharedPtrs\n";
            }
        } else if (choice == 3) {
            std::cout << "\nEnter resource type (1 - int, 2 - string, 3 - vector<int>): ";
            std::cin >> type;
            clearInputBuffer();

            if (type == 1 && !sharedPtrsInt.empty()) {
                std::cout << "\nEnter index of SharedPtr (0-" << sharedPtrsInt.size() - 1 << "): ";
                int index;
                std::cin >> index;
                clearInputBuffer();
                if (index >= 0 && index < sharedPtrsInt.size()) {
                    if (sharedPtrsInt[index]) {
                        sharedPtrsInt[index]->print();
                    } else {
                        std::cout << "\nNo resource managed by SharedPtr\n";
                    }
                } else {
                    std::cout << "\nInvalid index\n";
                }
            } else if (type == 2 && !sharedPtrsString.empty()) {
                std::cout << "\nEnter index of SharedPtr (0-" << sharedPtrsString.size() - 1 << "): ";
                int index;
                std::cin >> index;
                clearInputBuffer();
                if (index >= 0 && index < sharedPtrsString.size()) {
                    if (sharedPtrsString[index]) {
                        sharedPtrsString[index]->print();
                    } else {
                        std::cout << "\nNo resource managed by SharedPtr\n";
                    }
                } else {
                    std::cout << "\nInvalid index\n";
                }
            } else if (type == 3 && !sharedPtrsVectorInt.empty()) {
                std::cout << "\nEnter index of SharedPtr (0-" << sharedPtrsVectorInt.size() - 1 << "): ";
                int index;
                std::cin >> index;
                clearInputBuffer();
                if (index >= 0 && index < sharedPtrsVectorInt.size()) {
                    if (sharedPtrsVectorInt[index]) {
                        sharedPtrsVectorInt[index]->print();
                    } else {
                        std::cout << "\nNo resource managed by SharedPtr\n";
                    }
                } else {
                    std::cout << "\nInvalid index\n";
                }
            } else {
                std::cout << "\nNo SharedPtrs\n";
            }
        } else if (choice == 4) {
            std::cout << "\nEnter resource type (1 - int, 2 - string, 3 - vector<int>): ";
            std::cin >> type;
            clearInputBuffer();

            if (type == 1 && !sharedPtrsInt.empty()) {
                std::cout << "\nEnter index of SharedPtr (0-" << sharedPtrsInt.size() - 1 << "): ";
                int index;
                std::cin >> index;
                clearInputBuffer();
                if (index >= 0 && index < sharedPtrsInt.size()) {
                    std::cout << "\nUse count: " << sharedPtrsInt[index].use_count() << std::endl;
                } else {
                    std::cout << "\nInvalid index\n";
                }
            } else if (type == 2 && !sharedPtrsString.empty()) {
                std::cout << "\nEnter index of SharedPtr (0-" << sharedPtrsString.size() - 1 << "): ";
                int index;
                std::cin >> index;
                clearInputBuffer();
                if (index >= 0 && index < sharedPtrsString.size()) {
                    std::cout << "\nUse count: " << sharedPtrsString[index].use_count() << std::endl;
                } else {
                    std::cout << "\nInvalid index\n";
                }
            } else if (type == 3 && !sharedPtrsVectorInt.empty()) {
                std::cout << "\nEnter index of SharedPtr (0-" << sharedPtrsVectorInt.size() - 1 << "): ";
                int index;
                std::cin >> index;
                clearInputBuffer();
                if (index >= 0 && index < sharedPtrsVectorInt.size()) {
                    std::cout << "\nUse count: " << sharedPtrsVectorInt[index].use_count() << std::endl;
                } else {
                    std::cout << "\nInvalid index\n";
                }
            } else {
                std::cout << "\nNo SharedPtrs\n";
            }
        } else if (choice == 5) {
            std::cout << "\nEnter resource type (1 - int, 2 - string, 3 - vector<int>): ";
            std::cin >> type;
            clearInputBuffer();

            if (type == 1 && !sharedPtrsInt.empty()) {
                std::cout << "\nEnter index of SharedPtr to reset (0-" << sharedPtrsInt.size() - 1 << "): ";
                int index;
                std::cin >> index;
                clearInputBuffer();
                if (index >= 0 && index < sharedPtrsInt.size()) {
                    sharedPtrsInt[index].reset();
                    std::cout << "\nSharedPtr reset\n";
                } else {
                    std::cout << "\nInvalid index\n";
                }
            } else if (type == 2 && !sharedPtrsString.empty()) {
                std::cout << "\nEnter index of SharedPtr to reset (0-" << sharedPtrsString.size() - 1 << "): ";
                int index;
                std::cin >> index;
                clearInputBuffer();
                if (index >= 0 && index < sharedPtrsString.size()) {
                    sharedPtrsString[index].reset();
                    std::cout << "\nSharedPtr reset\n";
                } else {
                    std::cout << "\nInvalid index\n";
                }
            } else if (type == 3 && !sharedPtrsVectorInt.empty()) {
                std::cout << "\nEnter index of SharedPtr to reset (0-" << sharedPtrsVectorInt.size() - 1 << "): ";
                int index;
                std::cin >> index;
                clearInputBuffer();
                if (index >= 0 && index < sharedPtrsVectorInt.size()) {
                    sharedPtrsVectorInt[index].reset();
                    std::cout << "\nSharedPtr reset\n";
                } else {
                    std::cout << "\nInvalid index\n";
                }
            } else {
                std::cout << "\nNo SharedPtrs\n";
            }
        } else if (choice == 6) {
            std::cout << "\nSharedPtrs (int):\n";
            if (!sharedPtrsInt.empty()) {
                for (size_t i = 0; i < sharedPtrsInt.size(); ++i) {
                    std::cout << "\nSharedPtr " << i << ": ";
                    if (sharedPtrsInt[i]) {
                        sharedPtrsInt[i]->print();
                    } else {
                        std::cout << "\nNo resource managed by SharedPtr\n";
                    }
                }
            } else {
                std::cout << "\nNo SharedPtrs\n";
            }

            std::cout << "\nSharedPtrs (string):\n";
            if (!sharedPtrsString.empty()) {
                for (size_t i = 0; i < sharedPtrsString.size(); ++i) {
                    std::cout << "\nSharedPtr " << i << ": ";
                    if (sharedPtrsString[i]) {
                        sharedPtrsString[i]->print();
                    } else {
                        std::cout << "\nNo resource managed by SharedPtr\n";
                    }
                }
            } else {
                std::cout << "\nNo SharedPtrs\n";
            }

            std::cout << "\nSharedPtrs (vector<int>):\n";
            if (!sharedPtrsVectorInt.empty()) {
                for (size_t i = 0; i < sharedPtrsVectorInt.size(); ++i) {
                    std::cout << "\nSharedPtr " << i << ": ";
                    if (sharedPtrsVectorInt[i]) {
                        sharedPtrsVectorInt[i]->print();
                    } else {
                        std::cout << "\nNo resource managed by SharedPtr\n";
                    }
                }
            } else {
                std::cout << "\nNo SharedPtrs\n";
            }
        } else if (choice == 7) {
            std::cout << "\nEnter resource type (1 - int, 2 - string, 3 - vector<int>): ";
            std::cin >> type;
            clearInputBuffer();

            if (type == 1 && !sharedPtrsInt.empty()) {
                std::cout << "\nEnter index of SharedPtr to remove (0-" << sharedPtrsInt.size() - 1 << "): ";
                int index;
                std::cin >> index;
                clearInputBuffer();
                if (index >= 0 && index < sharedPtrsInt.size()) {
                    sharedPtrsInt.erase(sharedPtrsInt.begin() + index);
                    std::cout << "\nSharedPtr removed\n";
                } else {
                    std::cout << "\nInvalid index\n";
                }
            } else if (type == 2 && !sharedPtrsString.empty()) {
                std::cout << "\nEnter index of SharedPtr to remove (0-" << sharedPtrsString.size() - 1 << "): ";
                int index;
                std::cin >> index;
                clearInputBuffer();
                if (index >= 0 && index < sharedPtrsString.size()) {
                    sharedPtrsString.erase(sharedPtrsString.begin() + index);
                    std::cout << "\nSharedPtr removed\n";
                } else {
                    std::cout << "\nInvalid index\n";
                }
            } else if (type == 3 && !sharedPtrsVectorInt.empty()) {
                std::cout << "\nEnter index of SharedPtr to remove (0-" << sharedPtrsVectorInt.size() - 1 << "): ";
                int index;
                std::cin >> index;
                clearInputBuffer();
                if (index >= 0 && index < sharedPtrsVectorInt.size()) {
                    sharedPtrsVectorInt.erase(sharedPtrsVectorInt.begin() + index);
                    std::cout << "\nSharedPtr removed\n";
                } else {
                    std::cout << "\nInvalid index\n";
                }
            } else {
                std::cout << "\nNo SharedPtrs\n";
            }
        } else if (choice == 8) {
            std::cout << "\nEnter resource type (1 - int, 2 - string, 3 - vector<int>): ";
            std::cin >> type;
            clearInputBuffer();

            std::cout << "\nEnter number of SharedPtrs to create: ";
            std::cin >> count;
            clearInputBuffer();

            if (type == 1) {
                int value;
                std::cout << "\nEnter resource value: ";
                std::cin >> value;
                clearInputBuffer();

                auto start = std::chrono::high_resolution_clock::now();
                for (int i = 0; i < count; ++i) {
                    sharedPtrsInt.push_back(SharedPtr<ResourceInt>(new ResourceInt("MultiShared", value)));
                }
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsed = end - start;
                std::cout << "\nTime to create " << count << " SharedPtrs: " << elapsed.count() << " s\n";

                std::vector<std::shared_ptr<ResourceInt>> stlSharedPtrs;
                start = std::chrono::high_resolution_clock::now();
                for (int i = 0; i < count; ++i) {
                    stlSharedPtrs.push_back(std::make_shared<ResourceInt>("MultiSTLShared", value));
                }
                end = std::chrono::high_resolution_clock::now();
                elapsed = end - start;
                std::cout << "\nTime to create " << count << " std::shared_ptrs: " << elapsed.count() << " s\n";
            } else if (type == 2) {
                std::string value;
                std::cout << "\nEnter resource value: ";
                std::cin >> value;
                clearInputBuffer();

                auto start = std::chrono::high_resolution_clock::now();
                for (int i = 0; i < count; ++i) {
                    sharedPtrsString.push_back(SharedPtr<ResourceString>(new ResourceString("MultiShared", value)));
                }
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsed = end - start;
                std::cout << "\nTime to create " << count << " SharedPtrs: " << elapsed.count() << " s\n";

                std::vector<std::shared_ptr<ResourceString>> stlSharedPtrs;
                start = std::chrono::high_resolution_clock::now();
                for (int i = 0; i < count; ++i) {
                    stlSharedPtrs.push_back(std::make_shared<ResourceString>("MultiSTLShared", value));
                }
                end = std::chrono::high_resolution_clock::now();
                elapsed = end - start;
                std::cout << "\nTime to create " << count << " std::shared_ptrs: " << elapsed.count() << " s\n";
            } else if (type == 3) {
                std::vector<int> value;
                std::cout << "\nEnter resource value (comma-separated integers): ";
                std::string input;
                std::cin >> input;
                clearInputBuffer();
                std::stringstream ss(input);
                int val;
                while (ss >> val) {
                    value.push_back(val);
                    if (ss.peek() == ',') ss.ignore();
                }

                auto start = std::chrono::high_resolution_clock::now();
                for (int i = 0; i < count; ++i) {
                    sharedPtrsVectorInt.push_back(SharedPtr<ResourceVectorInt>(new ResourceVectorInt("MultiShared", value)));
                }
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsed = end - start;
                std::cout << "\nTime to create " << count << " SharedPtrs: " << elapsed.count() << " s\n";

                std::vector<std::shared_ptr<ResourceVectorInt>> stlSharedPtrs;
                start = std::chrono::high_resolution_clock::now();
                for (int i = 0; i < count; ++i) {
                    stlSharedPtrs.push_back(std::make_shared<ResourceVectorInt>("MultiSTLShared", value));
                }
                end = std::chrono::high_resolution_clock::now();
                elapsed = end - start;
                std::cout << "\nTime to create " << count << " std::shared_ptrs: " << elapsed.count() << " s\n";
            } else {
                std::cout << "\nInvalid type\n";
            }
        } else if (choice == 9) {
            sharedPtrsInt.resize(originalSizeInt);
            sharedPtrsString.resize(originalSizeString);
            sharedPtrsVectorInt.resize(originalSizeVectorInt);
            std::cout << "\nCreated SharedPtrs removed\n";
        } else if (choice == 10) {
            break;
        } else {
            std::cout << "\nInvalid choice\n";
        }
    }
}

void weakPtrMenu() {
    SharedPtr<ResourceInt> sharedPtrInt;
    SharedPtr<ResourceString> sharedPtrString;
    SharedPtr<ResourceVectorInt> sharedPtrVectorInt;
    WeakPtr<ResourceInt> weakPtrInt;
    WeakPtr<ResourceString> weakPtrString;
    WeakPtr<ResourceVectorInt> weakPtrVectorInt;
    std::string name;
    int type;
    int count;

    while (true) {
        std::cout << "\nWeakPtr Menu:\n";
        std::cout << "\n1.  ➤   Create SharedPtr\n";
        std::cout << "\n2.  ➤   Create WeakPtr from SharedPtr\n";
        std::cout << "\n3.  ➤   Lock WeakPtr\n";
        std::cout << "\n4.  ➤   Use Count\n";
        std::cout << "\n5.  ➤   Expired\n";
        std::cout << "\n6.  ➤   Create Multiple WeakPtrs\n";
        std::cout << "\n7.  ➤   Back to Main Menu\n";
        std::cout << "\nEnter your choice: ";

        int choice;
        std::cin >> choice;
        clearInputBuffer();

        if (choice == 1) {
            std::cout << "\nEnter resource type (1 - int, 2 - string, 3 - vector<int>): ";
            std::cin >> type;
            clearInputBuffer();

            std::cout << "\nEnter resource name: ";
            std::cin >> name;
            clearInputBuffer();

            if (type == 1) {
                int value;
                std::cout << "\nEnter resource value: ";
                std::cin >> value;
                clearInputBuffer();
                sharedPtrInt.reset(new ResourceInt(name, value));
            } else if (type == 2) {
                std::string value;
                std::cout << "\nEnter resource value: ";
                std::cin >> value;
                clearInputBuffer();
                sharedPtrString.reset(new ResourceString(name, value));
            } else if (type == 3) {
                std::vector<int> value;
                std::cout << "\nEnter resource value (comma-separated integers): ";
                std::string input;
                std::cin >> input;
                clearInputBuffer();
                std::stringstream ss(input);
                int val;
                while (ss >> val) {
                    value.push_back(val);
                    if (ss.peek() == ',') ss.ignore();
                }
                sharedPtrVectorInt.reset(new ResourceVectorInt(name, value));
            } else {
                std::cout << "\nInvalid type\n";
            }
        } else if (choice == 2) {
            std::cout << "\nEnter resource type (1 - int, 2 - string, 3 - vector<int>): ";
            std::cin >> type;
            clearInputBuffer();

            if (type == 1 && sharedPtrInt) {
                weakPtrInt = sharedPtrInt;
                std::cout << "\nWeakPtr created from SharedPtr\n";
            } else if (type == 2 && sharedPtrString) {
                weakPtrString = sharedPtrString;
                std::cout << "\nWeakPtr created from SharedPtr\n";
            } else if (type == 3 && sharedPtrVectorInt) {
                weakPtrVectorInt = sharedPtrVectorInt;
                std::cout << "\nWeakPtr created from SharedPtr\n";
            } else {
                std::cout << "\nNo resource managed by SharedPtr\n";
            }
        } else if (choice == 3) {
            std::cout << "\nEnter resource type (1 - int, 2 - string, 3 - vector<int>): ";
            std::cin >> type;
            clearInputBuffer();

            if (type == 1) {
                SharedPtr<ResourceInt> lockedPtr = weakPtrInt.lock();
                if (lockedPtr) {
                    lockedPtr->print();
                } else {
                    std::cout << "\nWeakPtr expired\n";
                }
            } else if (type == 2) {
                SharedPtr<ResourceString> lockedPtr = weakPtrString.lock();
                if (lockedPtr) {
                    lockedPtr->print();
                } else {
                    std::cout << "\nWeakPtr expired\n";
                }
            } else if (type == 3) {
                SharedPtr<ResourceVectorInt> lockedPtr = weakPtrVectorInt.lock();
                if (lockedPtr) {
                    lockedPtr->print();
                } else {
                    std::cout << "\nWeakPtr expired\n";
                }
            } else {
                std::cout << "\nInvalid type\n";
            }
        } else if (choice == 4) {
            std::cout << "\nEnter resource type (1 - int, 2 - string, 3 - vector<int>): ";
            std::cin >> type;
            clearInputBuffer();

            if (type == 1) {
                std::cout << "\nUse count: " << weakPtrInt.use_count() << std::endl;
            } else if (type == 2) {
                std::cout << "\nUse count: " << weakPtrString.use_count() << std::endl;
            } else if (type == 3) {
                std::cout << "\nUse count: " << weakPtrVectorInt.use_count() << std::endl;
            } else {
                std::cout << "\nInvalid type\n";
            }
        } else if (choice == 5) {
            std::cout << "\nEnter resource type (1 - int, 2 - string, 3 - vector<int>): ";
            std::cin >> type;
            clearInputBuffer();

            if (type == 1) {
                std::cout << "\nExpired: " << (weakPtrInt.expired() ? "Yes" : "No") << std::endl;
            } else if (type == 2) {
                std::cout << "\nExpired: " << (weakPtrString.expired() ? "Yes" : "No") << std::endl;
            } else if (type == 3) {
                std::cout << "\nExpired: " << (weakPtrVectorInt.expired() ? "Yes" : "No") << std::endl;
            } else {
                std::cout << "\nInvalid type\n";
            }
        } else if (choice == 6) {
            std::cout << "\nEnter resource type (1 - int, 2 - string, 3 - vector<int>): ";
            std::cin >> type;
            clearInputBuffer();

            std::cout << "\nEnter number of WeakPtrs to create: ";
            std::cin >> count;
            clearInputBuffer();

            if (type == 1) {
                auto start = std::chrono::high_resolution_clock::now();
                for (int i = 0; i < count; ++i) {
                    weakPtrInt = sharedPtrInt;
                }
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsed = end - start;
                std::cout << "\nTime to create " << count << " WeakPtrs: " << elapsed.count() << " s\n";

                std::weak_ptr<ResourceInt> stlWeakPtr;
                start = std::chrono::high_resolution_clock::now();
                for (int i = 0; i < count; ++i) {
                    stlWeakPtr = std::make_shared<ResourceInt>("MultiSTLShared", 0);
                }
                end = std::chrono::high_resolution_clock::now();
                elapsed = end - start;
                std::cout << "\nTime to create " << count << " std::weak_ptrs: " << elapsed.count() << " s\n";
            } else if (type == 2) {
                auto start = std::chrono::high_resolution_clock::now();
                for (int i = 0; i < count; ++i) {
                    weakPtrString = sharedPtrString;
                }
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsed = end - start;
                std::cout << "\nTime to create " << count << " WeakPtrs: " << elapsed.count() << " s\n";

                std::weak_ptr<ResourceString> stlWeakPtr;
                start = std::chrono::high_resolution_clock::now();
                for (int i = 0; i < count; ++i) {
                    stlWeakPtr = std::make_shared<ResourceString>("MultiSTLShared", "");
                }
                end = std::chrono::high_resolution_clock::now();
                elapsed = end - start;
                std::cout << "\nTime to create " << count << " std::weak_ptrs: " << elapsed.count() << " s\n";
            } else if (type == 3) {
                auto start = std::chrono::high_resolution_clock::now();
                for (int i = 0; i < count; ++i) {
                    weakPtrVectorInt = sharedPtrVectorInt;
                }
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsed = end - start;
                std::cout << "\nTime to create " << count << " WeakPtrs: " << elapsed.count() << " s\n";

                std::weak_ptr<ResourceVectorInt> stlWeakPtr;
                start = std::chrono::high_resolution_clock::now();
                for (int i = 0; i < count; ++i) {
                    stlWeakPtr = std::make_shared<ResourceVectorInt>("MultiSTLShared", std::vector<int>());
                }
                end = std::chrono::high_resolution_clock::now();
                elapsed = end - start;
                std::cout << "\nTime to create " << count << " std::weak_ptrs: " << elapsed.count() << " s\n";
            } else {
                std::cout << "\nInvalid type\n";
            }
        } else if (choice == 7) {
            break;
        } else {
            std::cout << "\nInvalid choice\n";
        }
    }
}

void uniquePtrMenu() {
    UniquePtr<ResourceInt> uniquePtrInt;
    UniquePtr<ResourceString> uniquePtrString;
    UniquePtr<ResourceVectorInt> uniquePtrVectorInt;
    std::string name;
    int type;
    int count;

    while (true) {
        std::cout << "\nUniquePtr Menu:\n";
        std::cout << "\n1.  ➤   Create UniquePtr\n";
        std::cout << "\n2.  ➤   Get Resource\n";
        std::cout << "\n3.  ➤   Release\n";
        std::cout << "\n4.  ➤   Reset\n";
        std::cout << "\n5.  ➤   Create Multiple UniquePtrs\n";
        std::cout << "\n6.  ➤   Back to Main Menu\n";
        std::cout << "\nEnter your choice: ";

        int choice;
        std::cin >> choice;
        clearInputBuffer();

        if (choice == 1) {
            std::cout << "\nEnter resource type (1 - int, 2 - string, 3 - vector<int>): ";
            std::cin >> type;
            clearInputBuffer();

            std::cout << "\nEnter resource name: ";
            std::cin >> name;
            clearInputBuffer();

            if (type == 1) {
                int value;
                std::cout << "\nEnter resource value: ";
                std::cin >> value;
                clearInputBuffer();
                uniquePtrInt.reset(new ResourceInt(name, value));
            } else if (type == 2) {
                std::string value;
                std::cout << "\nEnter resource value: ";
                std::cin >> value;
                clearInputBuffer();
                uniquePtrString.reset(new ResourceString(name, value));
            } else if (type == 3) {
                std::vector<int> value;
                std::cout << "\nEnter resource value (comma-separated integers): ";
                std::string input;
                std::cin >> input;
                clearInputBuffer();
                std::stringstream ss(input);
                int val;
                while (ss >> val) {
                    value.push_back(val);
                    if (ss.peek() == ',') ss.ignore();
                }
                uniquePtrVectorInt.reset(new ResourceVectorInt(name, value));
            } else {
                std::cout << "\nInvalid type\n";
            }
        } else if (choice == 2) {
            std::cout << "\nEnter resource type (1 - int, 2 - string, 3 - vector<int>): ";
            std::cin >> type;
            clearInputBuffer();

            if (type == 1 && uniquePtrInt.get()) {
                uniquePtrInt->print();
            } else if (type == 2 && uniquePtrString.get()) {
                uniquePtrString->print();
            } else if (type == 3 && uniquePtrVectorInt.get()) {
                uniquePtrVectorInt->print();
            } else {
                std::cout << "\nNo resource managed by UniquePtr\n";
            }
        } else if (choice == 3) {
            std::cout << "\nEnter resource type (1 - int, 2 - string, 3 - vector<int>): ";
            std::cin >> type;
            clearInputBuffer();

            if (type == 1) {
                ResourceInt* ptr = uniquePtrInt.release();
                if (ptr) {
                    std::cout << "\nResource released\n";
                } else {
                    std::cout << "\nNo resource managed by UniquePtr\n";
                }
            } else if (type == 2) {
                ResourceString* ptr = uniquePtrString.release();
                if (ptr) {
                    std::cout << "\nResource released\n";
                } else {
                    std::cout << "\nNo resource managed by UniquePtr\n";
                }
            } else if (type == 3) {
                ResourceVectorInt* ptr = uniquePtrVectorInt.release();
                if (ptr) {
                    std::cout << "\nResource released\n";
                } else {
                    std::cout << "\nNo resource managed by UniquePtr\n";
                }
            } else {
                std::cout << "\nInvalid type\n";
            }
        } else if (choice == 4) {
            std::cout << "\nEnter resource type (1 - int, 2 - string, 3 - vector<int>): ";
            std::cin >> type;
            clearInputBuffer();

            if (type == 1) {
                uniquePtrInt.reset();
                std::cout << "\nUniquePtr reset\n";
            } else if (type == 2) {
                uniquePtrString.reset();
                std::cout << "\nUniquePtr reset\n";
            } else if (type == 3) {
                uniquePtrVectorInt.reset();
                std::cout << "\nUniquePtr reset\n";
            } else {
                std::cout << "\nInvalid type\n";
            }
        } else if (choice == 5) {
            std::cout << "\nEnter resource type (1 - int, 2 - string, 3 - vector<int>): ";
            std::cin >> type;
            clearInputBuffer();

            std::cout << "\nEnter number of UniquePtrs to create: ";
            std::cin >> count;
            clearInputBuffer();

            if (type == 1) {
                int value;
                std::cout << "\nEnter resource value: ";
                std::cin >> value;
                clearInputBuffer();

                auto start = std::chrono::high_resolution_clock::now();
                for (int i = 0; i < count; ++i) {
                    uniquePtrInt.reset(new ResourceInt("MultiUnique", value));
                }
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsed = end - start;
                std::cout << "\nTime to create " << count << " UniquePtrs: " << elapsed.count() << " s\n";

                std::vector<std::unique_ptr<ResourceInt>> stlUniquePtrs;
                start = std::chrono::high_resolution_clock::now();
                for (int i = 0; i < count; ++i) {
                    stlUniquePtrs.push_back(std::make_unique<ResourceInt>("MultiSTLUnique", value));
                }
                end = std::chrono::high_resolution_clock::now();
                elapsed = end - start;
                std::cout << "\nTime to create " << count << " std::unique_ptrs: " << elapsed.count() << " s\n";
            } else if (type == 2) {
                std::string value;
                std::cout << "\nEnter resource value: ";
                std::cin >> value;
                clearInputBuffer();

                auto start = std::chrono::high_resolution_clock::now();
                for (int i = 0; i < count; ++i) {
                    uniquePtrString.reset(new ResourceString("MultiUnique", value));
                }
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsed = end - start;
                std::cout << "\nTime to create " << count << " UniquePtrs: " << elapsed.count() << " s\n";

                std::vector<std::unique_ptr<ResourceString>> stlUniquePtrs;
                start = std::chrono::high_resolution_clock::now();
                for (int i = 0; i < count; ++i) {
                    stlUniquePtrs.push_back(std::make_unique<ResourceString>("MultiSTLUnique", value));
                }
                end = std::chrono::high_resolution_clock::now();
                elapsed = end - start;
                std::cout << "\nTime to create " << count << " std::unique_ptrs: " << elapsed.count() << " s\n";
            } else if (type == 3) {
                std::vector<int> value;
                std::cout << "\nEnter resource value (comma-separated integers): ";
                std::string input;
                std::cin >> input;
                clearInputBuffer();
                std::stringstream ss(input);
                int val;
                while (ss >> val) {
                    value.push_back(val);
                    if (ss.peek() == ',') ss.ignore();
                }

                auto start = std::chrono::high_resolution_clock::now();
                for (int i = 0; i < count; ++i) {
                    uniquePtrVectorInt.reset(new ResourceVectorInt("MultiUnique", value));
                }
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsed = end - start;
                std::cout << "\nTime to create " << count << " UniquePtrs: " << elapsed.count() << " s\n";

                std::vector<std::unique_ptr<ResourceVectorInt>> stlUniquePtrs;
                start = std::chrono::high_resolution_clock::now();
                for (int i = 0; i < count; ++i) {
                    stlUniquePtrs.push_back(std::make_unique<ResourceVectorInt>("MultiSTLUnique", value));
                }
                end = std::chrono::high_resolution_clock::now();
                elapsed = end - start;
                std::cout << "\nTime to create " << count << " std::unique_ptrs: " << elapsed.count() << " s\n";
            } else {
                std::cout << "\nInvalid type\n";
            }
        } else if (choice == 6) {
            break;
        } else {
            std::cout << "\nInvalid choice\n";
        }
    }
}

int main() {
    while (true) {
        std::cout << "\nMain Menu:\n";
        std::cout << "\n1.  ➤   SharedPtr Menu\n";
        std::cout << "\n2.  ➤   WeakPtr Menu\n";
        std::cout << "\n3.  ➤   UniquePtr Menu\n";
        std::cout << "\n4.  ➤   Exit\n";
        std::cout << "\nEnter your choice: ";

        int choice;
        std::cin >> choice;
        clearInputBuffer();

        if (choice == 1) {
            sharedPtrMenu();
        } else if (choice == 2) {
            weakPtrMenu();
        } else if (choice == 3) {
            uniquePtrMenu();
        } else if (choice == 4) {
            break;
        } else {
            std::cout << "\nInvalid choice\n";
        }
    }

    return 0;
}
