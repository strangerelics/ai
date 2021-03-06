float32 GetStep(uint32 samples_per_tick, float frequency)
{
    float32 step = 0;
    if (frequency > 0)
    {
        uint32 samples_per_second = samples_per_tick * 1000;
        float32 period = samples_per_second / frequency;
        step = frequency / samples_per_second;
    }
    return step;
}

void SinWave(float32* stream, uint64 length, uint32 samples_per_tick, float frequency, float attack, void* memory)
{
    SIN_STATE* state = (SIN_STATE*) memory;
    float32 step = GetStep(samples_per_tick, frequency);
    for (uint32 i=0; i<length; i++)
    {
        *stream += ((float32)sin(state->x * Tau32) * 0.5f);
        stream++;
        state->x += step;
        while (state->x > 1.0f)
        {
            state->x -= 1.0f;
        }
    }
}

global_variable float32 triangle_shape[512] = {
    8.0f, 8.0f, 8.0f, 8.0f, 8.0f, 8.0f, 8.0f, 8.0f, 8.0f, 8.0f, 8.0f, 8.0f, 8.0f, 8.0f, 8.0f, 8.0f, 
    9.0f, 9.0f, 9.0f, 9.0f, 9.0f, 9.0f, 9.0f, 9.0f, 9.0f, 9.0f, 9.0f, 9.0f, 9.0f, 9.0f, 9.0f, 9.0f, 
    10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 
    11.0f, 11.0f, 11.0f, 11.0f, 11.0f, 11.0f, 11.0f, 11.0f, 11.0f, 11.0f, 11.0f, 11.0f, 11.0f, 11.0f, 11.0f, 11.0f, 
    12.0f, 12.0f, 12.0f, 12.0f, 12.0f, 12.0f, 12.0f, 12.0f, 12.0f, 12.0f, 12.0f, 12.0f, 12.0f, 12.0f, 12.0f, 12.0f, 
    13.0f, 13.0f, 13.0f, 13.0f, 13.0f, 13.0f, 13.0f, 13.0f, 13.0f, 13.0f, 13.0f, 13.0f, 13.0f, 13.0f, 13.0f, 13.0f, 
    14.0f, 14.0f, 14.0f, 14.0f, 14.0f, 14.0f, 14.0f, 14.0f, 14.0f, 14.0f, 14.0f, 14.0f, 14.0f, 14.0f, 14.0f, 14.0f, 
    15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 
    15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 
    14.58f, 14.58f, 14.58f, 14.58f, 14.58f, 14.58f, 14.58f, 14.58f, 
    14.58f, 14.58f, 14.58f, 14.58f, 14.58f, 14.58f, 14.58f, 14.58f, 
    13.1f, 13.1f, 13.1f, 13.1f, 13.1f, 13.1f, 13.1f, 13.1f, 13.1f, 13.1f, 13.1f, 13.1f, 13.1f, 13.1f, 13.1f, 13.1f, 
    11.46f, 11.46f, 11.46f, 11.46f, 11.46f, 11.46f, 11.46f, 11.46f, 11.46f, 11.46f, 11.46f, 11.46f, 11.46f, 11.46f, 11.46f, 11.46f, 
    9.88f, 9.88f, 9.88f, 9.88f, 9.88f, 9.88f, 9.88f, 9.88f, 9.88f, 9.88f, 9.88f, 9.88f, 9.88f, 9.88f, 9.88f, 9.88f, 
    8.7f, 8.7f, 8.7f, 8.7f, 8.7f, 8.7f, 8.7f, 8.7f, 8.7f, 8.7f, 8.7f, 8.7f, 8.7f, 8.7f, 8.7f, 8.7f, 
    7.66f, 7.66f, 7.66f, 7.66f, 7.66f, 7.66f, 7.66f, 7.66f, 7.66f, 7.66f, 7.66f, 7.66f, 7.66f, 7.66f, 7.66f, 7.66f, 
    6.64f, 6.64f, 6.64f, 6.64f, 6.64f, 6.64f, 6.64f, 6.64f, 6.64f, 6.64f, 6.64f, 6.64f, 6.64f, 6.64f, 6.64f, 6.64f, 
    5.70f, 5.70f, 5.70f, 5.70f, 5.70f, 5.70f, 5.70f, 5.70f, 5.70f, 5.70f, 5.70f, 5.70f, 5.70f, 5.70f, 5.70f, 5.70f, 
    4.76f, 4.76f, 4.76f, 4.76f, 4.76f, 4.76f, 4.76f, 4.76f, 4.76f, 4.76f, 4.76f, 4.76f, 4.76f, 4.76f, 4.76f, 4.76f, 
    3.82f, 3.82f, 3.82f, 3.82f, 3.82f, 3.82f, 3.82f, 3.82f, 3.82f, 3.82f, 3.82f, 3.82f, 3.82f, 3.82f, 3.82f, 3.82f, 
    2.88f, 2.88f, 2.88f, 2.88f, 2.88f, 2.88f, 2.88f, 2.88f, 2.88f, 2.88f, 2.88f, 2.88f, 2.88f, 2.88f, 2.88f, 2.88f, 
    2.18f, 2.18f, 2.18f, 2.18f, 2.18f, 2.18f, 2.18f, 2.18f, 2.18f, 2.18f, 2.18f, 2.18f, 2.18f, 2.18f, 2.18f, 2.18f, 
    1.46f, 1.46f, 1.46f, 1.46f, 1.46f, 1.46f, 1.46f, 1.46f, 1.46f, 1.46f, 1.46f, 1.46f, 1.46f, 1.46f, 1.46f, 1.46f, 
    0.76f, 0.76f, 0.76f, 0.76f, 0.76f, 0.76f, 0.76f, 0.76f, 0.76f, 0.76f, 0.76f, 0.76f, 0.76f, 0.76f, 0.76f, 0.76f, 
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 
    1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 
    2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 
    3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 
    4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 
    5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 
    6.0f, 6.0f, 6.0f, 6.0f, 6.0f, 6.0f, 6.0f, 6.0f, 6.0f, 6.0f, 6.0f, 6.0f, 6.0f, 6.0f, 6.0f, 6.0f, 
    7.0f, 7.0f, 7.0f, 7.0f, 7.0f, 7.0f, 7.0f, 7.0f, 7.0f, 7.0f, 7.0f, 7.0f, 7.0f, 7.0f, 7.0f, 7
};

// global_variable float triangle_shape[32] = {
//     0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 
//     8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f,
//     16.0f, 15.0f, 14.0f, 13.0f, 12.0f, 11.0f, 10.0f, 9.0f, 
//     8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f
// };

global_variable float square_shape[2] = {
    0.0f, 15.0f
};

global_variable float weird_shape[4] = {
    0.0f, 7.5f, 15.0f, 7.5f
};

float32 BandHarmonic(float32 x, int i)
{
    int harmonic = (i * 2) + 1;
    float32 theta = (((x * harmonic) / 2.0f));
    float32 result = sinf(Tau32 * theta) / harmonic;
    return result;
}


void Triangle(TriangleChannel* state, float32* stream, uint64 length, uint32 samples_per_tick, float frequency, float attack)
{
    float32 period = GetStep(samples_per_tick, frequency);
    for (uint32 i=0; i<length; i++)
    {
        int num_steps = ArrayCount(triangle_shape);
        float step_x = state->x * num_steps;
        int step = (int)step_x;
        step_x -= step;
        float32 previous_level = triangle_shape[(step + num_steps - 1) % num_steps] / 7.5f - 1.0f;
        float32 this_level = triangle_shape[step] / 7.5f - 1.0f;
        float32 next_level = triangle_shape[(step + 1) % num_steps] / 7.5f - 1.0f;

        float32 level = 0.0f;
        if (state->num_harmonics > 0)
        {
            float32 x = step_x;
            float32 start_level;
            float32 end_level;
            if (x >= 0.5f)
            {
                start_level = this_level;
                end_level = next_level;
                x -= 1.0f;
            }
            else
            {
                start_level = previous_level;
                end_level = this_level;
            }
            if (x > 0.5f) x -= 1.0f;
            float32 diff = end_level - start_level;
            float32 pre_band = 0.0f;
            float32 band_level = 0.0f;
            for (int i=0; i < state->num_harmonics; i++)
            {
                int harmonic = (i * 2) + 1;
                float32 theta = (((x * harmonic) / 2.0f));
                float32 this_band = sinf(Tau32 * theta) / harmonic;
                pre_band += BandHarmonic(x, i);
                band_level += BandHarmonic(0.5f, i);
            }
            float32 band = ((pre_band) + band_level) / (2.0f * band_level);
            float32 band_shift = diff * band;
            level = start_level + band_shift;
        }
        else if (state->num_harmonics < 0)
        {
            float32 diff = next_level - this_level;
            level = this_level + diff * step_x;
        }
        else
        {
            level = this_level; 
        }
        // float32 result = (level / 7.5f) - 1.0f;
        *stream = level * attack;
        
        stream++;
        state->x += period;
        while (state->x >= 1.0f)
        {
            state->x -= 1.0f;
        }
        // float32 result;
        // {
        //     float32 x = state->x;
        //     float32 phase = x * 2.0f;
        //     if (x >= 0.5f)
        //     {
        //         phase -= 1.0f;
        //     }
        //     result = 0;
        //     float32 step = (float32)floor(phase * 15);
        //     float32 step_phase = (phase * 15) - step;
        //     // step_phase = (float32)(pow(step_phase * 2.0f - 1.0f, 3) + 1.0f) / 2.0f;
        //     // step_phase = (float32)sin(step_phase * Tau32) * 0.1f;
        //     step_phase = (float32)asin(pow(step_phase * 2.0f - 1.0f, 1)) / Tau32;
        //     step += step_phase;
        //     if (step > 15) {
        //         step = 30 - step;
        //     }
        //     step = max(step, 0.0f);
        //     // result = (float32)(pow(floor(phase * 15.0f) / 15.0f, 0.75f) * 2.0f) - 1.0f;
        //     // result = (float32)(pow(step / 15.0f, .9) * 2.0f) - 1.0f;
        //     // result = (float32)((step / 15.0f) * 2.0f) - 1.0f;
        //     result = ((float32)pow(phase, 0.8) * 2.0f) - 1.0f;
        //     // result = (float32)((floor(phase * 15) / 15.0f) * 2.0f) - 1.0f;
        //     if (x < 0.5f)
        //     {
        //         result = (result *-1);
        //         // result = result - ((float32)sin(step_phase * Tau32 / 2.0f) * 0.1f);
        //     }
        //     else
        //     {

        //     }
        // }
        // *stream += ((float32)(result) * 0.15f);
        // stream++;
        // state->x += period;
        // while (state->x > 1.0)
        // {
        //     state->x -= 1.0;
        // }
    }
}

void Play(float64 time, AUDIO_CURSOR* cursor, float frequency, float attack, TriangleChannel* data)
{
    if (cursor->written >= cursor->end)
    {
        return;
    }
    cursor->position = cursor->position.Plus(time);
    if (cursor->position.LessThan(cursor->start))
    {
        return;
    }
    float64 diff = cursor->position.Minus(cursor->start).Time();
    float64 time_to_play = min(diff, time);
    uint64 length = min((uint64)(time_to_play * cursor->samples_per_beat), cursor->end - cursor->written);
    Triangle(data, &(cursor->stream)[cursor->written], length, cursor->samples_per_tick, frequency, attack);
    cursor->written += length;
}

float32 AbsoluteNote(int note)
{
    return 440.0f * (float32)pow(2, (note - 69) / 12.0f);
}

int Minor(int note)
{
    switch (note)
    {
        case 0:
            return 0;
        case 1:
            return 2;
        case 2:
            return 3;
        case 3:
            return 5;
        case 4:
            return 7;
        case 5:
            return 8;
        case 6:
            return 10;
        default:
            return 0;
    }
}

float32 AMinor(int note, int accidental)
{
    int octave = note / 7;
    int mod = note % 7;
    if (mod < 0)
    {
        mod += 7;
    }
    int pitch = Minor(mod);
    pitch += octave * 12;
    pitch += accidental;
    pitch += 45;
    return AbsoluteNote(pitch);
}

float32 AMinor(int note)
{
    return AMinor(note, 0);
}

void GetSound(GAME_AUDIO* audio, GAME_STATE* state, uint32 ticks)
{
    AUDIO_CLOCK *clock = &(state->clock);
    AUDIO_CURSOR cursor = {};

    float32 samples_per_minute = (float32)(audio->samples_per_tick * 1000 * 60);
    float32 samples_per_beat = samples_per_minute / clock->bpm;
    float64 elapsed = (ticks * audio->samples_per_tick) / samples_per_beat;
    clock->time = clock->time.Plus(elapsed);
    state->audio_beats_written -= elapsed;
    state->audio_beats_written = max(state->audio_beats_written, 0);

    cursor.start = clock->time.Plus(state->audio_beats_written);
    cursor.end = audio->size;
    cursor.samples_per_beat = samples_per_beat;
    cursor.samples_per_tick = audio->samples_per_tick;
    cursor.stream = (float32*)audio->stream;

#if 1
    while(!state->muted && cursor.written < cursor.end)
    {
        // Play(1.0f, &cursor, 0, 0.5f, &(state->triangle_channel));
        // Play(1.0f, &cursor, AMin, 0.5f, &(state->triangle_channel));
        // Play(1.0f, &cursor, state->debug_frequency, 0.75f, &(state->triangle_channel));
        Play(1.0f, &cursor, AMinor(9), 0.5f, &(state->triangle_channel));
        // Play(1.0, &cursor, AMinor(4), 0.5f, &(state->triangle_channel));
        // Play(0.5, &cursor, AMinor(1), 0.5f, &(state->triangle_channel));
        // Play(0.5, &cursor, AMinor(2), 0.5f, &(state->triangle_channel));
        // Play(1.0, &cursor, AMinor(3), 0.5f, &(state->triangle_channel));
        // Play(0.5, &cursor, AMinor(2), 0.5f, &(state->triangle_channel));
        // Play(0.5, &cursor, AMinor(1), 0.5f, &(state->triangle_channel));

        // Play(1.0, &cursor, AMinor(0), 0.5f, &(state->triangle_channel));
        // Play(0.5, &cursor, AMinor(0), 0.5f, &(state->triangle_channel));
        // Play(0.5, &cursor, AMinor(2), 0.5f, &(state->triangle_channel));
        // Play(1.0, &cursor, AMinor(4), 0.5f, &(state->triangle_channel));
        // Play(0.5, &cursor, AMinor(3), 0.5f, &(state->triangle_channel));
        // Play(0.5, &cursor, AMinor(2), 0.5f, &(state->triangle_channel));

        // Play(1.0, &cursor, AMinor(1), 0.5f, &(state->triangle_channel));
        // Play(0.5, &cursor, AMinor(1), 0.5f, &(state->triangle_channel));
        // Play(0.5, &cursor, AMinor(2), 0.5f, &(state->triangle_channel));
        // Play(1.0, &cursor, AMinor(3), 0.5f, &(state->triangle_channel));
        // Play(1.0, &cursor, AMinor(4), 0.5f, &(state->triangle_channel));

        // Play(1.0, &cursor, AMinor(2), 0.5f, &(state->triangle_channel));
        // Play(1.0, &cursor, AMinor(0), 0.5f, &(state->triangle_channel));
        // Play(1.0, &cursor, AMinor(0), 0.5f, &(state->triangle_channel));
        // Play(1.0, &cursor,     0,     0.5f, &(state->triangle_channel));

        // Play(0.5, &cursor,     0,     0.5f, &(state->triangle_channel));
        // Play(1.0, &cursor, AMinor(3), 0.5f, &(state->triangle_channel));
        // Play(0.5, &cursor, AMinor(5), 0.5f, &(state->triangle_channel));
        // Play(1.0, &cursor, AMinor(7), 0.5f, &(state->triangle_channel));
        // Play(0.5, &cursor, AMinor(6), 0.5f, &(state->triangle_channel));
        // Play(0.5, &cursor, AMinor(5), 0.5f, &(state->triangle_channel));

        // Play(1.5, &cursor, AMinor(4), 0.5f, &(state->triangle_channel));
        // Play(0.5, &cursor, AMinor(2), 0.5f, &(state->triangle_channel));
        // Play(1.0, &cursor, AMinor(4), 0.5f, &(state->triangle_channel));
        // Play(0.5, &cursor, AMinor(3), 0.5f, &(state->triangle_channel));
        // Play(0.5, &cursor, AMinor(2), 0.5f, &(state->triangle_channel));

        // Play(1.0, &cursor, AMinor(1), 0.5f, &(state->triangle_channel));
        // Play(0.5, &cursor, AMinor(1), 0.5f, &(state->triangle_channel));
        // Play(0.5, &cursor, AMinor(2), 0.5f, &(state->triangle_channel));
        // Play(1.0, &cursor, AMinor(3), 0.5f, &(state->triangle_channel));
        // Play(1.0, &cursor, AMinor(4), 0.5f, &(state->triangle_channel));

        // Play(1.0, &cursor, AMinor(2), 0.5f, &(state->triangle_channel));
        // Play(1.0, &cursor, AMinor(0), 0.5f, &(state->triangle_channel));
        // Play(1.0, &cursor, AMinor(0), 0.5f, &(state->triangle_channel));
        // Play(1.0, &cursor,     0,     0.5f, &(state->triangle_channel));
    }
#endif
    state->audio_beats_written += audio->size / samples_per_beat;
    if (1)
    {
        state->audio_debug_refresh_timer = 100;
        memcpy(state->audio_buffer,audio->stream, 1024 * 4);
    }
    else
    {
        state->audio_debug_refresh_timer -= ticks;
    }
}
