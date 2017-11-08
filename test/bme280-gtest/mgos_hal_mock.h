#ifndef MGOS_HAL_MOCK_H
#define MGOS_HAL_MOCK_H

#include <memory>
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace ::testing;
using ::testing::Return;

class MgosHalMock {
public:
    virtual ~MgosHalMock(){}
    MOCK_METHOD1(mgos_msleep,void(uint32_t));
    MOCK_METHOD1(mgos_usleep,void(uint32_t));
};

#endif // MGOS_HAL_MOCK_H
