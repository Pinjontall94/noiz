#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>
#include <SDL2/SDL_error.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define SAMPLE_RATE 44100
#define AUDIO_BUF_SIZE 1024

void sdl_setup(void);
void callback(void *userdata, Uint8 *stream, int len);

int main(void)
{
    sdl_setup();
    printf("Ok\n");
    SDL_Quit();
    return 0;
}

void callback(void *userdata, Uint8 *stream, int len)
{
    (void) userdata;
    assert(0 && "not implemented");
}

void sdl_setup(void)
{
    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_EVENTS) < 1)
    {
        fprintf(stderr, "Failed to init subsystem: %s", SDL_GetError());
        exit(1);
    }

    SDL_AudioSpec audiospec = {
        .freq = SAMPLE_RATE,
        .format = AUDIO_S16LSB, // Sint16, little-endian
        .channels = 1,
        .size = AUDIO_BUF_SIZE,
        .callback = callback,
    };

    SDL_AudioDeviceID dev = SDL_OpenAudioDevice(NULL, 0, desired, obtained, SDL_AUDIO_ALLOW_ANY_CHANGE);
    if (dev < 1)
    {
        fprintf(stderr, "Failed to open audio device: %s\n", SDL_GetError());
        exit(1);
    }
    // Unpause audio (start playback)
    SDL_PauseAudioDevice(dev, 0);
}
