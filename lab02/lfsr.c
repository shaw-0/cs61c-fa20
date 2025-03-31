#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "lfsr.h"

void lfsr_calculate(uint16_t *reg) {
    /* YOUR CODE HERE */
    uint16_t origin = *reg;
    uint16_t msb = ((origin ^ (origin >> 2)) ^ (origin >> 3) ^ (origin >> 5)) & 0x01;
    *reg = (origin >> 1) | (msb << 15);
}

