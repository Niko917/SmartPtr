#pragma once
#include <concepts>
#include <iostream>
#include "ControlBlock.hpp"
#include "SharedPtr.hpp"

template <typename T, typename Deleter>
class SharedPtr;

template <typename T>
class WeakPtr {
private:
    T* ptr;
    ControlBlock* RefCounter;

public:
    WeakPtr() : ptr(nullptr), RefCounter(new ControlBlock(false)) {}
    WeakPtr(const SharedPtr<T>& shared) : ptr(shared.ptr_), RefCounter(shared.RefCounter) {
        if (RefCounter) {
            RefCounter->IncrementWeak();
        }
    }
    WeakPtr(const WeakPtr<T>& other_weak) : ptr(other_weak.ptr), RefCounter(other_weak.RefCounter) {
        if (RefCounter) {
            RefCounter->IncrementWeak();
        }
    }
    WeakPtr(WeakPtr&& other_weak) noexcept : ptr(other_weak.ptr), RefCounter(other_weak.RefCounter) {
        other_weak.ptr = nullptr;
        other_weak.RefCounter = nullptr;
    }
    ~WeakPtr() {
        release();
    }
    WeakPtr& operator=(WeakPtr&& other) noexcept {
        if (this != &other) {
            release();
            ptr = other.ptr;
            RefCounter = other.RefCounter;
            other.ptr = nullptr;
            other.RefCounter = nullptr;
        }
        return *this;
    }
    WeakPtr& operator=(const WeakPtr& other) {
        if (this != &other) {
            release();
            ptr = other.ptr;
            RefCounter = other.RefCounter;
            if (RefCounter) {
                RefCounter->IncrementWeak();
            }
        }
        return *this;
    }
    inline bool expired() const noexcept {
        return RefCounter == nullptr || RefCounter->SharedCount() == 0;
    }
    SharedPtr<T> lock() const {
        if (expired()) {
            return SharedPtr<T>();
        }
        return SharedPtr<T>(ptr, RefCounter);
    }

private:
    void release() {
        if (RefCounter) {
            RefCounter->DecrementWeak();
            if (RefCounter->SharedCount() == 0 && RefCounter->WeakCount() == 0) {
                delete RefCounter;
            }
        }
    }

    friend class SharedPtr<T>;
};
