
#include "fileQueue.h"
#include "gtest/gtest.h"

class fileQueueTest:public ::testing::Test{
public:
    fileQueueTest(){}

    virtual void SetUp(){
        for(int i=0;i<10;++i){
            fq.add(File(i));
        }
    }
    FileQueue fq;
};

TEST_F(fileQueueTest, FileQueue_size){
    ASSERT_EQ(fq.size(), 10);
}

TEST_F(fileQueueTest, FileQueue_add){
    fq.add(File(10));
    ASSERT_EQ(fq.size(), 11);
}

TEST_F(fileQueueTest, FileQueue_front){
    File f = fq.front();
    ASSERT_EQ(f.remainBlockNumber(), 0);
}


TEST_F(fileQueueTest, FileQueue_remove_front){
    File f;
    int counter = 0;
    while(!fq.empty()){
        f = fq.front();
        fq.remove_front();
        ASSERT_EQ(f.remainBlockNumber(), counter);
        ++counter;
        ASSERT_EQ(fq.size(), 10-counter);
    }
}

/*
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
*/
