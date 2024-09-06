#pragma once
#include <iostream>
#include <memory>


template <typename T, typename deleter = std::default_delete<T>>
class Unique_Ptr {
private:
    T* ptr;
    deleter del; // functional object
    
public:
    Unique_Ptr(T* ptr): ptr(ptr) {} // constructor_1

    Unique_Ptr(T* ptr, deleter) {} // consytructor_2

    ~Unique_Ptr() { // destructor
        deleter(ptr);
    }

    


    T& operator*() const { return *ptr; }
    T* operator->() const noexcept { return ptr; }
    T* get() const { return ptr; }
};


