


#include "serverPool.h"
#include "gtest/gtest.h"

class ServerPoolTest:public ::testing::Test{
public:
    ServerPoolTest(){}

    virtual void SetUp(){
        for(int i=0;i<5;++i){
            serv_pool.add(Server(i*service_rate, i*leaving_rate, i));
        }
    }
    ServerPool serv_pool;
    double service_rate = 10;
    double leaving_rate = 20;
};


TEST_F(ServerPoolTest, ServerPoolTest_getServer){
    Server s = serv_pool.getServer();
    ASSERT_EQ(s.is_free, false);
    ASSERT_EQ(s.is_active, true);
    ASSERT_EQ(serv_pool.serverNumber(), 5);
    ASSERT_EQ(serv_pool.freeServerNumber(), 4);
}

TEST_F(ServerPoolTest, ServerPoolTest_free){
    Server s = serv_pool.getServer();
    ASSERT_EQ(serv_pool.serverNumber(), 5);
    ASSERT_EQ(serv_pool.freeServerNumber(), 4);
    serv_pool.free(s.id);
    ASSERT_EQ(serv_pool.serverNumber(), 5);
    ASSERT_EQ(serv_pool.freeServerNumber(), 5);
}

TEST_F(ServerPoolTest, ServerPoolTest_remove){
    Server s = serv_pool.getServer();
    ASSERT_EQ(serv_pool.serverNumber(), 5);
    ASSERT_EQ(serv_pool.freeServerNumber(), 4);

    serv_pool.remove(s.id);
    ASSERT_EQ(serv_pool.serverNumber(), 4);
    ASSERT_EQ(serv_pool.freeServerNumber(), 4);
}


/*
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
*/
