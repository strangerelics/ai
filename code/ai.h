#if !defined(CLAIRE_AI_H)

#include "platform.h"
#include "sound.h"
#include "draw.h"

#define BOARD_WIDTH 32
#define BOARD_HEIGHT 20
#define GAME_HEIGHT 240
#define GAME_WIDTH 256

struct RGBA_COLOR
{
    uint8 r,g,b,a;
};


struct MEMORY_ARENA
{
    memory_index size;
    uint8 *base;
    memory_index used;
};


internal void InitializeArena(MEMORY_ARENA *arena, memory_index size, uint8 *base)
{
    arena->size = size;
    arena->base = base;
    arena->used = 0;
}

#define PushStruct(arena, type) (type *)PushSize_(arena, sizeof(type))
#define PushArray(arena, count, type) (type *)PushSize_(arena, (count)*sizeof(type))
void * PushSize_(MEMORY_ARENA *arena, memory_index size)
{
    Assert((arena->used + size) <= arena->size);
    void *result = arena->base + arena->used;
    arena->used += size;

    return result;
}

#define PopStruct(arena, type) *((type *)PopSize_(arena, sizeof(type)))
#define PopArray(arena, count, type) *((type *)PopSize_(arena, (count)*sizeof(type)))
void * PopSize_(MEMORY_ARENA *arena, memory_index size)
{
    Assert((arena->used - size) >= 0);
    void *result = arena->base + arena->used - size;
    arena->used -= size;

    return result;
}

#define BLOCK_SIZE 16
#define CAMERA_WIDTH 16
#define CAMERA_HEIGHT (CAMERA_WIDTH - 1)
#define LEVELMAP_WIDTH (CAMERA_WIDTH * 1)
#define LEVELMAP_HEIGHT (CAMERA_WIDTH * 1)


struct PixelBuffer
{
    uint8* pixels;
    int w, h, pitch;
};

struct Entity
{
    TileRect sprite;
    V2 position;
    float temperature;
    float brightness;
};

struct Sense
{
    float mean;
    float variance;
};

#define IDEAS_COUNT 256

struct GAME_STATE
{
    MEMORY_ARENA arena;
    PixelBuffer buffer;
    uint8 buffer_pixels[GAME_WIDTH * GAME_HEIGHT];
    PixelBuffer spritemap;
    uint8 spritemap_pixels[8 * 8 * 256];
    PixelBuffer debug_spritemap;
    uint8 debug_spritemap_pixels[8 * 8 * 256];
    
    int frames;

    
    // debug state
    int mode;
    int edit_mode;
    TileRect selected_sprites[8];
    uint8 current_sprite;
    // selecting
    bool32 copying;
    TileCoord select_start;
    bool32 selecting_sprite;
    // editing
    uint8 cursor_color;
    bool32 swap_colors; 

    
    // game state
    TriangleChannel triangle_channel;
    AUDIO_CLOCK clock;
    float64 audio_beats_written;
    float32 audio_buffer[1024];
    bool32 muted;
    int audio_debug_refresh_timer;
    float32 debug_frequency;

    int random_number_index;

    V2 friend_position;
    float friend_temperature;

    float associations[IDEAS_COUNT * (IDEAS_COUNT - 1) / 2];
    float mood[IDEAS_COUNT];
    Entity entities[IDEAS_COUNT];
    Sense senses[IDEAS_COUNT];
};

#define PAIN_PLEASURE 0
#define NEAR_FAR 1
#define HOT_COLD 2
#define BRIGHT_DARK 3
#define MOVE_TOWARDS_AWAY 4
#define DISTANCE 5

#define CLAIRE_AI_H
#endif
