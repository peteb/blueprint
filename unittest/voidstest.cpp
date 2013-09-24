#include <gtest/gtest.h>

namespace {
    
    // The fixture for testing class Voids.
    class voidstest : public ::testing::Test {
    protected:
        voidstest() {
        }
        
        virtual ~voidstest() {
        }

    };
    
    // TEST(voidstest, voidstest_empty_) {        
    // }

    //--- getNiCount tests
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
