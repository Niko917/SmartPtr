#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <chrono>
#include "../include/WeakPtr.hpp"
#include "../include/SharedPtr.hpp"
#include "../include/UniquePtr.hpp"

template<typename T>
class Resource {
public:
    Resource(const std::string& name, const T& value, bool silent = false) : name_(name), value_(value), silent_(silent) {
        if (!silent_) {
            std::cout << "\nResource " << name_ << " created with value ";
            printValue(value_);
            std::cout << std::endl;
        }
    }

    ~Resource() {
        if (!silent_) {
            std::cout << "\nResource " << name_ << " destroyed" << std::endl;
        }
    }

    void print() const {
        std::cout << "Resource " << name_ << " has value ";
        printValue(value_);
        std::cout << std::endl;
    }

private:
    std::string name_;
    T value_;
    bool silent_;

    template<typename U>
    void printValue(const U& value) const {
        std::cout << value;
    }

    void printValue(const std::vector<int>& value) const {
        for (int v : value) {
            std::cout << v << " ";
        }
    }
};

template<typename T>
using SharedPtrVector = std::vector<SharedPtr<Resource<T>>>;

template<typename T>
using UniquePtrVector = std::vector<UniquePtr<Resource<T>>>;

void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

template<typename T>
T createResourceValue() {
    if constexpr (std::is_same_v<T, std::vector<int>>) {
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
        return value;
    } else {
        T value;
        std::cout << "\nEnter resource value: ";
        std::cin >> value;
        clearInputBuffer();
        return value;
    }
}

template<typename T>
void printResource(const SharedPtr<Resource<T>>& ptr) {
    if (ptr) {
        ptr->print();
    } else {
        std::cout << "\nNo resource managed by SharedPtr\n";
    }
}

template<typename T>
void createSharedPtr(SharedPtrVector<T>& sharedPtrs) {
    std::string name;
    std::cout << "\nEnter resource name: ";
    std::cin >> name;
    clearInputBuffer();

    T value = createResourceValue<T>();
    sharedPtrs.push_back(SharedPtr<Resource<T>>(new Resource<T>(name, value)));
}

template<typename T>
void createSharedPtrFromExisting(SharedPtrVector<T>& sharedPtrs) {
    if (sharedPtrs.empty()) {
        std::cout << "\nNo existing SharedPtrs\n";
        return;
    }

    std::cout << "\nEnter index of existing SharedPtr (0-" << sharedPtrs.size() - 1 << "): ";
    int index;
    std::cin >> index;
    clearInputBuffer();

    if (index >= 0 && index < sharedPtrs.size()) {
        sharedPtrs.push_back(sharedPtrs[index]);
        std::cout << "\nSharedPtr created to existing resource\n";
    } else {
        std::cout << "\nInvalid index\n";
    }
}

template<typename T>
void getResource(const SharedPtrVector<T>& sharedPtrs) {
    if (sharedPtrs.empty()) {
        std::cout << "\nNo SharedPtrs\n";
        return;
    }

    std::cout << "\nEnter index of SharedPtr (0-" << sharedPtrs.size() - 1 << "): ";
    int index;
    std::cin >> index;
    clearInputBuffer();

    if (index >= 0 && index < sharedPtrs.size()) {
        printResource(sharedPtrs[index]);
    } else {
        std::cout << "\nInvalid index\n";
    }
}

template<typename T>
void getUseCount(const SharedPtrVector<T>& sharedPtrs) {
    if (sharedPtrs.empty()) {
        std::cout << "No SharedPtrs\n";
        return;
    }

    std::cout << "\nEnter index of SharedPtr (0-" << sharedPtrs.size() - 1 << "): ";
    int index;
    std::cin >> index;
    clearInputBuffer();

    if (index >= 0 && index < sharedPtrs.size()) {
        std::cout << "\nUse count: " << sharedPtrs[index].use_count() << std::endl;
    } else {
        std::cout << "\nInvalid index\n";
    }
}

template<typename T>
void resetSharedPtr(SharedPtrVector<T>& sharedPtrs) {
    if (sharedPtrs.empty()) {
        std::cout << "No SharedPtrs\n";
        return;
    }

    std::cout << "\nEnter index of SharedPtr to reset (0-" << sharedPtrs.size() - 1 << "): ";
    int index;
    std::cin >> index;
    clearInputBuffer();

    if (index >= 0 && index < sharedPtrs.size()) {
        sharedPtrs[index].reset();
        std::cout << "\nSharedPtr reset\n";
    } else {
        std::cout << "\nInvalid index\n";
    }
}

template<typename T>
void listAllSharedPtrs(const SharedPtrVector<T>& sharedPtrs) {
    if (sharedPtrs.empty()) {
        std::cout << "No SharedPtrs\n";
        return;
    }

    for (size_t i = 0; i < sharedPtrs.size(); ++i) {
        std::cout << "\nSharedPtr " << i << ": ";
        printResource(sharedPtrs[i]);
    }
}

template<typename T>
void removeSharedPtr(SharedPtrVector<T>& sharedPtrs) {
    if (sharedPtrs.empty()) {
        std::cout << "No SharedPtrs\n";
        return;
    }

    std::cout << "\nEnter index of SharedPtr to remove (0-" << sharedPtrs.size() - 1 << "): ";
    int index;
    std::cin >> index;
    clearInputBuffer();

    if (index >= 0 && index < sharedPtrs.size()) {
        sharedPtrs.erase(sharedPtrs.begin() + index);
        std::cout << "\nSharedPtr removed\n";
    } else {
        std::cout << "\nInvalid index\n";
    }
}

template<typename T>
void createMultipleSharedPtrs(SharedPtrVector<T>& sharedPtrs, int count) {
    T value = createResourceValue<T>();

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < count; ++i) {
        sharedPtrs.push_back(SharedPtr<Resource<T>>(new Resource<T>("MultiShared", value, true)));
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "\nTime to create " << count << " SharedPtrs: " << elapsed.count() << " s\n";

    std::vector<std::shared_ptr<Resource<T>>> stlSharedPtrs;
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < count; ++i) {
        stlSharedPtrs.push_back(std::make_shared<Resource<T>>("MultiSTLShared", value, true));
    }
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "\nTime to create " << count << " std::shared_ptrs: " << elapsed.count() << " s\n";
}

template<typename T>
void removeCreatedSharedPtrs(SharedPtrVector<T>& sharedPtrs, size_t originalSize) {
    sharedPtrs.resize(originalSize);
}

void sharedPtrMenu() {
    SharedPtrVector<int> sharedPtrsInt;
    SharedPtrVector<std::string> sharedPtrsString;
    SharedPtrVector<std::vector<int>> sharedPtrsVectorInt;
    SharedPtrVector<char> sharedPtrsChar;
    SharedPtrVector<bool> sharedPtrsBool;
    SharedPtrVector<double> sharedPtrsDouble;

    size_t originalSizeInt = sharedPtrsInt.size();
    size_t originalSizeString = sharedPtrsString.size();
    size_t originalSizeVectorInt = sharedPtrsVectorInt.size();
    size_t originalSizeChar = sharedPtrsChar.size();
    size_t originalSizeBool = sharedPtrsBool.size();
    size_t originalSizeDouble = sharedPtrsDouble.size();

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
            std::cout << "\nEnter resource type (1 - int, 2 - string, 3 - vector<int>, 4 - char, 5 - bool, 6 - double): ";
            int type;
            std::cin >> type;
            clearInputBuffer();

            if (type == 1) {
                createSharedPtr(sharedPtrsInt);
            } else if (type == 2) {
                createSharedPtr(sharedPtrsString);
            } else if (type == 3) {
                createSharedPtr(sharedPtrsVectorInt);
            } else if (type == 4) {
                createSharedPtr(sharedPtrsChar);
            } else if (type == 5) {
                createSharedPtr(sharedPtrsBool);
            } else if (type == 6) {
                createSharedPtr(sharedPtrsDouble);
            } else {
                std::cout << "\nInvalid type\n";
            }
        } else if (choice == 2) {
            std::cout << "\nEnter resource type (1 - int, 2 - string, 3 - vector<int>, 4 - char, 5 - bool, 6 - double): ";
            int type;
            std::cin >> type;
            clearInputBuffer();

            if (type == 1) {
                createSharedPtrFromExisting(sharedPtrsInt);
            } else if (type == 2) {
                createSharedPtrFromExisting(sharedPtrsString);
            } else if (type == 3) {
                createSharedPtrFromExisting(sharedPtrsVectorInt);
            } else if (type == 4) {
                createSharedPtrFromExisting(sharedPtrsChar);
            } else if (type == 5) {
                createSharedPtrFromExisting(sharedPtrsBool);
            } else if (type == 6) {
                createSharedPtrFromExisting(sharedPtrsDouble);
            } else {
                std::cout << "\nInvalid type\n";
            }
        } else if (choice == 3) {
            std::cout << "\nEnter resource type (1 - int, 2 - string, 3 - vector<int>, 4 - char, 5 - bool, 6 - double): ";
            int type;
            std::cin >> type;
            clearInputBuffer();

            if (type == 1) {
                getResource(sharedPtrsInt);
            } else if (type == 2) {
                getResource(sharedPtrsString);
            } else if (type == 3) {
                getResource(sharedPtrsVectorInt);
            } else if (type == 4) {
                getResource(sharedPtrsChar);
            } else if (type == 5) {
                getResource(sharedPtrsBool);
            } else if (type == 6) {
                getResource(sharedPtrsDouble);
            } else {
                std::cout << "\nInvalid type\n";
            }
        } else if (choice == 4) {
            std::cout << "\nEnter resource type (1 - int, 2 - string, 3 - vector<int>, 4 - char, 5 - bool, 6 - double): ";
            int type;
            std::cin >> type;
            clearInputBuffer();

            if (type == 1) {
                getUseCount(sharedPtrsInt);
            } else if (type == 2) {
                getUseCount(sharedPtrsString);
            } else if (type == 3) {
                getUseCount(sharedPtrsVectorInt);
            } else if (type == 4) {
                getUseCount(sharedPtrsChar);
            } else if (type == 5) {
                getUseCount(sharedPtrsBool);
            } else if (type == 6) {
                getUseCount(sharedPtrsDouble);
            } else {
                std::cout << "\nInvalid type\n";
            }
        } else if (choice == 5) {
            std::cout << "\nEnter resource type (1 - int, 2 - string, 3 - vector<int>, 4 - char, 5 - bool, 6 - double): ";
            int type;
            std::cin >> type;
            clearInputBuffer();

            if (type == 1) {
                resetSharedPtr(sharedPtrsInt);
            } else if (type == 2) {
                resetSharedPtr(sharedPtrsString);
            } else if (type == 3) {
                resetSharedPtr(sharedPtrsVectorInt);
            } else if (type == 4) {
                resetSharedPtr(sharedPtrsChar);
            } else if (type == 5) {
                resetSharedPtr(sharedPtrsBool);
            } else if (type == 6) {
                resetSharedPtr(sharedPtrsDouble);
            } else {
                std::cout << "\nInvalid type\n";
            }
        } else if (choice == 6) {
            std::cout << "\nSharedPtrs (int): ";
            listAllSharedPtrs(sharedPtrsInt);

            std::cout << "\nSharedPtrs (string): ";
            listAllSharedPtrs(sharedPtrsString);

            std::cout << "\nSharedPtrs (vector<int>): ";
            listAllSharedPtrs(sharedPtrsVectorInt);

            std::cout << "\nSharedPtrs (char): ";
            listAllSharedPtrs(sharedPtrsChar);

            std::cout << "\nSharedPtrs (bool): ";
            listAllSharedPtrs(sharedPtrsBool);

            std::cout << "\nSharedPtrs (double): ";
            listAllSharedPtrs(sharedPtrsDouble);
        } else if (choice == 7) {
            std::cout << "\nEnter resource type (1 - int, 2 - string, 3 - vector<int>, 4 - char, 5 - bool, 6 - double): ";
            int type;
            std::cin >> type;
            clearInputBuffer();

            if (type == 1) {
                removeSharedPtr(sharedPtrsInt);
            } else if (type == 2) {
                removeSharedPtr(sharedPtrsString);
            } else if (type == 3) {
                removeSharedPtr(sharedPtrsVectorInt);
            } else if (type == 4) {
                removeSharedPtr(sharedPtrsChar);
            } else if (type == 5) {
                removeSharedPtr(sharedPtrsBool);
            } else if (type == 6) {
                removeSharedPtr(sharedPtrsDouble);
            } else {
                std::cout << "\nInvalid type\n";
            }
        } else if (choice == 8) {
            std::cout << "\nEnter resource type (1 - int, 2 - string, 3 - vector<int>, 4 - char, 5 - bool, 6 - double): ";
            int type;
            std::cin >> type;
            clearInputBuffer();

            int count;
            std::cout << "\nEnter number of SharedPtrs to create: ";
            std::cin >> count;
            clearInputBuffer();

            if (type == 1) {
                createMultipleSharedPtrs(sharedPtrsInt, count);
            } else if (type == 2) {
                createMultipleSharedPtrs(sharedPtrsString, count);
            } else if (type == 3) {
                createMultipleSharedPtrs(sharedPtrsVectorInt, count);
            } else if (type == 4) {
                createMultipleSharedPtrs(sharedPtrsChar, count);
            } else if (type == 5) {
                createMultipleSharedPtrs(sharedPtrsBool, count);
            } else if (type == 6) {
                createMultipleSharedPtrs(sharedPtrsDouble, count);
            } else {
                std::cout << "\nInvalid type\n";
            }
        } else if (choice == 9) {
            removeCreatedSharedPtrs(sharedPtrsInt, originalSizeInt);
            removeCreatedSharedPtrs(sharedPtrsString, originalSizeString);
            removeCreatedSharedPtrs(sharedPtrsVectorInt, originalSizeVectorInt);
            removeCreatedSharedPtrs(sharedPtrsChar, originalSizeChar);
            removeCreatedSharedPtrs(sharedPtrsBool, originalSizeBool);
            removeCreatedSharedPtrs(sharedPtrsDouble, originalSizeDouble);
        } else if (choice == 10) {
            break;
        } else {
            std::cout << "\nInvalid choice\n";
        }
    }
}

template<typename T>
void createWeakPtr(SharedPtr<Resource<T>>& sharedPtr, WeakPtr<Resource<T>>& weakPtr) {
    if (sharedPtr) {
        weakPtr = sharedPtr;
        std::cout << "\nWeakPtr created from SharedPtr\n";
    } else {
        std::cout << "\nNo resource managed by SharedPtr\n";
    }
}

template<typename T>
void lockWeakPtr(const WeakPtr<Resource<T>>& weakPtr) {
    SharedPtr<Resource<T>> lockedPtr = weakPtr.lock();
    if (lockedPtr) {
        lockedPtr->print();
    } else {
        std::cout << "\nWeakPtr expired\n";
    }
}

template<typename T>
void getWeakPtrUseCount(const WeakPtr<Resource<T>>& weakPtr) {
    std::cout << "\nUse count: " << weakPtr.use_count() << std::endl;
}

template<typename T>
void checkWeakPtrExpired(const WeakPtr<Resource<T>>& weakPtr) {
    std::cout << "\nExpired: " << (weakPtr.expired() ? "Yes" : "No") << std::endl;
}

template<typename T>
void createMultipleWeakPtrs(SharedPtr<Resource<T>>& sharedPtr, int count) {
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < count; ++i) {
        WeakPtr<Resource<T>> weakPtr = sharedPtr;
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "\nTime to create " << count << " WeakPtrs: " << elapsed.count() << " s\n";

    std::weak_ptr<Resource<T>> stlWeakPtr;
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < count; ++i) {
        stlWeakPtr = std::make_shared<Resource<T>>("MultiSTLShared", T(), true);
    }
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "\nTime to create " << count << " std::weak_ptrs: " << elapsed.count() << " s\n";
}

void weakPtrMenu() {
    SharedPtr<Resource<int>> sharedPtrInt;
    SharedPtr<Resource<std::string>> sharedPtrString;
    SharedPtr<Resource<std::vector<int>>> sharedPtrVectorInt;
    SharedPtr<Resource<char>> sharedPtrChar;
    SharedPtr<Resource<bool>> sharedPtrBool;
    SharedPtr<Resource<double>> sharedPtrDouble;
    WeakPtr<Resource<int>> weakPtrInt;
    WeakPtr<Resource<std::string>> weakPtrString;
    WeakPtr<Resource<std::vector<int>>> weakPtrVectorInt;
    WeakPtr<Resource<char>> weakPtrChar;
    WeakPtr<Resource<bool>> weakPtrBool;
    WeakPtr<Resource<double>> weakPtrDouble;

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
            std::cout << "\nEnter resource type (1 - int, 2 - string, 3 - vector<int>, 4 - char, 5 - bool, 6 - double): ";
            int type;
            std::cin >> type;
            clearInputBuffer();

            std::string name;
            std::cout << "\nEnter resource name: ";
            std::cin >> name;
            clearInputBuffer();

            if (type == 1) {
                int value = createResourceValue<int>();
                sharedPtrInt.reset(new Resource<int>(name, value));
            } else if (type == 2) {
                std::string value = createResourceValue<std::string>();
                sharedPtrString.reset(new Resource<std::string>(name, value));
            } else if (type == 3) {
                std::vector<int> value = createResourceValue<std::vector<int>>();
                sharedPtrVectorInt.reset(new Resource<std::vector<int>>(name, value));
            } else if (type == 4) {
                char value = createResourceValue<char>();
                sharedPtrChar.reset(new Resource<char>(name, value));
            } else if (type == 5) {
                bool value = createResourceValue<bool>();
                sharedPtrBool.reset(new Resource<bool>(name, value));
            } else if (type == 6) {
                double value = createResourceValue<double>();
                sharedPtrDouble.reset(new Resource<double>(name, value));
            } else {
                std::cout << "\nInvalid type\n";
            }
        } else if (choice == 2) {
            std::cout << "\nEnter resource type (1 - int, 2 - string, 3 - vector<int>, 4 - char, 5 - bool, 6 - double): ";
            int type;
            std::cin >> type;
            clearInputBuffer();

            if (type == 1) {
                createWeakPtr(sharedPtrInt, weakPtrInt);
            } else if (type == 2) {
                createWeakPtr(sharedPtrString, weakPtrString);
            } else if (type == 3) {
                createWeakPtr(sharedPtrVectorInt, weakPtrVectorInt);
            } else if (type == 4) {
                createWeakPtr(sharedPtrChar, weakPtrChar);
            } else if (type == 5) {
                createWeakPtr(sharedPtrBool, weakPtrBool);
            } else if (type == 6) {
                createWeakPtr(sharedPtrDouble, weakPtrDouble);
            } else {
                std::cout << "\nInvalid type\n";
            }
        } else if (choice == 3) {
            std::cout << "\nEnter resource type (1 - int, 2 - string, 3 - vector<int>, 4 - char, 5 - bool, 6 - double): ";
            int type;
            std::cin >> type;
            clearInputBuffer();

            if (type == 1) {
                lockWeakPtr(weakPtrInt);
            } else if (type == 2) {
                lockWeakPtr(weakPtrString);
            } else if (type == 3) {
                lockWeakPtr(weakPtrVectorInt);
            } else if (type == 4) {
                lockWeakPtr(weakPtrChar);
            } else if (type == 5) {
                lockWeakPtr(weakPtrBool);
            } else if (type == 6) {
                lockWeakPtr(weakPtrDouble);
            } else {
                std::cout << "\nInvalid type\n";
            }
        } else if (choice == 4) {
            std::cout << "\nEnter resource type (1 - int, 2 - string, 3 - vector<int>, 4 - char, 5 - bool, 6 - double): ";
            int type;
            std::cin >> type;
            clearInputBuffer();

            if (type == 1) {
                getWeakPtrUseCount(weakPtrInt);
            } else if (type == 2) {
                getWeakPtrUseCount(weakPtrString);
            } else if (type == 3) {
                getWeakPtrUseCount(weakPtrVectorInt);
            } else if (type == 4) {
                getWeakPtrUseCount(weakPtrChar);
            } else if (type == 5) {
                getWeakPtrUseCount(weakPtrBool);
            } else if (type == 6) {
                getWeakPtrUseCount(weakPtrDouble);
            } else {
                std::cout << "\nInvalid type\n";
            }
        } else if (choice == 5) {
            std::cout << "\nEnter resource type (1 - int, 2 - string, 3 - vector<int>, 4 - char, 5 - bool, 6 - double): ";
            int type;
            std::cin >> type;
            clearInputBuffer();

            if (type == 1) {
                checkWeakPtrExpired(weakPtrInt);
            } else if (type == 2) {
                checkWeakPtrExpired(weakPtrString);
            } else if (type == 3) {
                checkWeakPtrExpired(weakPtrVectorInt);
            } else if (type == 4) {
                checkWeakPtrExpired(weakPtrChar);
            } else if (type == 5) {
                checkWeakPtrExpired(weakPtrBool);
            } else if (type == 6) {
                checkWeakPtrExpired(weakPtrDouble);
            } else {
                std::cout << "\nInvalid type\n";
            }
        } else if (choice == 6) {
            std::cout << "\nEnter resource type (1 - int, 2 - string, 3 - vector<int>, 4 - char, 5 - bool, 6 - double): ";
            int type;
            std::cin >> type;
            clearInputBuffer();

            int count;
            std::cout << "\nEnter number of WeakPtrs to create: ";
            std::cin >> count;
            clearInputBuffer();

            if (type == 1) {
                createMultipleWeakPtrs(sharedPtrInt, count);
            } else if (type == 2) {
                createMultipleWeakPtrs(sharedPtrString, count);
            } else if (type == 3) {
                createMultipleWeakPtrs(sharedPtrVectorInt, count);
            } else if (type == 4) {
                createMultipleWeakPtrs(sharedPtrChar, count);
            } else if (type == 5) {
                createMultipleWeakPtrs(sharedPtrBool, count);
            } else if (type == 6) {
                createMultipleWeakPtrs(sharedPtrDouble, count);
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

template<typename T>
void createUniquePtr(UniquePtr<Resource<T>>& uniquePtr) {
    std::string name;
    std::cout << "\nEnter resource name: ";
    std::cin >> name;
    clearInputBuffer();

    T value = createResourceValue<T>();
    uniquePtr.reset(new Resource<T>(name, value));
}

template<typename T>
void getUniquePtrResource(const UniquePtr<Resource<T>>& uniquePtr) {
    if (uniquePtr.get()) {
        uniquePtr->print();
    } else {
        std::cout << "\nNo resource managed by UniquePtr\n";
    }
}

template<typename T>
void releaseUniquePtr(UniquePtr<Resource<T>>& uniquePtr) {
    Resource<T>* ptr = uniquePtr.release();

    if (ptr) {
        std::cout << "\nResource released\n";
    } else {
        std::cout << "\nNo resource managed by UniquePtr\n";
    }
}

template<typename T>
void resetUniquePtr(UniquePtr<Resource<T>>& uniquePtr) {
    uniquePtr.reset();
    std::cout << "\nUniquePtr reset\n";
}

template<typename T>
void createMultipleUniquePtrs(UniquePtr<Resource<T>>& uniquePtr, int count) {
    T value = createResourceValue<T>();

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < count; ++i) {
        uniquePtr.reset(new Resource<T>("MultiUnique", value, true));
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "\nTime to create " << count << " UniquePtrs: " << elapsed.count() << " s\n";

    std::vector<std::unique_ptr<Resource<T>>> stlUniquePtrs;
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < count; ++i) {
        stlUniquePtrs.push_back(std::make_unique<Resource<T>>("MultiSTLUnique", value, true));
    }
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "\nTime to create " << count << " std::unique_ptrs: " << elapsed.count() << " s\n";
}


void uniquePtrMenu() {
    UniquePtr<Resource<int>> uniquePtrInt;
    UniquePtr<Resource<std::string>> uniquePtrString;
    UniquePtr<Resource<std::vector<int>>> uniquePtrVectorInt;
    UniquePtr<Resource<char>> uniquePtrChar;
    UniquePtr<Resource<bool>> uniquePtrBool;
    UniquePtr<Resource<double>> uniquePtrDouble;

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
            std::cout << "\nEnter resource type (1 - int, 2 - string, 3 - vector<int>, 4 - char, 5 - bool, 6 - double): ";
            int type;
            std::cin >> type;
            clearInputBuffer();

            if (type == 1) {
                createUniquePtr(uniquePtrInt);
            } else if (type == 2) {
                createUniquePtr(uniquePtrString);
            } else if (type == 3) {
                createUniquePtr(uniquePtrVectorInt);
            } else if (type == 4) {
                createUniquePtr(uniquePtrChar);
            } else if (type == 5) {
                createUniquePtr(uniquePtrBool);
            } else if (type == 6) {
                createUniquePtr(uniquePtrDouble);
            } else {
                std::cout << "\nInvalid type\n";
            }
        } else if (choice == 2) {
            std::cout << "\nEnter resource type (1 - int, 2 - string, 3 - vector<int>, 4 - char, 5 - bool, 6 - double): ";
            int type;
            std::cin >> type;
            clearInputBuffer();

            if (type == 1) {
                getUniquePtrResource(uniquePtrInt);
            } else if (type == 2) {
                getUniquePtrResource(uniquePtrString);
            } else if (type == 3) {
                getUniquePtrResource(uniquePtrVectorInt);
            } else if (type == 4) {
                getUniquePtrResource(uniquePtrChar);
            } else if (type == 5) {
                getUniquePtrResource(uniquePtrBool);
            } else if (type == 6) {
                getUniquePtrResource(uniquePtrDouble);
            } else {
                std::cout << "\nInvalid type\n";
            }
        } else if (choice == 3) {
            std::cout << "\nEnter resource type (1 - int, 2 - string, 3 - vector<int>, 4 - char, 5 - bool, 6 - double): ";
            int type;
            std::cin >> type;
            clearInputBuffer();

            if (type == 1) {
                releaseUniquePtr(uniquePtrInt);
            } else if (type == 2) {
                releaseUniquePtr(uniquePtrString);
            } else if (type == 3) {
                releaseUniquePtr(uniquePtrVectorInt);
            } else if (type == 4) {
                releaseUniquePtr(uniquePtrChar);
            } else if (type == 5) {
                releaseUniquePtr(uniquePtrBool);
            } else if (type == 6) {
                releaseUniquePtr(uniquePtrDouble);
            } else {
                std::cout << "\nInvalid type\n";
            }
        } else if (choice == 4) {
            std::cout << "\nEnter resource type (1 - int, 2 - string, 3 - vector<int>, 4 - char, 5 - bool, 6 - double): ";
            int type;
            std::cin >> type;
            clearInputBuffer();

            if (type == 1) {
                resetUniquePtr(uniquePtrInt);
            } else if (type == 2) {
                resetUniquePtr(uniquePtrString);
            } else if (type == 3) {
                resetUniquePtr(uniquePtrVectorInt);
            } else if (type == 4) {
                resetUniquePtr(uniquePtrChar);
            } else if (type == 5) {
                resetUniquePtr(uniquePtrBool);
            } else if (type == 6) {
                resetUniquePtr(uniquePtrDouble);
            } else {
                std::cout << "\nInvalid type\n";
            }
        } else if (choice == 5) {
            std::cout << "\nEnter resource type (1 - int, 2 - string, 3 - vector<int>, 4 - char, 5 - bool, 6 - double): ";
            int type;
            std::cin >> type;
            clearInputBuffer();

            int count;
            std::cout << "\nEnter number of UniquePtrs to create: ";
            std::cin >> count;
            clearInputBuffer();

            if (type == 1) {
                createMultipleUniquePtrs(uniquePtrInt, count);
            } else if (type == 2) {
                createMultipleUniquePtrs(uniquePtrString, count);
            } else if (type == 3) {
                createMultipleUniquePtrs(uniquePtrVectorInt, count);
            } else if (type == 4) {
                createMultipleUniquePtrs(uniquePtrChar, count);
            } else if (type == 5) {
                createMultipleUniquePtrs(uniquePtrBool, count);
            } else if (type == 6) {
                createMultipleUniquePtrs(uniquePtrDouble, count);
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
