#pragma once
// Types
typedef unsigned char u8;
typedef unsigned short u16;

// CB
#define CB_PREFIX_OFFSET 0x100

// Screen
#define SCREEN_SCALE 4
#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 144
#define SCALED_SCREEN_WIDTH SCREEN_WIDTH * SCREEN_SCALE
#define SCALED_SCREEN_HEIGHT SCREEN_HEIGHT * SCREEN_SCALE
#define TILEMAP_WIDTH 32

// Interruptions
#define VBlank 0x90

// Memory locations
#define INITIAL_PROGRAM_COUNTER 0x0100
#define rLY 0xFF44
#define INITIAL_STACK_POINTER 0xFFFE
#define VRAM_LOCATION_START 0x8000
#define VRAM_LOCATION_TILEDATA_START 0x9000
#define VRAM_LOCATION_TILEDATA_END 0x97F0
#define VRAM_LOCATION_TILEMAP_START 0x9800
#define VRAM_LOCATION_TILEMAP_END 0x9A33
#define VRAM_LOCATION_END 0x9FFF
#define HRAM_LOCAITON_START 0xFF00