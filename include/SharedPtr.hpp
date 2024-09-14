#pragma once
#include <cstddef>
#include <memory>
#include <optional>
#include <stdexcept>
#include <utility>
#include "ControlBlock.hpp"

template <typename T>
class WeakPtr;

template <typename T, typename Deleter = std::default_delete<T>>
class SharedPtr { 
private:
    T* ptr_;
    ControlBlock* RefCounter;
    Deleter deleter;

public:
    SharedPtr() noexcept : ptr_(nullptr), RefCounter(new ControlBlock(true)), deleter() {}
    explicit SharedPtr(T* ptr) : ptr_(ptr), RefCounter(new ControlBlock(true)), deleter() {}
    SharedPtr(T* ptr, ControlBlock* rc) : ptr_(ptr), RefCounter(std::move(rc)) {
        if (RefCounter) {
            RefCounter->IncrementShared();
        }
    }
    SharedPtr(const SharedPtr& other) : ptr_(other.get()), RefCounter(other.RefCounter), deleter(other.deleter) {
        if (RefCounter) {
            RefCounter->IncrementShared();
        }
    }
    SharedPtr(SharedPtr&& other) noexcept : ptr_(other.get()), RefCounter(other.RefCounter), deleter(std::move(other.deleter)) {
        other.ptr_ = nullptr;
        other.RefCounter = nullptr;
    }
    ~SharedPtr() {
        release();
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
            deleter = std::move(other.deleter);
            other.ptr_ = nullptr;
            other.RefCounter = nullptr;
        }
        return *this;
    }
    T* get() const noexcept {
        return ptr_;
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
    void reset(T* new_ptr) {
        if (ptr_ != new_ptr) {
            release();
            ptr_ = new_ptr;
            
            RefCounter = new ControlBlock(true);
            if (RefCounter) {
                RefCounter->IncrementShared();
            }
        }
    }
    void swap(SharedPtr& other) noexcept {
        std::swap(ptr_, other.ptr_);
        std::swap(RefCounter, other.RefCounter);
        std::swap(deleter, other.deleter);
    }

private:
    void release() {
        if (RefCounter) {
            RefCounter->DecrementShared();
            if (RefCounter->SharedCount() == 0) {
                deleter(ptr_);
                if (RefCounter->WeakCount() == 0) {
                    delete RefCounter;
                }
            }
        }
    }


    friend class WeakPtr<T>;
};


template <typename T>
void swap(SharedPtr<T>& lhs_, SharedPtr<T>& rhs_) noexcept {
    lhs_.swap(rhs_);
}
