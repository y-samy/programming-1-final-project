#include "libparse.h"


size_t file_entry_count(FILE *file_p)
{
    size_t count = 0;
    int c, prev_c = 0;
    while (1) {
        c = fgetc(file_p);
        if (c == EOF) {
            if (prev_c != '\n')
                count++;
            break;
        }
        if (c == '\n' && prev_c != '\n')
            count++;
        prev_c = c;
    }
    return count;
}