#include "gtest/gtest.h"
#include "fixtures.h"

class AlmacenTest : public ::testing::Test{
public:
    static Almacen* ptr;
    void SetUp(){
        ptr->pushBack(1);
    }
    void TearDown(){
    }
    static void SetUpTestCase(){
       ptr =  new Almacen(10);
    }
    static void TearDownTestCase(){
        delete ptr;
    }

};

Almacen* AlmacenTest::ptr = nullptr;

TEST_F(AlmacenTest, Constructor){
    ASSERT_EQ(24, sizeof(*ptr));
}

TEST_F(AlmacenTest, Add){
    ptr->pushBack(1);
    ASSERT_EQ(3, ptr->getSize());
}


TEST_F(AlmacenTest, erase){
    ptr->pushBack(1);
    ptr->deleteAt(0);
    ASSERT_EQ(4, ptr->getSize());
}
