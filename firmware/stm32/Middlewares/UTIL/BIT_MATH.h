#ifndef BIT_MATH_H
#define BIT_MATH_H

#define SET_BIT(REG, BIT_NUM) REG |= (1 << BIT_NUM)
#define CLEAR_BIT(REG, BIT_NUM) REG &= (~(1 << BIT_NUM))
#define TOGGLE_BIT(REG, BIT_NUM) REG ^= (1 << BIT_NUM)
//#define READ_BIT(REG, BIT_NUM) (REG & (1 << BIT_NUM)) // if the bit was 0 the whole returned number will be zero ,but if it was 1 the returned number will be a positive number.
#define READ_BIT(REG, BIT_NUM) (((REG & (1 << BIT_NUM)) == 0) ? 0 : 1) // this will return only 0 or 1.

#endif