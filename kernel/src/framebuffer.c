#include <font.h>
#include <stdint.h>
#include <framebuffer.h>
#include <kprint.h>
#include <bootutils.h>
#include <kernel.h>

void draw_pixel(uint64_t x, uint64_t y, uint32_t colour) {
    uint32_t *location = (uint32_t*)(((uint8_t*) kernel.framebuffer.addr) + y * kernel.framebuffer.pitch);
    location[x] = colour;
}

void fill_square(uint64_t x, uint64_t y, uint64_t width, uint64_t height, uint32_t colour) {
    unsigned char *where = (unsigned char*)(((uint8_t*) kernel.framebuffer.addr) + y * kernel.framebuffer.pitch) + x;
    uint8_t r = (colour >> 16) & 0xFF;
    uint8_t g = (colour >> 8 ) & 0xFF;
    uint8_t b = (colour      ) & 0xFF;
    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            where[j*kernel.framebuffer.bytes_per_pix] = r;
            where[j*kernel.framebuffer.bytes_per_pix + 1] = g;
            where[j*kernel.framebuffer.bytes_per_pix + 2] = b;
        }
        where += kernel.framebuffer.pitch;
    }

}

void draw_char(char ch, uint64_t x_coord, uint64_t y_coord, uint32_t colour) {
    uint64_t first_byte_idx = ch * 16;
    for (size_t y = 0; y < 16; y++) {
        for (size_t x = 0; x < 8; x++) {
            if ((font[first_byte_idx + y] >> (7 - x)) & 1)
                draw_pixel(x_coord + x, y_coord + y, colour);
            else
                draw_pixel(x_coord + x, y_coord + y, 0);
        }
    }
}

void init_framebuffer() {
    kernel.framebuffer = boot_get_framebuffer();
    draw_char('a', 5, 5, 0xFFFFFF);
}
