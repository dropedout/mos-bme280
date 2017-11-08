#ifndef MGOS_MOCK_H
#define MGOS_MOCK_H

// MOCKING C-Functions with GMOCK :)
#include <memory>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
using namespace ::testing;
using ::testing::Return;

class MgosMock {
public:
    virtual ~MgosMock(){}

    MOCK_METHOD0(mgos_init,bool());
    // mock methods
    MOCK_METHOD0(bcm2835_init,int());
    MOCK_METHOD2(bcm2835_gpio_fsel,void(uint8_t,uint8_t));

};


class TestFixture: public Test{
public:
    TestFixture(){
        _mgos.reset(new ::testing::NiceMock<MgosMock>());
    }
    ~TestFixture(){
        _mgos.reset();
    }
    virtual void SetUp(){}
    virtual void TearDown(){}

    // pointer for accessing mocked library
    static std::unique_ptr<MgosMock> _mgos;
};
#endif // MGOS_MOCK_H

