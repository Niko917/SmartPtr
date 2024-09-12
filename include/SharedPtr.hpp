#pragma once
#include <cstddef>
#include <memory>
#include <optional>
#include <utility>
#include "ControlBlock.hpp"


template <typename T, typename Deleter = std::default_delete<T>>
class SharedPtr { 
private:
    T* ptr;
    ControlBlock* RefCounter;

    Deleter deleter;
    
public:
    SharedPtr() noexcept : ptr(nullptr), RefCounter(new ControlBlock(true)), deleter() {}

    explicit SharedPtr(T* ptr) : ptr(ptr), RefCounter(new ControlBlock(true)), deleter() {}

    
    SharedPtr(const SharedPtr& other) : ptr(other.ptr), RefCounter(other.RefCounter), deleter(other.deleter) {
        if (RefCounter) {
            RefCounter->IncrementShared();
        }
    }

    
    SharedPtr(SharedPtr&& other) noexcept : ptr(other.ptr), RefCounter(other.RefCounter), deleter(std::move(other.deleter)) {
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


