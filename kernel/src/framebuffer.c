#include <string.h>
#include <font.h>
#include <stdint.h>
#include <framebuffer.h>
#include <kprint.h>
#include <bootutils.h>
#include <kernel.h>

#define BG_COLOUR 0x22262e
#define FG_COLOUR 0xd7dae0

void draw_pixel(uint64_t x, uint64_t y, uint32_t colour) {
    uint32_t *location = (uint32_t*)(((uint8_t*) kernel.framebuffer.addr) + y * kernel.framebuffer.pitch);
    location[x] = colour;
}

void fill_rect(uint64_t x, uint64_t y, uint64_t width, uint64_t height, uint32_t colour) {
    unsigned char *where = (unsigned char*)(((uint8_t*) kernel.framebuffer.addr) + y * kernel.framebuffer.pitch) + x;
    uint8_t r = (colour >> 16) & 0xFF;
    uint8_t g = (colour >> 8 ) & 0xFF;
    uint8_t b = (colour      ) & 0xFF;
    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            where[j*kernel.framebuffer.bytes_per_pix] = b;
            where[j*kernel.framebuffer.bytes_per_pix + 1] = g;
            where[j*kernel.framebuffer.bytes_per_pix + 2] = r;
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
                draw_pixel(x_coord + x, y_coord + y, BG_COLOUR);
        }
    }
}

void scroll_pixels(size_t num_pix) {
    size_t max_height = kernel.framebuffer.height - num_pix;
    size_t fb_width_bytes = kernel.framebuffer.width * kernel.framebuffer.bytes_per_pix;
    uintptr_t new_row_loc = (uintptr_t) kernel.framebuffer.addr;
    for (size_t y = 0; y < max_height; y++) {
        uint32_t *old_row_loc = (uint32_t*)(((uint8_t*) kernel.framebuffer.addr) + (y + num_pix) * kernel.framebuffer.pitch);
        memcpy((uint32_t*) new_row_loc, old_row_loc, fb_width_bytes);
        new_row_loc += kernel.framebuffer.pitch;
    }
    fill_rect(0, max_height, kernel.framebuffer.width, num_pix, BG_COLOUR);
}

void scroll_line() {
    kernel.char_y -= 16;
    scroll_pixels(16);
}

void newline() {
    kernel.char_x = 0;
    kernel.char_y += 16;
    if (kernel.char_y >= kernel.framebuffer.height - 16) scroll_line();
}

void write_framebuffer_char(char ch) {
    if (!kernel.framebuffer.is_valid) return;
    if (kernel.char_y >= kernel.framebuffer.height) {
        kernel.char_x = 0;
        kernel.char_y = 0;
    }
    if (ch == '\n') {
        newline();
        return;
    }
    draw_char(ch, kernel.char_x, kernel.char_y, FG_COLOUR);
    kernel.char_x += 8;
    if (kernel.char_x >= kernel.framebuffer.width) newline();
}

void write_framebuffer_text(const char *msg) {
    while (*msg) {
        write_framebuffer_char(*msg);
        msg++;
    }
}

void init_framebuffer() {
    kernel.framebuffer = boot_get_framebuffer();
    fill_rect(0, 0, kernel.framebuffer.width, kernel.framebuffer.height, BG_COLOUR);
    write_framebuffer_text("Framebuffer initialised.\n");
}
