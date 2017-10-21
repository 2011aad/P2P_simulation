

#include "server.h"
#include "gtest/gtest.h"

class ServerTest:public ::testing::Test{
public:
    ServerTest(){}

    virtual void SetUp(){
        server = Server(10*100, 10, 0);
    }
    Server server;
};


TEST_F(ServerTest, ServerTest_upload){
    double total_time = 0;
    for(int i=0;i<10000;++i){
        auto time_success_pair = server.upload(0, 0);
        if(time_success_pair.second) total_time += time_success_pair.first;
    }
    total_time /= 10000;
    ASSERT_LT(total_time, 2e-3);
}

/*
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
*/
