/* Zap light 16 font as a 8x16 bitmap array */

unsigned char font[] = {
	0x00,0x00,0x00,0x3e,0x63,0x5d,0x7d,0x7b,0x77,0x77,0x7f,0x77,0x3e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7e,0x24,0x24,0x24,0x24,0x24,0x24,0x22,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x02,0x7f,0x04,0x08,
	0x10,0x7f,0x20,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x10,0x20,0x40,0x20,0x10,0x08,0x00,0x7c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x08,0x04,0x02,0x04,0x08,0x10,0x00,0x3e,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x38,0x7c,0xfe,0x7c,0x38,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x30,0x10,0x11,0x12,0x04,0x08,0x12,0x26,
	0x4a,0x0f,0x02,0x02,0x00,0x00,0x00,0x10,0x30,0x10,0x11,0x12,0x04,0x08,0x10,0x26,0x49,0x02,0x04,0x0f,0x00,0x00,0x00,0x70,0x08,0x30,0x09,0x72,0x04,0x08,0x12,0x26,0x4a,0x0f,0x02,0x02,0x00,0x00,0x00,0x08,0x08,
	0x08,0x08,0x08,0x00,0x00,0x08,0x08,0x08,0x08,0x08,0x00,0x00,0x00,0x24,0x24,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x08,0x08,0x30,0x00,0x00,0x07,0x08,0x08,0x08,0x3e,0x08,0x08,0x08,0x08,0x08,0x08,0x70,0x00,0x00,0x00,0x00,0x00,0x08,0x08,0x3e,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x08,0x3e,
	0x08,0x08,0x08,0x08,0x3e,0x08,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x42,0xa4,0xa4,0x48,0x10,0x10,0x2a,0x55,0x55,0x8a,0x00,0x00,0x00,0x00,0x00,0x00,0xf1,0x5b,0x55,0x51,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x49,0x49,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x10,0x20,0x10,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x08,
	0x04,0x08,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x24,0x24,0x24,0x12,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x24,0x24,0x24,0x48,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x24,0x24,0x24,0x48,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x24,0x24,0x24,0x12,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x10,0x10,0x10,0x08,0x00,0x42,0x3c,0x00,0x3c,0x42,0x42,0x40,0x40,0x4e,0x42,0x42,0x42,0x3c,0x00,0x00,0x00,0x00,0x42,0x3c,0x00,0x00,0x3a,0x46,0x42,0x42,0x42,0x46,0x3a,0x02,0x02,0x42,0x3c,0x08,0x08,0x00,
	0x3e,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x3e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x08,0x08,0x08,0x08,0x08,0x08,0x3e,0x00,0x00,0x00,0x00,0x00,0x00,0x3c,0x42,0x42,0x40,0x30,0x0c,0x02,0x42,0x42,
	0x3c,0x08,0x08,0x30,0x00,0x00,0x00,0x00,0x00,0x3c,0x42,0x40,0x30,0x0c,0x02,0x42,0x3c,0x08,0x08,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x08,
	0x08,0x08,0x08,0x08,0x08,0x00,0x08,0x08,0x00,0x00,0x00,0x00,0x24,0x24,0x24,0x24,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x24,0x24,0x24,0x7e,0x24,0x24,0x7e,0x24,0x24,0x24,0x00,
	0x00,0x00,0x00,0x00,0x08,0x08,0x3e,0x49,0x48,0x48,0x3e,0x09,0x09,0x49,0x3e,0x08,0x08,0x00,0x00,0x00,0x00,0x31,0x4a,0x4a,0x34,0x08,0x08,0x16,0x29,0x29,0x46,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x24,0x24,0x24,
	0x18,0x28,0x45,0x42,0x46,0x39,0x00,0x00,0x00,0x00,0x08,0x08,0x08,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x08,0x08,0x10,0x10,0x10,0x10,0x10,0x10,0x08,0x08,0x04,0x00,0x00,
	0x00,0x00,0x20,0x10,0x10,0x08,0x08,0x08,0x08,0x08,0x08,0x10,0x10,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x49,0x2a,0x1c,0x2a,0x49,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x08,0x08,0x7f,
	0x08,0x08,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x08,0x08,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x02,0x04,0x04,0x08,0x08,0x10,0x10,0x20,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x3c,0x42,0x42,0x42,0x4a,0x52,0x42,0x42,
	0x42,0x3c,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x18,0x28,0x08,0x08,0x08,0x08,0x08,0x08,0x3e,0x00,0x00,0x00,0x00,0x00,0x00,0x3c,0x42,0x42,0x02,0x04,0x08,0x10,0x20,0x40,0x7e,0x00,0x00,0x00,0x00,0x00,0x00,0x3c,
	0x42,0x42,0x02,0x1c,0x02,0x02,0x42,0x42,0x3c,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x0c,0x14,0x24,0x44,0x44,0x7e,0x04,0x04,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x7e,0x40,0x40,0x40,0x7c,0x02,0x02,0x02,0x42,0x3c,
	0x00,0x00,0x00,0x00,0x00,0x00,0x1c,0x20,0x40,0x40,0x7c,0x42,0x42,0x42,0x42,0x3c,0x00,0x00,0x00,0x00,0x00,0x00,0x7e,0x02,0x02,0x04,0x04,0x08,0x08,0x10,0x10,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x3c,0x42,0x42,
	0x42,0x3c,0x42,0x42,0x42,0x42,0x3c,0x00,0x00,0x00,0x00,0x00,0x00,0x3c,0x42,0x42,0x42,0x42,0x3e,0x02,0x02,0x04,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x08,0x00,0x00,0x00,0x08,0x08,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x08,0x00,0x00,0x00,0x08,0x08,0x08,0x10,0x00,0x00,0x00,0x00,0x00,0x04,0x08,0x10,0x20,0x40,0x20,0x10,0x08,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7e,0x00,
	0x00,0x00,0x7e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x10,0x08,0x04,0x02,0x04,0x08,0x10,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x3c,0x42,0x42,0x02,0x04,0x08,0x08,0x00,0x08,0x08,0x00,0x00,0x00,0x00,
	0x00,0x00,0x1c,0x22,0x4a,0x56,0x52,0x52,0x52,0x4e,0x20,0x1e,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x24,0x24,0x42,0x42,0x7e,0x42,0x42,0x42,0x42,0x00,0x00,0x00,0x00,0x00,0x00,0x7c,0x42,0x42,0x42,0x7c,0x42,0x42,
	0x42,0x42,0x7c,0x00,0x00,0x00,0x00,0x00,0x00,0x3c,0x42,0x42,0x40,0x40,0x40,0x40,0x42,0x42,0x3c,0x00,0x00,0x00,0x00,0x00,0x00,0x78,0x44,0x42,0x42,0x42,0x42,0x42,0x42,0x44,0x78,0x00,0x00,0x00,0x00,0x00,0x00,
	0x7e,0x40,0x40,0x40,0x7c,0x40,0x40,0x40,0x40,0x7e,0x00,0x00,0x00,0x00,0x00,0x00,0x7e,0x40,0x40,0x40,0x7c,0x40,0x40,0x40,0x40,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x3c,0x42,0x42,0x40,0x40,0x4e,0x42,0x42,0x42,
	0x3c,0x00,0x00,0x00,0x00,0x00,0x00,0x42,0x42,0x42,0x42,0x7e,0x42,0x42,0x42,0x42,0x42,0x00,0x00,0x00,0x00,0x00,0x00,0x3e,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x3e,0x00,0x00,0x00,0x00,0x00,0x00,0x1f,0x04,
	0x04,0x04,0x04,0x04,0x04,0x44,0x44,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x42,0x44,0x48,0x50,0x60,0x60,0x50,0x48,0x44,0x42,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x7e,0x00,
	0x00,0x00,0x00,0x00,0x00,0x41,0x63,0x63,0x55,0x55,0x49,0x49,0x41,0x41,0x41,0x00,0x00,0x00,0x00,0x00,0x00,0x42,0x62,0x62,0x52,0x52,0x4a,0x4a,0x46,0x46,0x42,0x00,0x00,0x00,0x00,0x00,0x00,0x3c,0x42,0x42,0x42,
	0x42,0x42,0x42,0x42,0x42,0x3c,0x00,0x00,0x00,0x00,0x00,0x00,0x7c,0x42,0x42,0x42,0x42,0x7c,0x40,0x40,0x40,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x3c,0x42,0x42,0x42,0x42,0x42,0x42,0x5a,0x66,0x3c,0x03,0x00,0x00,
	0x00,0x00,0x00,0x7c,0x42,0x42,0x42,0x7c,0x48,0x44,0x44,0x42,0x42,0x00,0x00,0x00,0x00,0x00,0x00,0x3c,0x42,0x42,0x40,0x30,0x0c,0x02,0x42,0x42,0x3c,0x00,0x00,0x00,0x00,0x00,0x00,0x7f,0x08,0x08,0x08,0x08,0x08,
	0x08,0x08,0x08,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x3c,0x00,0x00,0x00,0x00,0x00,0x00,0x41,0x41,0x41,0x22,0x22,0x22,0x14,0x14,0x08,0x08,0x00,0x00,0x00,0x00,0x00,
	0x00,0x41,0x41,0x41,0x49,0x49,0x55,0x55,0x63,0x63,0x41,0x00,0x00,0x00,0x00,0x00,0x00,0x42,0x42,0x24,0x24,0x18,0x18,0x24,0x24,0x42,0x42,0x00,0x00,0x00,0x00,0x00,0x00,0x41,0x41,0x22,0x22,0x14,0x08,0x08,0x08,
	0x08,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x7e,0x02,0x02,0x04,0x08,0x10,0x20,0x40,0x40,0x7e,0x00,0x00,0x00,0x00,0x00,0x1c,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x1c,0x00,0x00,0x00,0x00,0x00,0x20,
	0x20,0x10,0x10,0x08,0x08,0x04,0x04,0x02,0x02,0x00,0x00,0x00,0x00,0x00,0x38,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x38,0x00,0x00,0x00,0x08,0x14,0x22,0x41,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7f,0x00,0x00,0x00,0x10,0x10,0x10,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3c,
	0x42,0x02,0x3e,0x42,0x42,0x46,0x3a,0x00,0x00,0x00,0x00,0x00,0x40,0x40,0x40,0x5c,0x62,0x42,0x42,0x42,0x42,0x62,0x5c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3c,0x42,0x40,0x40,0x40,0x40,0x42,0x3c,0x00,0x00,
	0x00,0x00,0x00,0x02,0x02,0x02,0x3a,0x46,0x42,0x42,0x42,0x42,0x46,0x3a,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3c,0x42,0x42,0x7e,0x40,0x40,0x42,0x3c,0x00,0x00,0x00,0x00,0x00,0x0e,0x10,0x10,0x10,0x7c,0x10,
	0x10,0x10,0x10,0x10,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3a,0x46,0x42,0x42,0x42,0x46,0x3a,0x02,0x02,0x42,0x3c,0x00,0x00,0x40,0x40,0x40,0x5c,0x62,0x42,0x42,0x42,0x42,0x42,0x42,0x00,0x00,0x00,0x00,
	0x00,0x08,0x08,0x00,0x18,0x08,0x08,0x08,0x08,0x08,0x08,0x3e,0x00,0x00,0x00,0x00,0x00,0x04,0x04,0x00,0x0c,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x44,0x38,0x00,0x00,0x40,0x40,0x40,0x44,0x48,0x50,0x60,0x50,
	0x48,0x44,0x42,0x00,0x00,0x00,0x00,0x00,0x18,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x3e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x76,0x49,0x49,0x49,0x49,0x49,0x49,0x49,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x5c,0x62,0x42,0x42,0x42,0x42,0x42,0x42,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3c,0x42,0x42,0x42,0x42,0x42,0x42,0x3c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x5c,0x62,0x42,0x42,0x42,0x42,0x62,
	0x5c,0x40,0x40,0x40,0x00,0x00,0x00,0x00,0x00,0x3a,0x46,0x42,0x42,0x42,0x42,0x46,0x3a,0x02,0x02,0x02,0x00,0x00,0x00,0x00,0x00,0x5c,0x62,0x40,0x40,0x40,0x40,0x40,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x3c,0x42,0x40,0x30,0x0c,0x02,0x42,0x3c,0x00,0x00,0x00,0x00,0x00,0x10,0x10,0x10,0x10,0x7c,0x10,0x10,0x10,0x10,0x10,0x0e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x42,0x42,0x42,0x42,0x42,0x42,0x46,0x3a,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x41,0x41,0x41,0x22,0x22,0x14,0x14,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x41,0x41,0x49,0x49,0x49,0x49,0x49,0x36,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x42,0x42,
	0x24,0x18,0x18,0x24,0x42,0x42,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x42,0x42,0x42,0x42,0x42,0x46,0x3a,0x02,0x02,0x42,0x3c,0x00,0x00,0x00,0x00,0x00,0x7e,0x02,0x04,0x08,0x10,0x20,0x40,0x7e,0x00,0x00,0x00,
	0x00,0x00,0x06,0x08,0x08,0x08,0x08,0x30,0x08,0x08,0x08,0x08,0x08,0x06,0x00,0x00,0x00,0x00,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x00,0x00,0x00,0x00,0x30,0x08,0x08,0x08,0x08,0x06,0x08,
	0x08,0x08,0x08,0x08,0x30,0x00,0x00,0x00,0x31,0x49,0x46,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x3c,0x3c,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x0c,
	0x00,0x18,0x24,0x24,0x42,0x42,0x7e,0x42,0x42,0x42,0x42,0x00,0x00,0x00,0x0c,0x30,0x00,0x18,0x24,0x24,0x42,0x42,0x7e,0x42,0x42,0x42,0x42,0x00,0x00,0x00,0x18,0x24,0x00,0x18,0x24,0x24,0x42,0x42,0x7e,0x42,0x42,
	0x42,0x42,0x00,0x00,0x00,0x32,0x4c,0x00,0x18,0x24,0x24,0x42,0x42,0x7e,0x42,0x42,0x42,0x42,0x00,0x00,0x00,0x24,0x24,0x00,0x18,0x24,0x24,0x42,0x42,0x7e,0x42,0x42,0x42,0x42,0x00,0x00,0x00,0x18,0x24,0x24,0x18,
	0x24,0x24,0x42,0x42,0x7e,0x42,0x42,0x42,0x42,0x00,0x00,0x00,0x00,0x00,0x00,0x1f,0x28,0x48,0x48,0x7e,0x48,0x48,0x48,0x48,0x4f,0x00,0x00,0x00,0x00,0x00,0x00,0x3c,0x42,0x42,0x40,0x40,0x40,0x40,0x42,0x42,0x3c,
	0x08,0x08,0x30,0x30,0x0c,0x00,0x7e,0x40,0x40,0x40,0x7c,0x40,0x40,0x40,0x40,0x7e,0x00,0x00,0x00,0x0c,0x30,0x00,0x7e,0x40,0x40,0x40,0x7c,0x40,0x40,0x40,0x40,0x7e,0x00,0x00,0x00,0x18,0x24,0x00,0x7e,0x40,0x40,
	0x40,0x7c,0x40,0x40,0x40,0x40,0x7e,0x00,0x00,0x00,0x24,0x24,0x00,0x7e,0x40,0x40,0x40,0x7c,0x40,0x40,0x40,0x40,0x7e,0x00,0x00,0x00,0x30,0x0c,0x00,0x3e,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x3e,0x00,0x00,
	0x00,0x06,0x18,0x00,0x3e,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x3e,0x00,0x00,0x00,0x18,0x24,0x00,0x3e,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x3e,0x00,0x00,0x00,0x22,0x22,0x00,0x3e,0x08,0x08,0x08,0x08,
	0x08,0x08,0x08,0x08,0x3e,0x00,0x00,0x00,0x00,0x00,0x00,0x78,0x44,0x42,0x42,0xf2,0x42,0x42,0x42,0x44,0x78,0x00,0x00,0x00,0x32,0x4c,0x00,0x42,0x62,0x62,0x52,0x52,0x4a,0x4a,0x46,0x46,0x42,0x00,0x00,0x00,0x30,
	0x0c,0x00,0x3c,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x3c,0x00,0x00,0x00,0x0c,0x30,0x00,0x3c,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x3c,0x00,0x00,0x00,0x18,0x24,0x00,0x3c,0x42,0x42,0x42,0x42,0x42,0x42,
	0x42,0x42,0x3c,0x00,0x00,0x00,0x32,0x4c,0x00,0x3c,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x3c,0x00,0x00,0x00,0x24,0x24,0x00,0x3c,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x3c,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x22,0x14,0x08,0x14,0x22,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x3a,0x44,0x46,0x4a,0x4a,0x52,0x52,0x62,0x22,0x5c,0x40,0x00,0x00,0x30,0x0c,0x00,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,
	0x3c,0x00,0x00,0x00,0x0c,0x30,0x00,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x3c,0x00,0x00,0x00,0x18,0x24,0x00,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x3c,0x00,0x00,0x00,0x24,0x24,0x00,0x42,0x42,
	0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x3c,0x00,0x00,0x00,0x06,0x18,0x00,0x41,0x41,0x22,0x22,0x14,0x08,0x08,0x08,0x08,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x40,0x7c,0x42,0x42,0x42,0x42,0x7c,0x40,0x40,0x00,
	0x00,0x00,0x00,0x00,0x00,0x38,0x44,0x4c,0x50,0x50,0x4c,0x42,0x42,0x52,0x4c,0x00,0x00,0x00,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0x00,0x00,0x00,0x08,0x08,0x00,0x08,
	0x08,0x08,0x08,0x08,0x08,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x08,0x3e,0x49,0x48,0x48,0x48,0x48,0x49,0x3e,0x08,0x08,0x00,0x00,0x00,0x00,0x1c,0x20,0x20,0x20,0x78,0x20,0x20,0x20,0x22,0x7e,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x0e,0x11,0x20,0x7e,0x20,0x7c,0x20,0x11,0x0e,0x00,0x00,0x00,0x00,0x00,0x00,0x41,0x41,0x22,0x14,0x08,0x3e,0x08,0x3e,0x08,0x08,0x00,0x00,0x00,0x24,0x18,0x00,0x3c,0x42,0x42,0x40,0x30,0x0c,
	0x02,0x42,0x42,0x3c,0x00,0x00,0x00,0x00,0x00,0x1c,0x22,0x20,0x18,0x24,0x22,0x22,0x12,0x0c,0x02,0x22,0x1c,0x00,0x00,0x00,0x24,0x18,0x00,0x00,0x3c,0x42,0x40,0x30,0x0c,0x02,0x42,0x3c,0x00,0x00,0x00,0x00,0x00,
	0x00,0x3c,0x42,0x99,0xa5,0xa1,0xa1,0xa5,0x99,0x42,0x3c,0x00,0x00,0x00,0x00,0x00,0x38,0x04,0x3c,0x44,0x3c,0x00,0x7c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x12,0x24,0x48,0x24,0x12,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7e,0x02,0x02,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x22,0x1c,0x22,0x22,0x22,0x1c,0x22,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3c,
	0x42,0xb9,0xa5,0xa5,0xb9,0xa9,0xa5,0x42,0x3c,0x00,0x00,0x00,0x00,0x3c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x24,0x24,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x08,0x08,0x7f,0x08,0x08,0x08,0x00,0x7f,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x44,0x04,0x18,0x20,0x40,0x7c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x44,0x04,0x38,
	0x04,0x44,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x24,0x18,0x00,0x7e,0x02,0x02,0x04,0x08,0x10,0x20,0x40,0x40,0x7e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x42,0x42,0x42,0x42,0x42,0x42,0x66,0x5a,0x40,0x40,
	0x40,0x00,0x00,0x00,0x3e,0x7a,0x7a,0x7a,0x7a,0x3a,0x0a,0x0a,0x0a,0x0a,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x24,0x18,0x00,0x00,0x7e,0x02,0x04,
	0x08,0x10,0x20,0x40,0x7e,0x00,0x00,0x00,0x00,0x00,0x10,0x30,0x50,0x10,0x10,0x10,0x7c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x44,0x44,0x44,0x38,0x00,0x7c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x48,0x24,0x12,0x24,0x48,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x37,0x48,0x48,0x48,0x4e,0x48,0x48,0x48,0x48,0x37,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x36,0x49,0x49,0x4f,0x48,
	0x48,0x49,0x36,0x00,0x00,0x00,0x22,0x22,0x00,0x41,0x41,0x22,0x22,0x14,0x08,0x08,0x08,0x08,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x10,0x00,0x10,0x10,0x20,0x40,0x42,0x42,0x3c,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0f,0x08,0x08,0x08,
	0x08,0x08,0x08,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf8,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x0f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x08,0x08,0x08,0x08,
	0x08,0x08,0x08,0xf8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x0f,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0xf8,0x08,0x08,0x08,0x08,0x08,
	0x08,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x08,0x08,0x08,0x08,0x08,0x08,
	0x08,0xff,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x88,0x22,0x88,0x22,0x88,0x22,0x88,0x22,0x88,0x22,0x88,0x22,0x88,0x22,0x88,0x22,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x1f,0x10,0x17,0x14,0x14,0x14,0x14,0x14,0x14,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xfc,0x04,0xf4,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x17,0x10,0x1f,0x00,
	0x00,0x00,0x00,0x00,0x00,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0xf4,0x04,0xfc,0x00,0x00,0x00,0x00,0x00,0x00,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x17,0x10,0x17,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x14,
	0x14,0x14,0x14,0xf4,0x04,0xf4,0x14,0x14,0x14,0x14,0x14,0x14,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0xf7,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0xf7,0x00,0xff,0x00,0x00,0x00,
	0x00,0x00,0x00,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0xf7,0x00,0xf7,0x14,0x14,0x14,0x14,0x14,0x14,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x08,
	0x1c,0x2a,0x08,0x08,0x08,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x08,0x08,0x08,0x2a,0x1c,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x20,0x7f,0x20,0x10,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x04,0xfe,0x04,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x0c,0x00,0x00,0x3c,0x42,0x02,0x3e,0x42,0x42,0x46,0x3a,0x00,0x00,0x00,0x00,0x0c,0x30,0x00,0x00,0x3c,0x42,0x02,
	0x3e,0x42,0x42,0x46,0x3a,0x00,0x00,0x00,0x00,0x18,0x24,0x00,0x00,0x3c,0x42,0x02,0x3e,0x42,0x42,0x46,0x3a,0x00,0x00,0x00,0x00,0x32,0x4c,0x00,0x00,0x3c,0x42,0x02,0x3e,0x42,0x42,0x46,0x3a,0x00,0x00,0x00,0x00,
	0x24,0x24,0x00,0x00,0x3c,0x42,0x02,0x3e,0x42,0x42,0x46,0x3a,0x00,0x00,0x00,0x18,0x24,0x24,0x18,0x00,0x3c,0x42,0x02,0x3e,0x42,0x42,0x46,0x3a,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x36,0x49,0x09,0x3f,0x48,
	0x48,0x49,0x36,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3c,0x42,0x40,0x40,0x40,0x40,0x42,0x3c,0x08,0x08,0x30,0x00,0x30,0x0c,0x00,0x00,0x3c,0x42,0x42,0x7e,0x40,0x40,0x42,0x3c,0x00,0x00,0x00,0x00,0x0c,0x30,
	0x00,0x00,0x3c,0x42,0x42,0x7e,0x40,0x40,0x42,0x3c,0x00,0x00,0x00,0x00,0x18,0x24,0x00,0x00,0x3c,0x42,0x42,0x7e,0x40,0x40,0x42,0x3c,0x00,0x00,0x00,0x00,0x24,0x24,0x00,0x00,0x3c,0x42,0x42,0x7e,0x40,0x40,0x42,
	0x3c,0x00,0x00,0x00,0x00,0x30,0x0c,0x00,0x00,0x18,0x08,0x08,0x08,0x08,0x08,0x08,0x3e,0x00,0x00,0x00,0x00,0x0c,0x30,0x00,0x00,0x18,0x08,0x08,0x08,0x08,0x08,0x08,0x3e,0x00,0x00,0x00,0x00,0x18,0x24,0x00,0x00,
	0x18,0x08,0x08,0x08,0x08,0x08,0x08,0x3e,0x00,0x00,0x00,0x00,0x24,0x24,0x00,0x00,0x18,0x08,0x08,0x08,0x08,0x08,0x08,0x3e,0x00,0x00,0x00,0x00,0x00,0x66,0x18,0x64,0x02,0x3a,0x46,0x42,0x42,0x42,0x42,0x3c,0x00,
	0x00,0x00,0x00,0x32,0x4c,0x00,0x00,0x5c,0x62,0x42,0x42,0x42,0x42,0x42,0x42,0x00,0x00,0x00,0x00,0x30,0x0c,0x00,0x00,0x3c,0x42,0x42,0x42,0x42,0x42,0x42,0x3c,0x00,0x00,0x00,0x00,0x0c,0x30,0x00,0x00,0x3c,0x42,
	0x42,0x42,0x42,0x42,0x42,0x3c,0x00,0x00,0x00,0x00,0x18,0x24,0x00,0x00,0x3c,0x42,0x42,0x42,0x42,0x42,0x42,0x3c,0x00,0x00,0x00,0x00,0x32,0x4c,0x00,0x00,0x3c,0x42,0x42,0x42,0x42,0x42,0x42,0x3c,0x00,0x00,0x00,
	0x00,0x24,0x24,0x00,0x00,0x3c,0x42,0x42,0x42,0x42,0x42,0x42,0x3c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x10,0x00,0x00,0x7c,0x00,0x00,0x10,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x3c,0x46,0x4a,0x4a,
	0x52,0x52,0x62,0x3c,0x40,0x00,0x00,0x00,0x30,0x0c,0x00,0x00,0x42,0x42,0x42,0x42,0x42,0x42,0x46,0x3a,0x00,0x00,0x00,0x00,0x0c,0x30,0x00,0x00,0x42,0x42,0x42,0x42,0x42,0x42,0x46,0x3a,0x00,0x00,0x00,0x00,0x18,
	0x24,0x00,0x00,0x42,0x42,0x42,0x42,0x42,0x42,0x46,0x3a,0x00,0x00,0x00,0x00,0x24,0x24,0x00,0x00,0x42,0x42,0x42,0x42,0x42,0x42,0x46,0x3a,0x00,0x00,0x00,0x00,0x0c,0x30,0x00,0x00,0x42,0x42,0x42,0x42,0x42,0x46,
	0x3a,0x02,0x02,0x42,0x3c,0x00,0x00,0x40,0x40,0x40,0x5c,0x62,0x42,0x42,0x42,0x42,0x62,0x5c,0x40,0x40,0x40,0x00,0x24,0x24,0x00,0x00,0x42,0x42,0x42,0x42,0x42,0x46,0x3a,0x02,0x02,0x42,0x3c
};