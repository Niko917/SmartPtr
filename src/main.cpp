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
        std::cout << "Resource " << name_ << " created with value " << value_ << std::endl;
    }

    ~ResourceInt() {
        std::cout << "Resource " << name_ << " destroyed" << std::endl;
    }

    void print() const {
        std::cout << "Resource " << name_ << " has value " << value_ << std::endl;
    }

private:
    std::string name_;
    int value_;
};

class ResourceString {
public:
    ResourceString(const std::string& name, const std::string& value) : name_(name), value_(value) {
        std::cout << "Resource " << name_ << " created with value " << value_ << std::endl;
    }

    ~ResourceString() {
        std::cout << "Resource " << name_ << " destroyed" << std::endl;
    }

    void print() const {
        std::cout << "Resource " << name_ << " has value " << value_ << std::endl;
    }

private:
    std::string name_;
    std::string value_;
};

class ResourceVectorInt {
public:
    ResourceVectorInt(const std::string& name, const std::vector<int>& value) : name_(name), value_(value) {
        std::cout << "Resource " << name_ << " created with value ";
        for (int v : value_) std::cout << v << " ";
        std::cout << std::endl;
    }

    ~ResourceVectorInt() {
        std::cout << "Resource " << name_ << " destroyed" << std::endl;
    }

    void print() const {
        std::cout << "Resource " << name_ << " has value ";
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
        std::cout << "1. Create SharedPtr\n";
        std::cout << "2. Create SharedPtr to Existing Resource\n";
        std::cout << "3. Get Resource\n";
        std::cout << "4. Use Count\n";
        std::cout << "5. Reset\n";
        std::cout << "6. List All SharedPtrs\n";
        std::cout << "7. Remove SharedPtr\n";
        std::cout << "8. Create Multiple SharedPtrs\n";
        std::cout << "9. Remove Created SharedPtrs\n";
        std::cout << "10. Back to Main Menu\n";
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;
        clearInputBuffer();

        if (choice == 1) {
            std::cout << "Enter resource type (1 - int, 2 - string, 3 - vector<int>): ";
            std::cin >> type;
            clearInputBuffer();

            std::cout << "Enter resource name: ";
            std::cin >> name;
            clearInputBuffer();

            if (type == 1) {
                int value;
                std::cout << "Enter resource value: ";
                std::cin >> value;
                clearInputBuffer();
                sharedPtrsInt.push_back(SharedPtr<ResourceInt>(new ResourceInt(name, value)));
            } else if (type == 2) {
                std::string value;
                std::cout << "Enter resource value: ";
                std::cin >> value;
                clearInputBuffer();
                sharedPtrsString.push_back(SharedPtr<ResourceString>(new ResourceString(name, value)));
            } else if (type == 3) {
                std::vector<int> value;
                std::cout << "Enter resource value (comma-separated integers): ";
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
                std::cout << "Invalid type\n";
            }
        } else if (choice == 2) {
            std::cout << "Enter resource type (1 - int, 2 - string, 3 - vector<int>): ";
            std::cin >> type;
            clearInputBuffer();

            if (type == 1 && !sharedPtrsInt.empty()) {
                std::cout << "Enter index of existing SharedPtr (0-" << sharedPtrsInt.size() - 1 << "): ";
                int index;
                std::cin >> index;
                clearInputBuffer();
                if (index >= 0 && index < sharedPtrsInt.size()) {
                    sharedPtrsInt.push_back(sharedPtrsInt[index]);
                    std::cout << "SharedPtr created to existing resource\n";
                } else {
                    std::cout << "Invalid index\n";
                }
            } else if (type == 2 && !sharedPtrsString.empty()) {
                std::cout << "Enter index of existing SharedPtr (0-" << sharedPtrsString.size() - 1 << "): ";
                int index;
                std::cin >> index;
                clearInputBuffer();
                if (index >= 0 && index < sharedPtrsString.size()) {
                    sharedPtrsString.push_back(sharedPtrsString[index]);
                    std::cout << "SharedPtr created to existing resource\n";
                } else {
                    std::cout << "Invalid index\n";
                }
            } else if (type == 3 && !sharedPtrsVectorInt.empty()) {
                std::cout << "Enter index of existing SharedPtr (0-" << sharedPtrsVectorInt.size() - 1 << "): ";
                int index;
                std::cin >> index;
                clearInputBuffer();
                if (index >= 0 && index < sharedPtrsVectorInt.size()) {
                    sharedPtrsVectorInt.push_back(sharedPtrsVectorInt[index]);
                    std::cout << "SharedPtr created to existing resource\n";
                } else {
                    std::cout << "Invalid index\n";
                }
            } else {
                std::cout << "No existing SharedPtrs\n";
            }
        } else if (choice == 3) {
            std::cout << "Enter resource type (1 - int, 2 - string, 3 - vector<int>): ";
            std::cin >> type;
            clearInputBuffer();

            if (type == 1 && !sharedPtrsInt.empty()) {
                std::cout << "Enter index of SharedPtr (0-" << sharedPtrsInt.size() - 1 << "): ";
                int index;
                std::cin >> index;
                clearInputBuffer();
                if (index >= 0 && index < sharedPtrsInt.size()) {
                    if (sharedPtrsInt[index]) {
                        sharedPtrsInt[index]->print();
                    } else {
                        std::cout << "No resource managed by SharedPtr\n";
                    }
                } else {
                    std::cout << "Invalid index\n";
                }
            } else if (type == 2 && !sharedPtrsString.empty()) {
                std::cout << "Enter index of SharedPtr (0-" << sharedPtrsString.size() - 1 << "): ";
                int index;
                std::cin >> index;
                clearInputBuffer();
                if (index >= 0 && index < sharedPtrsString.size()) {
                    if (sharedPtrsString[index]) {
                        sharedPtrsString[index]->print();
                    } else {
                        std::cout << "No resource managed by SharedPtr\n";
                    }
                } else {
                    std::cout << "Invalid index\n";
                }
            } else if (type == 3 && !sharedPtrsVectorInt.empty()) {
                std::cout << "Enter index of SharedPtr (0-" << sharedPtrsVectorInt.size() - 1 << "): ";
                int index;
                std::cin >> index;
                clearInputBuffer();
                if (index >= 0 && index < sharedPtrsVectorInt.size()) {
                    if (sharedPtrsVectorInt[index]) {
                        sharedPtrsVectorInt[index]->print();
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
            std::cout << "Enter resource type (1 - int, 2 - string, 3 - vector<int>): ";
            std::cin >> type;
            clearInputBuffer();

            if (type == 1 && !sharedPtrsInt.empty()) {
                std::cout << "Enter index of SharedPtr (0-" << sharedPtrsInt.size() - 1 << "): ";
                int index;
                std::cin >> index;
                clearInputBuffer();
                if (index >= 0 && index < sharedPtrsInt.size()) {
                    std::cout << "Use count: " << sharedPtrsInt[index].use_count() << std::endl;
                } else {
                    std::cout << "Invalid index\n";
                }
            } else if (type == 2 && !sharedPtrsString.empty()) {
                std::cout << "Enter index of SharedPtr (0-" << sharedPtrsString.size() - 1 << "): ";
                int index;
                std::cin >> index;
                clearInputBuffer();
                if (index >= 0 && index < sharedPtrsString.size()) {
                    std::cout << "Use count: " << sharedPtrsString[index].use_count() << std::endl;
                } else {
                    std::cout << "Invalid index\n";
                }
            } else if (type == 3 && !sharedPtrsVectorInt.empty()) {
                std::cout << "Enter index of SharedPtr (0-" << sharedPtrsVectorInt.size() - 1 << "): ";
                int index;
                std::cin >> index;
                clearInputBuffer();
                if (index >= 0 && index < sharedPtrsVectorInt.size()) {
                    std::cout << "Use count: " << sharedPtrsVectorInt[index].use_count() << std::endl;
                } else {
                    std::cout << "Invalid index\n";
                }
            } else {
                std::cout << "No SharedPtrs\n";
            }
        } else if (choice == 5) {
            std::cout << "Enter resource type (1 - int, 2 - string, 3 - vector<int>): ";
            std::cin >> type;
            clearInputBuffer();

            if (type == 1 && !sharedPtrsInt.empty()) {
                std::cout << "Enter index of SharedPtr to reset (0-" << sharedPtrsInt.size() - 1 << "): ";
                int index;
                std::cin >> index;
                clearInputBuffer();
                if (index >= 0 && index < sharedPtrsInt.size()) {
                    sharedPtrsInt[index].reset();
                    std::cout << "SharedPtr reset\n";
                } else {
                    std::cout << "Invalid index\n";
                }
            } else if (type == 2 && !sharedPtrsString.empty()) {
                std::cout << "Enter index of SharedPtr to reset (0-" << sharedPtrsString.size() - 1 << "): ";
                int index;
                std::cin >> index;
                clearInputBuffer();
                if (index >= 0 && index < sharedPtrsString.size()) {
                    sharedPtrsString[index].reset();
                    std::cout << "SharedPtr reset\n";
                } else {
                    std::cout << "Invalid index\n";
                }
            } else if (type == 3 && !sharedPtrsVectorInt.empty()) {
                std::cout << "Enter index of SharedPtr to reset (0-" << sharedPtrsVectorInt.size() - 1 << "): ";
                int index;
                std::cin >> index;
                clearInputBuffer();
                if (index >= 0 && index < sharedPtrsVectorInt.size()) {
                    sharedPtrsVectorInt[index].reset();
                    std::cout << "SharedPtr reset\n";
                } else {
                    std::cout << "Invalid index\n";
                }
            } else {
                std::cout << "No SharedPtrs\n";
            }
        } else if (choice == 6) {
            std::cout << "SharedPtrs (int):\n";
            if (!sharedPtrsInt.empty()) {
                for (size_t i = 0; i < sharedPtrsInt.size(); ++i) {
                    std::cout << "SharedPtr " << i << ": ";
                    if (sharedPtrsInt[i]) {
                        sharedPtrsInt[i]->print();
                    } else {
                        std::cout << "No resource managed by SharedPtr\n";
                    }
                }
            } else {
                std::cout << "No SharedPtrs\n";
            }

            std::cout << "SharedPtrs (string):\n";
            if (!sharedPtrsString.empty()) {
                for (size_t i = 0; i < sharedPtrsString.size(); ++i) {
                    std::cout << "SharedPtr " << i << ": ";
                    if (sharedPtrsString[i]) {
                        sharedPtrsString[i]->print();
                    } else {
                        std::cout << "No resource managed by SharedPtr\n";
                    }
                }
            } else {
                std::cout << "No SharedPtrs\n";
            }

            std::cout << "SharedPtrs (vector<int>):\n";
            if (!sharedPtrsVectorInt.empty()) {
                for (size_t i = 0; i < sharedPtrsVectorInt.size(); ++i) {
                    std::cout << "SharedPtr " << i << ": ";
                    if (sharedPtrsVectorInt[i]) {
                        sharedPtrsVectorInt[i]->print();
                    } else {
                        std::cout << "No resource managed by SharedPtr\n";
                    }
                }
            } else {
                std::cout << "No SharedPtrs\n";
            }
        } else if (choice == 7) {
            std::cout << "Enter resource type (1 - int, 2 - string, 3 - vector<int>): ";
            std::cin >> type;
            clearInputBuffer();

            if (type == 1 && !sharedPtrsInt.empty()) {
                std::cout << "Enter index of SharedPtr to remove (0-" << sharedPtrsInt.size() - 1 << "): ";
                int index;
                std::cin >> index;
                clearInputBuffer();
                if (index >= 0 && index < sharedPtrsInt.size()) {
                    sharedPtrsInt.erase(sharedPtrsInt.begin() + index);
                    std::cout << "SharedPtr removed\n";
                } else {
                    std::cout << "Invalid index\n";
                }
            } else if (type == 2 && !sharedPtrsString.empty()) {
                std::cout << "Enter index of SharedPtr to remove (0-" << sharedPtrsString.size() - 1 << "): ";
                int index;
                std::cin >> index;
                clearInputBuffer();
                if (index >= 0 && index < sharedPtrsString.size()) {
                    sharedPtrsString.erase(sharedPtrsString.begin() + index);
                    std::cout << "SharedPtr removed\n";
                } else {
                    std::cout << "Invalid index\n";
                }
            } else if (type == 3 && !sharedPtrsVectorInt.empty()) {
                std::cout << "Enter index of SharedPtr to remove (0-" << sharedPtrsVectorInt.size() - 1 << "): ";
                int index;
                std::cin >> index;
                clearInputBuffer();
                if (index >= 0 && index < sharedPtrsVectorInt.size()) {
                    sharedPtrsVectorInt.erase(sharedPtrsVectorInt.begin() + index);
                    std::cout << "SharedPtr removed\n";
                } else {
                    std::cout << "Invalid index\n";
                }
            } else {
                std::cout << "No SharedPtrs\n";
            }
        } else if (choice == 8) {
            std::cout << "Enter resource type (1 - int, 2 - string, 3 - vector<int>): ";
            std::cin >> type;
            clearInputBuffer();

            std::cout << "Enter number of SharedPtrs to create: ";
            std::cin >> count;
            clearInputBuffer();

            if (type == 1) {
                int value;
                std::cout << "Enter resource value: ";
                std::cin >> value;
                clearInputBuffer();

                auto start = std::chrono::high_resolution_clock::now();
                for (int i = 0; i < count; ++i) {
                    sharedPtrsInt.push_back(SharedPtr<ResourceInt>(new ResourceInt("MultiShared", value)));
                }
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsed = end - start;
                std::cout << "Time to create " << count << " SharedPtrs: " << elapsed.count() << " s\n";

                std::vector<std::shared_ptr<ResourceInt>> stlSharedPtrs;
                start = std::chrono::high_resolution_clock::now();
                for (int i = 0; i < count; ++i) {
                    stlSharedPtrs.push_back(std::make_shared<ResourceInt>("MultiSTLShared", value));
                }
                end = std::chrono::high_resolution_clock::now();
                elapsed = end - start;
                std::cout << "Time to create " << count << " std::shared_ptrs: " << elapsed.count() << " s\n";
            } else if (type == 2) {
                std::string value;
                std::cout << "Enter resource value: ";
                std::cin >> value;
                clearInputBuffer();

                auto start = std::chrono::high_resolution_clock::now();
                for (int i = 0; i < count; ++i) {
                    sharedPtrsString.push_back(SharedPtr<ResourceString>(new ResourceString("MultiShared", value)));
                }
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsed = end - start;
                std::cout << "Time to create " << count << " SharedPtrs: " << elapsed.count() << " s\n";

                std::vector<std::shared_ptr<ResourceString>> stlSharedPtrs;
                start = std::chrono::high_resolution_clock::now();
                for (int i = 0; i < count; ++i) {
                    stlSharedPtrs.push_back(std::make_shared<ResourceString>("MultiSTLShared", value));
                }
                end = std::chrono::high_resolution_clock::now();
                elapsed = end - start;
                std::cout << "Time to create " << count << " std::shared_ptrs: " << elapsed.count() << " s\n";
            } else if (type == 3) {
                std::vector<int> value;
                std::cout << "Enter resource value (comma-separated integers): ";
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
                std::cout << "Time to create " << count << " SharedPtrs: " << elapsed.count() << " s\n";

                std::vector<std::shared_ptr<ResourceVectorInt>> stlSharedPtrs;
                start = std::chrono::high_resolution_clock::now();
                for (int i = 0; i < count; ++i) {
                    stlSharedPtrs.push_back(std::make_shared<ResourceVectorInt>("MultiSTLShared", value));
                }
                end = std::chrono::high_resolution_clock::now();
                elapsed = end - start;
                std::cout << "Time to create " << count << " std::shared_ptrs: " << elapsed.count() << " s\n";
            } else {
                std::cout << "Invalid type\n";
            }
        } else if (choice == 9) {
            sharedPtrsInt.resize(originalSizeInt);
            sharedPtrsString.resize(originalSizeString);
            sharedPtrsVectorInt.resize(originalSizeVectorInt);
            std::cout << "Created SharedPtrs removed\n";
        } else if (choice == 10) {
            break;
        } else {
            std::cout << "Invalid choice\n";
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
        std::cout << "1. Create SharedPtr\n";
        std::cout << "2. Create WeakPtr from SharedPtr\n";
        std::cout << "3. Lock WeakPtr\n";
        std::cout << "4. Use Count\n";
        std::cout << "5. Expired\n";
        std::cout << "6. Create Multiple WeakPtrs\n";
        std::cout << "7. Back to Main Menu\n";
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;
        clearInputBuffer();

        if (choice == 1) {
            std::cout << "Enter resource type (1 - int, 2 - string, 3 - vector<int>): ";
            std::cin >> type;
            clearInputBuffer();

            std::cout << "Enter resource name: ";
            std::cin >> name;
            clearInputBuffer();

            if (type == 1) {
                int value;
                std::cout << "Enter resource value: ";
                std::cin >> value;
                clearInputBuffer();
                sharedPtrInt.reset(new ResourceInt(name, value));
            } else if (type == 2) {
                std::string value;
                std::cout << "Enter resource value: ";
                std::cin >> value;
                clearInputBuffer();
                sharedPtrString.reset(new ResourceString(name, value));
            } else if (type == 3) {
                std::vector<int> value;
                std::cout << "Enter resource value (comma-separated integers): ";
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
                std::cout << "Invalid type\n";
            }
        } else if (choice == 2) {
            std::cout << "Enter resource type (1 - int, 2 - string, 3 - vector<int>): ";
            std::cin >> type;
            clearInputBuffer();

            if (type == 1 && sharedPtrInt) {
                weakPtrInt = sharedPtrInt;
                std::cout << "WeakPtr created from SharedPtr\n";
            } else if (type == 2 && sharedPtrString) {
                weakPtrString = sharedPtrString;
                std::cout << "WeakPtr created from SharedPtr\n";
            } else if (type == 3 && sharedPtrVectorInt) {
                weakPtrVectorInt = sharedPtrVectorInt;
                std::cout << "WeakPtr created from SharedPtr\n";
            } else {
                std::cout << "No resource managed by SharedPtr\n";
            }
        } else if (choice == 3) {
            std::cout << "Enter resource type (1 - int, 2 - string, 3 - vector<int>): ";
            std::cin >> type;
            clearInputBuffer();

            if (type == 1) {
                SharedPtr<ResourceInt> lockedPtr = weakPtrInt.lock();
                if (lockedPtr) {
                    lockedPtr->print();
                } else {
                    std::cout << "WeakPtr expired\n";
                }
            } else if (type == 2) {
                SharedPtr<ResourceString> lockedPtr = weakPtrString.lock();
                if (lockedPtr) {
                    lockedPtr->print();
                } else {
                    std::cout << "WeakPtr expired\n";
                }
            } else if (type == 3) {
                SharedPtr<ResourceVectorInt> lockedPtr = weakPtrVectorInt.lock();
                if (lockedPtr) {
                    lockedPtr->print();
                } else {
                    std::cout << "WeakPtr expired\n";
                }
            } else {
                std::cout << "Invalid type\n";
            }
        } else if (choice == 4) {
            std::cout << "Enter resource type (1 - int, 2 - string, 3 - vector<int>): ";
            std::cin >> type;
            clearInputBuffer();

            if (type == 1) {
                std::cout << "Use count: " << weakPtrInt.use_count() << std::endl;
            } else if (type == 2) {
                std::cout << "Use count: " << weakPtrString.use_count() << std::endl;
            } else if (type == 3) {
                std::cout << "Use count: " << weakPtrVectorInt.use_count() << std::endl;
            } else {
                std::cout << "Invalid type\n";
            }
        } else if (choice == 5) {
            std::cout << "Enter resource type (1 - int, 2 - string, 3 - vector<int>): ";
            std::cin >> type;
            clearInputBuffer();

            if (type == 1) {
                std::cout << "Expired: " << (weakPtrInt.expired() ? "Yes" : "No") << std::endl;
            } else if (type == 2) {
                std::cout << "Expired: " << (weakPtrString.expired() ? "Yes" : "No") << std::endl;
            } else if (type == 3) {
                std::cout << "Expired: " << (weakPtrVectorInt.expired() ? "Yes" : "No") << std::endl;
            } else {
                std::cout << "Invalid type\n";
            }
        } else if (choice == 6) {
            std::cout << "Enter resource type (1 - int, 2 - string, 3 - vector<int>): ";
            std::cin >> type;
            clearInputBuffer();

            std::cout << "Enter number of WeakPtrs to create: ";
            std::cin >> count;
            clearInputBuffer();

            if (type == 1) {
                auto start = std::chrono::high_resolution_clock::now();
                for (int i = 0; i < count; ++i) {
                    weakPtrInt = sharedPtrInt;
                }
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsed = end - start;
                std::cout << "Time to create " << count << " WeakPtrs: " << elapsed.count() << " s\n";

                std::weak_ptr<ResourceInt> stlWeakPtr;
                start = std::chrono::high_resolution_clock::now();
                for (int i = 0; i < count; ++i) {
                    stlWeakPtr = std::make_shared<ResourceInt>("MultiSTLShared", 0);
                }
                end = std::chrono::high_resolution_clock::now();
                elapsed = end - start;
                std::cout << "Time to create " << count << " std::weak_ptrs: " << elapsed.count() << " s\n";
            } else if (type == 2) {
                auto start = std::chrono::high_resolution_clock::now();
                for (int i = 0; i < count; ++i) {
                    weakPtrString = sharedPtrString;
                }
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsed = end - start;
                std::cout << "Time to create " << count << " WeakPtrs: " << elapsed.count() << " s\n";

                std::weak_ptr<ResourceString> stlWeakPtr;
                start = std::chrono::high_resolution_clock::now();
                for (int i = 0; i < count; ++i) {
                    stlWeakPtr = std::make_shared<ResourceString>("MultiSTLShared", "");
                }
                end = std::chrono::high_resolution_clock::now();
                elapsed = end - start;
                std::cout << "Time to create " << count << " std::weak_ptrs: " << elapsed.count() << " s\n";
            } else if (type == 3) {
                auto start = std::chrono::high_resolution_clock::now();
                for (int i = 0; i < count; ++i) {
                    weakPtrVectorInt = sharedPtrVectorInt;
                }
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsed = end - start;
                std::cout << "Time to create " << count << " WeakPtrs: " << elapsed.count() << " s\n";

                std::weak_ptr<ResourceVectorInt> stlWeakPtr;
                start = std::chrono::high_resolution_clock::now();
                for (int i = 0; i < count; ++i) {
                    stlWeakPtr = std::make_shared<ResourceVectorInt>("MultiSTLShared", std::vector<int>());
                }
                end = std::chrono::high_resolution_clock::now();
                elapsed = end - start;
                std::cout << "Time to create " << count << " std::weak_ptrs: " << elapsed.count() << " s\n";
            } else {
                std::cout << "Invalid type\n";
            }
        } else if (choice == 7) {
            break;
        } else {
            std::cout << "Invalid choice\n";
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
        std::cout << "1. Create UniquePtr\n";
        std::cout << "2. Get Resource\n";
        std::cout << "3. Release\n";
        std::cout << "4. Reset\n";
        std::cout << "5. Create Multiple UniquePtrs\n";
        std::cout << "6. Back to Main Menu\n";
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;
        clearInputBuffer();

        if (choice == 1) {
            std::cout << "Enter resource type (1 - int, 2 - string, 3 - vector<int>): ";
            std::cin >> type;
            clearInputBuffer();

            std::cout << "Enter resource name: ";
            std::cin >> name;
            clearInputBuffer();

            if (type == 1) {
                int value;
                std::cout << "Enter resource value: ";
                std::cin >> value;
                clearInputBuffer();
                uniquePtrInt.reset(new ResourceInt(name, value));
            } else if (type == 2) {
                std::string value;
                std::cout << "Enter resource value: ";
                std::cin >> value;
                clearInputBuffer();
                uniquePtrString.reset(new ResourceString(name, value));
            } else if (type == 3) {
                std::vector<int> value;
                std::cout << "Enter resource value (comma-separated integers): ";
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
                std::cout << "Invalid type\n";
            }
        } else if (choice == 2) {
            std::cout << "Enter resource type (1 - int, 2 - string, 3 - vector<int>): ";
            std::cin >> type;
            clearInputBuffer();

            if (type == 1 && uniquePtrInt.get()) {
                uniquePtrInt->print();
            } else if (type == 2 && uniquePtrString.get()) {
                uniquePtrString->print();
            } else if (type == 3 && uniquePtrVectorInt.get()) {
                uniquePtrVectorInt->print();
            } else {
                std::cout << "No resource managed by UniquePtr\n";
            }
        } else if (choice == 3) {
            std::cout << "Enter resource type (1 - int, 2 - string, 3 - vector<int>): ";
            std::cin >> type;
            clearInputBuffer();

            if (type == 1) {
                ResourceInt* ptr = uniquePtrInt.release();
                if (ptr) {
                    std::cout << "Resource released\n";
                } else {
                    std::cout << "No resource managed by UniquePtr\n";
                }
            } else if (type == 2) {
                ResourceString* ptr = uniquePtrString.release();
                if (ptr) {
                    std::cout << "Resource released\n";
                } else {
                    std::cout << "No resource managed by UniquePtr\n";
                }
            } else if (type == 3) {
                ResourceVectorInt* ptr = uniquePtrVectorInt.release();
                if (ptr) {
                    std::cout << "Resource released\n";
                } else {
                    std::cout << "No resource managed by UniquePtr\n";
                }
            } else {
                std::cout << "Invalid type\n";
            }
        } else if (choice == 4) {
            std::cout << "Enter resource type (1 - int, 2 - string, 3 - vector<int>): ";
            std::cin >> type;
            clearInputBuffer();

            if (type == 1) {
                uniquePtrInt.reset();
                std::cout << "UniquePtr reset\n";
            } else if (type == 2) {
                uniquePtrString.reset();
                std::cout << "UniquePtr reset\n";
            } else if (type == 3) {
                uniquePtrVectorInt.reset();
                std::cout << "UniquePtr reset\n";
            } else {
                std::cout << "Invalid type\n";
            }
        } else if (choice == 5) {
            std::cout << "Enter resource type (1 - int, 2 - string, 3 - vector<int>): ";
            std::cin >> type;
            clearInputBuffer();

            std::cout << "Enter number of UniquePtrs to create: ";
            std::cin >> count;
            clearInputBuffer();

            if (type == 1) {
                int value;
                std::cout << "Enter resource value: ";
                std::cin >> value;
                clearInputBuffer();

                auto start = std::chrono::high_resolution_clock::now();
                for (int i = 0; i < count; ++i) {
                    uniquePtrInt.reset(new ResourceInt("MultiUnique", value));
                }
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsed = end - start;
                std::cout << "Time to create " << count << " UniquePtrs: " << elapsed.count() << " s\n";

                std::vector<std::unique_ptr<ResourceInt>> stlUniquePtrs;
                start = std::chrono::high_resolution_clock::now();
                for (int i = 0; i < count; ++i) {
                    stlUniquePtrs.push_back(std::make_unique<ResourceInt>("MultiSTLUnique", value));
                }
                end = std::chrono::high_resolution_clock::now();
                elapsed = end - start;
                std::cout << "Time to create " << count << " std::unique_ptrs: " << elapsed.count() << " s\n";
            } else if (type == 2) {
                std::string value;
                std::cout << "Enter resource value: ";
                std::cin >> value;
                clearInputBuffer();

                auto start = std::chrono::high_resolution_clock::now();
                for (int i = 0; i < count; ++i) {
                    uniquePtrString.reset(new ResourceString("MultiUnique", value));
                }
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsed = end - start;
                std::cout << "Time to create " << count << " UniquePtrs: " << elapsed.count() << " s\n";

                std::vector<std::unique_ptr<ResourceString>> stlUniquePtrs;
                start = std::chrono::high_resolution_clock::now();
                for (int i = 0; i < count; ++i) {
                    stlUniquePtrs.push_back(std::make_unique<ResourceString>("MultiSTLUnique", value));
                }
                end = std::chrono::high_resolution_clock::now();
                elapsed = end - start;
                std::cout << "Time to create " << count << " std::unique_ptrs: " << elapsed.count() << " s\n";
            } else if (type == 3) {
                std::vector<int> value;
                std::cout << "Enter resource value (comma-separated integers): ";
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
                std::cout << "Time to create " << count << " UniquePtrs: " << elapsed.count() << " s\n";

                std::vector<std::unique_ptr<ResourceVectorInt>> stlUniquePtrs;
                start = std::chrono::high_resolution_clock::now();
                for (int i = 0; i < count; ++i) {
                    stlUniquePtrs.push_back(std::make_unique<ResourceVectorInt>("MultiSTLUnique", value));
                }
                end = std::chrono::high_resolution_clock::now();
                elapsed = end - start;
                std::cout << "Time to create " << count << " std::unique_ptrs: " << elapsed.count() << " s\n";
            } else {
                std::cout << "Invalid type\n";
            }
        } else if (choice == 6) {
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
            std::cout << "Invalid choice\n";
        }
    }

    return 0;
}
