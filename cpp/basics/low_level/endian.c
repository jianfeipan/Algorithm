#include <stdbool.h>
#include <stdint.h>

/**
 * Returns true if the system is little-endian, false if big-endian.
 * 
 * 
                Memory Address:   Lowest (N)       Highest (N+1)
                                   +------------+   +------------+
  Little-Endian (e.g., x86/ARM):   |    0x01    |   |    0x00    |
                                   +------------+   +------------+
                                     LSB First        MSB Last
                                   (Least Sig.)     (Most Sig.)


                                   Lowest (N)       Highest (N+1)
                                   +------------+   +------------+
     Big-Endian (Network Order):   |    0x00    |   |    0x01    |
                                   +------------+   +------------+
                                     MSB First        LSB Last
                                   (Most Sig.)      (Least Sig.)
 */
bool is_little_endian() {
    uint16_t number = 1;
    uint8_t *byte_ptr = (uint8_t *)&number;
    
    return (*byte_ptr == 1);
}