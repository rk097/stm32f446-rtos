#include <stdint.h>

// utility
void int_to_str(int32_t value, char *buf) {
    char tmp[11];
    int i = 0;
    int j = 0;
    uint32_t magnitude;

    if (value < 0) {
        buf[j++] = '-';

        // Avoid overflow for INT32_MIN
        magnitude = (uint32_t)(-(value + 1)) + 1;
    } else {
        magnitude = (uint32_t)value;
    }

    if (magnitude == 0) {
        buf[j++] = '0';
        buf[j] = '\0';
        return;
    }

    while (magnitude > 0) {
        tmp[i++] = '0' + (magnitude % 10);
        magnitude /= 10;
    }

    while (i > 0) {
        buf[j++] = tmp[--i];
    }

    buf[j] = '\0';
}