#include <gtest/gtest.h>
#include "../include/SharedPtr.hpp"

class TestClass {
public:
    static int counter;
    TestClass() { counter++; }
    ~TestClass() { counter--; }
};

int TestClass::counter = 0;


TEST(SharedPtrTest, DefaultConstructor) {
    SharedPtr<int> ptr;
    EXPECT_EQ(ptr.get(), nullptr);
    EXPECT_EQ(ptr.use_count(), 0);
}


TEST(SharedPtrTest, PointerConstructor) {
    int* raw_ptr = new int(42);
    SharedPtr<int> ptr(raw_ptr);
    EXPECT_EQ(ptr.get(), raw_ptr);
    EXPECT_EQ(ptr.use_count(), 1);
}


TEST(SharedPtrTest, CopyConstructor) {
    SharedPtr<int> ptr1(new int(42));
    SharedPtr<int> ptr2(ptr1);
    EXPECT_EQ(ptr1.get(), ptr2.get());
    EXPECT_EQ(ptr1.use_count(), 2);
    EXPECT_EQ(ptr2.use_count(), 2);
}


TEST(SharedPtrTest, MoveConstructor) {
    SharedPtr<int> ptr1(new int(42));
    SharedPtr<int> ptr2(std::move(ptr1));
    
    EXPECT_EQ(ptr1.get(), nullptr);
    EXPECT_EQ(ptr2.get(), ptr1.get());
    EXPECT_EQ(ptr2.use_count(), 1);
}


TEST(SharedPtrTest, CopyAssignmentOperator) {
    SharedPtr<int> ptr1(new int(42));
    SharedPtr<int> ptr2;
    ptr2 = ptr1;
    
    EXPECT_EQ(ptr1.get(), ptr2.get());
    EXPECT_EQ(ptr1.use_count(), 2);
    EXPECT_EQ(ptr2.use_count(), 2);
}


TEST(SharedPtrTest, MoveAssignmentOperator) {
    SharedPtr<int> ptr1(new int(42));
    SharedPtr<int> ptr2;
    ptr2 = std::move(ptr1);
    
    EXPECT_EQ(ptr1.get(), nullptr);
    EXPECT_EQ(ptr2.get(), ptr1.get());
    EXPECT_EQ(ptr2.use_count(), 1);
}


/*TEST(SharedPtrTest, DereferenceOperator) {*/
/*    SharedPtr<int> ptr(new int(42));*/
/*    auto it = *ptr.value();
}*/


TEST(SharedPtrTest, GetMethod) {
    int* raw_ptr = new int(42);
    SharedPtr<int> ptr(raw_ptr);
    
    EXPECT_EQ(ptr.get(), raw_ptr);
}


TEST(SharedPtrTest, UseCountMethod) {
    SharedPtr<int> ptr1(new int(42));
    SharedPtr<int> ptr2(ptr1);
    
    EXPECT_EQ(ptr1.use_count(), 2);
    EXPECT_EQ(ptr2.use_count(), 2);
}


TEST(SharedPtrTest, ArrowOperator) {
    struct TestStruct { int value = 42; };
    SharedPtr<TestStruct> ptr(new TestStruct());
    
    EXPECT_EQ(ptr->value, 42);
}


TEST(SharedPtrTest, UniqueMethod) {
    SharedPtr<int> ptr1(new int(42));
    EXPECT_TRUE(ptr1.unique());
    SharedPtr<int> ptr2(ptr1);
    
    EXPECT_FALSE(ptr1.unique());
    EXPECT_FALSE(ptr2.unique());
}


/*TEST(SharedPtrTest, ResetMethod) {*/
/*    SharedPtr<int> ptr(new int(42));*/
/*    ptr.reset(new int(10));*/
/**/
/*    EXPECT_EQ(*ptr, 10);*/
/*    EXPECT_EQ(ptr.use_count(), 1);*/
/*}*/
/**/



/*TEST(SharedPtrTest, SwapMethod) {*/
/*    SharedPtr<int> ptr1(new int(42));*/
/*    SharedPtr<int> ptr2(new int(10));*/
/*    ptr1.swap(ptr2);*/
/**/
/*    EXPECT_EQ(*ptr1, 10);*/
/*    EXPECT_EQ(*ptr2, 42);*/
/*}*/
/**/


TEST(SharedPtrTest, Destructor) {
    {
        SharedPtr<TestClass> ptr(new TestClass());
        EXPECT_EQ(TestClass::counter, 1);
    }
    EXPECT_EQ(TestClass::counter, 0);
}



int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
