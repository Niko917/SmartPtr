#pragma once
#include <cstddef>
#include <memory>
#include <stdexcept>
#include <utility>
#include "ControlBlock.hpp"

template <typename T>
class WeakPtr;

template <typename T>
class SharedPtr { 
private:
    T* ptr_;
    ControlBlock* RefCounter;

public:
    constexpr SharedPtr() noexcept : ptr_(nullptr), RefCounter(new ControlBlock(false)) {}
    
    explicit SharedPtr(T* ptr) : ptr_(ptr), RefCounter(new ControlBlock(true)) {}
    
    SharedPtr(T* ptr, ControlBlock* rc) : ptr_(ptr), RefCounter(std::move(rc)) {
        if (RefCounter) {
            RefCounter->IncrementShared();
        }
    }

    SharedPtr(const SharedPtr& other) : ptr_(other.get()), RefCounter(other.RefCounter) {
        if (RefCounter) {
            RefCounter->IncrementShared();
        }
    }

    SharedPtr(SharedPtr&& other) noexcept : ptr_(other.get()), RefCounter(other.RefCounter) {
        other.ptr_ = nullptr;
        other.RefCounter = nullptr;
    }

    ~SharedPtr() {
        release();
    }


    SharedPtr(const WeakPtr<T>& weak) : ptr_(weak.ptr_), RefCounter(weak.RefCounter) {
        if (RefCounter && RefCounter->SharedCount() > 0) {
            RefCounter->IncrementShared();
        }
        else {
            ptr_ = nullptr;
            RefCounter = nullptr;
        }
    }

    SharedPtr& operator=(const SharedPtr& other) {
        if (this != &other) {
            release();
            ptr_ = other.ptr_;
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
            ptr_ = other.ptr_;
            RefCounter = other.RefCounter;
            other.ptr_ = nullptr;
            other.RefCounter = nullptr;
        }
        return *this;
    }

    T* get() const noexcept {
        return ptr_;
    }

    explicit operator bool() const noexcept {
        return this->get() != nullptr;
    }

    size_t use_count() const noexcept {
        return RefCounter ? RefCounter->SharedCount() : 0;
    }

    T& operator*() const {
        if (ptr_ == nullptr) {
            throw std::runtime_error("Dereferencing a nullptr");
        }
        return *ptr_;
    }

    T* operator->() const {
        return ptr_;
    }

    bool unique() const noexcept {
        return use_count() == 1;
    }

    void reset(T* new_ptr = nullptr) {
        if (ptr_ != new_ptr) {

            ptr_ = new_ptr; 
            
            if (new_ptr) {
                RefCounter = new ControlBlock(true);
            }
            else {
                RefCounter = nullptr;
            }
        }
    }


private:
    void release() {
        if (RefCounter) {
            RefCounter->DecrementShared();
            if (RefCounter->SharedCount() == 0) {
                delete ptr_;
                if (RefCounter->WeakCount() == 0) {
                    delete RefCounter;
                }
            }
            ptr_ = nullptr;
            RefCounter = nullptr;
        }
    }


    friend class WeakPtr<T>;
};


