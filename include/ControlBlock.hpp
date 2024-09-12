#pragma once
#include <cstddef>


class ControlBlock {

private:
    size_t shared_counter_;
    size_t weak_counter_;

public:
    ControlBlock(bool is_shared_) : shared_counter_(is_shared_ ? 1 : 0), weak_counter_(is_shared_ ? 0 : 1) {}

    inline constexpr void IncrementShared() noexcept {
        ++shared_counter_;
    }

    inline constexpr void DecrementShared() noexcept {
        --shared_counter_;
    }

    inline constexpr size_t SharedCount() const noexcept {
        return shared_counter_;
    }

    inline constexpr void IncrementWeak() noexcept {
        ++weak_counter_;
    }

    inline constexpr void DecrementWeak() noexcept {
        --weak_counter_;
    }

    inline constexpr size_t WeakCount() const noexcept {
        return weak_counter_;
    }
};
