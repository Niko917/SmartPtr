#pragma once
#include <iostream>
#include <memory>
#include <type_traits>
#include <concepts>

template <typename T, typename Deleter = std::default_delete<T>>
class UniquePtr {
private:
    T* ptr;
    Deleter del; // functional object
    
public:
    UniquePtr(T* ptr = nullptr) : ptr(ptr) {}

    UniquePtr(T* ptr, Deleter del) : ptr(ptr), del(std::move(del)) {}

    ~UniquePtr() {
        if (ptr) {
            del(ptr);
        }
    }

    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

    template <typename U, typename = std::enable_if_t<std::is_convertible_v<U*, T*>>>
    UniquePtr(UniquePtr<U, Deleter>&& other_ptr) noexcept : ptr(other_ptr.release()), del(std::move(other_ptr.del)) {}

    UniquePtr& operator=(UniquePtr&& other_ptr) noexcept {
        if (this != &other_ptr) {
            reset(other_ptr.release());
            del = std::move(other_ptr.del);
        }
        return *this;
    }

    T& operator*() const { return *ptr; }
    
    T* operator->() const noexcept { return ptr; }
    
    T* get() const { return ptr; }

    T* release() noexcept {
        T* tmp = ptr;
        ptr = nullptr;
        return tmp;
    }

    void reset(T* new_ptr = nullptr) noexcept {
        if (ptr) {
            del(ptr);
        }
        ptr = new_ptr;
    }

    bool operator==(const UniquePtr& other) const noexcept {
        return ptr == other.ptr;
    }

    bool operator!=(const UniquePtr& other) const noexcept {
        return ptr != other.ptr;
    }

    bool operator==(std::nullptr_t) const noexcept {
        return ptr == nullptr;
    }

    bool operator!=(std::nullptr_t) const noexcept {
        return ptr != nullptr;
    }

    // Friend declaration to allow access to private members
    template <typename U, typename D>
    friend class UniquePtr;
};

// Implementation of make_unique for simple types
template <typename T, typename Deleter = std::default_delete<T>>
UniquePtr<T, Deleter> make_unique(Deleter del = Deleter()) {
    return UniquePtr<T, Deleter>(new T(), std::move(del));
}

// Implementation of make_unique for types with constructor parameters
template <typename T, typename Deleter = std::default_delete<T>, typename... Args>
UniquePtr<T, Deleter> make_unique(Deleter del, Args&&... args) {
    return UniquePtr<T, Deleter>(new T(std::forward<Args>(args)...), std::move(del));
}

// Implementation of make_unique for arrays
template <typename T, typename Deleter = std::default_delete<T[]>>
UniquePtr<T[], Deleter> make_unique_array(std::size_t size, Deleter del = Deleter()) {
    return UniquePtr<T[], Deleter>(new T[size](), std::move(del));
}

