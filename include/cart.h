#pragma once

#include <common.h>

#define ENTRY_SIZE      4
#define LOGO_SIZE       48
#define TITLE_SIZE      16
#define FILENAME_SIZE   1024
#define HEADER_OFFSET   0x100

struct rom_header{
    u8 entry[ENTRY_SIZE];
    u8 logo[LOGO_SIZE];
    char title[TITLE_SIZE];
    u16 new_lic_code;
    u8 sgb_flag;
    u8 type;
    u8 rom_size;
    u8 ram_size;
    u8 dest_code;
    u8 lic_code;
    u8 version;
    u8 checksum;
    u16 global_checksum;
};

struct cart_context {
    char filename [FILENAME_SIZE];
    u32 rom_size;
    u8 *rom_data;
    struct rom_header *header;
};

int cart_load(char *cart, struct cart_context* cart_ctx);