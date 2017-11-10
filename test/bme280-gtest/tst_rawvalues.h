#ifndef TST_RAWVALUES_H
#define TST_RAWVALUES_H

#include "bm280_types.h"

#include <gtest/gtest.h>

TEST(RawValues,testRegRawValue) {
    sRegRawValue dut;
    uint8_t buffer[8] = {0};
    dut = buffer;
    EXPECT_EQ(dut.get(),0);

    buffer[0] = 0x80;
    dut = buffer;
    EXPECT_EQ(dut.get(),0x80000);

    buffer[0] = 0xab;buffer[1] = 0xcd;buffer[2] = 0xef;
    dut = buffer;
    EXPECT_EQ(dut.get(),0xabcde);
}

#endif // TST_RAWVALUES_H
