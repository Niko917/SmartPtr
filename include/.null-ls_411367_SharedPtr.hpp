#pragma once
#include <cstddef>
#include <memory>
#include <optional>
#include <utility>
#include "ControlBlock.hpp"
#include "WeakPtr.hpp"


template <typename T, typename Deleter = std::default_delete<T>>
class SharedPtr { 
private:
    T* ptr;
    ControlBlock* RefCounter;

    Deleter deleter;
   
public:
    
    SharedPtr() noexcept : ptr(nullptr), RefCounter(new ControlBlock(true)), deleter() {}

    explicit SharedPtr(T* ptr) : ptr(ptr), RefCounter(new ControlBlock(true)), deleter() {}

    SharedPtr(T* ptr, ControlBlock* rc) : ptr(ptr), RefCounter(std::move(rc)) {
        if (RefCounter) {
            RefCounter->IncrementShared();
        }
    }

    
    SharedPtr(const SharedPtr& other) : ptr(other.get()), RefCounter(other.RefCounter), deleter(other.deleter) {
        if (RefCounter) {
            RefCounter->IncrementShared();
        }
    }

    
    SharedPtr(SharedPtr&& other) noexcept : ptr(other.get()), RefCounter(other.RefCounter), deleter(std::move(other.deleter)) {
        other.ptr = nullptr;
        other.RefCounter = nullptr;
    }

    
    ~SharedPtr() {
        release();
    }

    
    SharedPtr& operator=(const SharedPtr& other) {
        if (this != other) {
            release();

            ptr = other.ptr;
            RefCounter = other.RefCounter;

            if (RefCounter) {
                RefCounter->IncrementShared();
            }
        }
        return *this;
    }


    SharedPtr& operator=(SharedPtr&& other) noexcept {
        if (this != &other) {
            release();
            ptr = other.ptr;
            RefCounter = other.RefCounter;
            deleter = std::move(other.deleter);

            other.ptr = nullptr;
            other.RefCounter = nullptr;
        }
        return *this;
    }


    std::optional<T&> operator*() const {
        if (ptr) {
            return *ptr;
        }
        return std::nullopt;
    }


    T* get() const noexcept {
        return ptr;
    }

    
    size_t use_count() const noexcept {
        if (ptr) {
            return RefCounter->SharedCount();
        }
        return 0;
    }

    T* operator->() const {
        return ptr;
    }


    bool unique() const noexcept {
        return use_count() == 1;
    }


    void reset(T* new_ptr) {
        if (ptr != new_ptr) {
            release();
            ptr = new_ptr;

            RefCounter = new ControlBlock(true);
            if (RefCounter) {
                RefCounter->IncrementShared();
            }
        }
        return;
    }


   void swap(SharedPtr& other) noexcept {
        MySwap(ptr, other.ptr);
        MySwap(RefCounter, other.RefCounter);
        MySwap(deleter, other.deleter);
    }

private:

    void release() {
        if (RefCounter) {
            
            RefCounter->DecrementShared();
            
            if (RefCounter->SharedCount() == 0) {
                deleter(ptr);

                if (RefCounter->WeakCount() == 0) {
                    delete RefCounter;
                }
            }
        }
    }
};


template <typename U>
void MySwap(U& first_, U& second_) noexcept {
    U tmp = std::move(first_);
    first_ = std::move(second_);
    second_ = std::move(tmp);
}




