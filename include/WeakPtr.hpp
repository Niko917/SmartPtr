#pragma once
#include <cstddef>
#include <memory>
#include <utility>
#include "ControlBlock.hpp"
#include "SharedPtr.hpp"

template <typename T>
class WeakPtr {
private:
    T* ptr_;
    ControlBlock* RefCounter;

public:
    WeakPtr() noexcept : ptr_(nullptr), RefCounter(nullptr) {}

    WeakPtr(const SharedPtr<T>& shared) noexcept : ptr_(shared.ptr_), RefCounter(shared.RefCounter) {
        if (RefCounter) {
            RefCounter->IncrementWeak();
        }
    }

    WeakPtr(const WeakPtr& other) noexcept : ptr_(other.ptr_), RefCounter(other.RefCounter) {
        if (RefCounter) {
            RefCounter->IncrementWeak();
        }
    }

    WeakPtr(WeakPtr&& other) noexcept : ptr_(other.ptr_), RefCounter(other.RefCounter) {
        other.ptr_ = nullptr;
        other.RefCounter = nullptr;
    }

    ~WeakPtr() {
        release();
    }

    WeakPtr& operator=(const WeakPtr& other) noexcept {
        if (this != &other) {
            release();
            ptr_ = other.ptr_;
            RefCounter = other.RefCounter;
            if (RefCounter) {
                RefCounter->IncrementWeak();
            }
        }
        return *this;
    }

    WeakPtr& operator=(WeakPtr&& other) noexcept {
        if (this != &other) {
            release();
            ptr_ = other.ptr_;
            RefCounter = other.RefCounter;
            other.ptr_ = nullptr;
            other.RefCounter = nullptr;
        }
        return *this;
    }

    WeakPtr& operator=(const SharedPtr<T>& shared) noexcept {
        release();
        ptr_ = shared.ptr_;
        RefCounter = shared.RefCounter;
        if (RefCounter) {
            RefCounter->IncrementWeak();
        }
        return *this;
    }

    SharedPtr<T> lock() const noexcept {
        if (RefCounter && RefCounter->SharedCount() > 0) {
            return SharedPtr<T>(*this);
        }
        return SharedPtr<T>();
    }

    size_t use_count() const noexcept {
        return RefCounter ? RefCounter->SharedCount() : 0;
    }

    bool expired() const noexcept {
        return use_count() == 0;
    }

    void reset() noexcept {
        release();
    }

private:
    void release() {
        if (RefCounter) {
            RefCounter->DecrementWeak();
            if (RefCounter->SharedCount() == 0 && RefCounter->WeakCount() == 0) {
                delete RefCounter;
            }
            ptr_ = nullptr;
            RefCounter = nullptr;
        }
    }

    friend class SharedPtr<T>;
};
