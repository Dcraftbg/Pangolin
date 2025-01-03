#pragma once
#define DT_UNKNOWN 0
#define DT_DIR 1
#define DT_BLK 2
struct dirent {
    ino_t d_ino;
    unsigned short d_reclen;
    unsigned char d_type;
    char d_name[256];
};
