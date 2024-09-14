#include <gtest/gtest.h>
#include "../include/WeakPtr.hpp"
#include "../include/SharedPtr.hpp"


TEST(WeakPtrTest, DefaultConstructor) {
    WeakPtr<int> ptr;
    
    EXPECT_EQ(ptr.expired(), true);
}


TEST(WeakPtrTest, ConstructorFromSharedPtr) {
    int* raw_ptr = new int(42);
    
    SharedPtr<int> shared_ptr(raw_ptr);
    WeakPtr<int> weak_ptr(shared_ptr);
    
    EXPECT_EQ(weak_ptr.expired(), false);
    EXPECT_EQ(weak_ptr.lock().get(), raw_ptr);
}


TEST(WeakPtrTest, CopyConstructor) {
    int* raw_ptr = new int(42);
    SharedPtr<int> shared_ptr(raw_ptr);
    
    WeakPtr<int> weak_ptr1(shared_ptr);
    WeakPtr<int> weak_ptr2(weak_ptr1);
    
    EXPECT_EQ(weak_ptr1.expired(), false);
    EXPECT_EQ(weak_ptr2.expired(), false);
    EXPECT_EQ(weak_ptr1.lock().get(), raw_ptr);
    EXPECT_EQ(weak_ptr2.lock().get(), raw_ptr);
}


TEST(WeakPtrTest, MoveConstructor) {
    int* raw_ptr = new int(42);
    SharedPtr<int> shared_ptr(raw_ptr);
    
    WeakPtr<int> weak_ptr1(shared_ptr);
    WeakPtr<int> weak_ptr2(std::move(weak_ptr1));
    
    EXPECT_EQ(weak_ptr1.expired(), true);
    EXPECT_EQ(weak_ptr2.expired(), false);
    EXPECT_EQ(weak_ptr2.lock().get(), raw_ptr);
}


TEST(WeakPtrTest, CopyAssignmentOperator) {
    int* raw_ptr1 = new int(42);
    int* raw_ptr2 = new int(24);
    
    SharedPtr<int> shared_ptr1(raw_ptr1);
    SharedPtr<int> shared_ptr2(raw_ptr2);
    
    WeakPtr<int> weak_ptr1(shared_ptr1);
    WeakPtr<int> weak_ptr2(shared_ptr2);
    weak_ptr2 = weak_ptr1;
    
    EXPECT_EQ(weak_ptr1.expired(), false);
    EXPECT_EQ(weak_ptr2.expired(), false);
    EXPECT_EQ(weak_ptr1.lock().get(), raw_ptr1);
    EXPECT_EQ(weak_ptr2.lock().get(), raw_ptr1);
}


TEST(WeakPtrTest, MoveAssignmentOperator) {
    int* raw_ptr1 = new int(42);
    int* raw_ptr2 = new int(24);
    
    SharedPtr<int> shared_ptr1(raw_ptr1);
    SharedPtr<int> shared_ptr2(raw_ptr2);
    
    WeakPtr<int> weak_ptr1(shared_ptr1);
    WeakPtr<int> weak_ptr2(shared_ptr2);
    weak_ptr2 = std::move(weak_ptr1);
    
    EXPECT_EQ(weak_ptr1.expired(), true);
    EXPECT_EQ(weak_ptr2.expired(), false);
    EXPECT_EQ(weak_ptr2.lock().get(), raw_ptr1);
}


TEST(WeakPtrTest, ExpiredMethod) {
    int* raw_ptr = new int(42);
    SharedPtr<int> shared_ptr(raw_ptr);
    WeakPtr<int> weak_ptr(shared_ptr);
    
    EXPECT_EQ(weak_ptr.expired(), false);
    
    shared_ptr.reset(nullptr);
    
    EXPECT_EQ(weak_ptr.expired(), true);
}


TEST(WeakPtrTest, LockMethod) {
    int* raw_ptr = new int(42);
    SharedPtr<int> shared_ptr(raw_ptr);
    WeakPtr<int> weak_ptr(shared_ptr);
    SharedPtr<int> locked_ptr = weak_ptr.lock();
    
    EXPECT_EQ(locked_ptr.get(), raw_ptr);
    EXPECT_EQ(locked_ptr.use_count(), 2);
    
    shared_ptr.reset(nullptr);
    locked_ptr = weak_ptr.lock();
    
    EXPECT_EQ(locked_ptr.get(), nullptr);
}
