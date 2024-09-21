#pragma once
#include <stdexcept>
#include <type_traits>


template <typename T>
class UniquePtr {
private:
    T* ptr_;
    
public:
    UniquePtr(T* ptr_ = nullptr) : ptr_(ptr_) {}

    ~UniquePtr() {
        if (ptr_) {
            delete(ptr_);
        }
    }

    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

    // SFINAE
    template <typename U, typename = std::enable_if_t<std::is_convertible_v<U*, T*>>>
    UniquePtr(UniquePtr<U>&& other_ptr_) noexcept : ptr_(other_ptr_.release()) {
        other_ptr_.ptr_ = nullptr;
    }

    UniquePtr& operator=(UniquePtr&& other_ptr_) noexcept {
        if (this != &other_ptr_) {
            reset(other_ptr_.release());
        }
        return *this;
    }

    T& operator*() const { 
        if (this == nullptr) {
            throw std::runtime_error("Dereferencing a nullptr");
        }
        return *ptr_; 
    }
    
    T* operator->() const noexcept { return ptr_; }
    
    T* get() const { return ptr_; }

    T* release() noexcept {
        T* tmp = ptr_;
        ptr_ = nullptr;
        return tmp;
    }

    void reset(T* new_ptr_ = nullptr) noexcept {
        if (ptr_) {
            delete(ptr_);
        }
        ptr_ = new_ptr_;
    }

    bool operator==(const UniquePtr& other) const noexcept {
        return ptr_ == other.ptr_;
    }

    bool operator!=(const UniquePtr& other) const noexcept {
        return ptr_ != other.ptr_;
    }

    // Friend declaration to allow access to private members
    template <typename U>
    friend class UniquePtr;
};

// Implementation of make_unique for types with constructor parameters
template <typename T, typename... Args>
UniquePtr<T> make_unique(Args&&... args) {
    return UniquePtr<T>(new T(std::forward<Args>(args)...));
}

// Implementation of make_unique for arrays
template <typename T>
UniquePtr<T[]> make_unique_array(std::size_t size) {
    return UniquePtr<T[]>(new T[size]());
}
