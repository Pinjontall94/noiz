#ifndef noiz_h
#define noiz_h
#include <SDL2/SDL.h>
#include <SDL2/SDL_stdinc.h>
#include <stdint.h>

#define SAMPLE_RATE 44100
#define AUDIO_BUF_SIZE 1024

void oscillator(Sint16 *stream, size_t len);
void audio_callback(void *userdata, Uint8 *stream, int len);
void sdl_setup(void);

#endif // noiz_h
