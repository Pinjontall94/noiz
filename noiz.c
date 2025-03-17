#include "noiz.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_stdinc.h>
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    bool quit = false;
    sdl_setup();
    printf("Ok\n");

    while (!quit)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                quit = true;
                break;
            }
        }
    }

    SDL_Quit();
    return 0;
}

void oscillator(Sint16 *stream, size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
	Sint16 val = 0;
	stream[i] = val;
    }
}

void audio_callback(void *userdata, Uint8 *stream, int len)
{
    (void)userdata;
    assert((len & (len - 1)) == 0);
    // Convert types and pass stream to oscillator
    oscillator((Sint16 *)stream, len / 2);
}

void sdl_setup(void)
{
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        fprintf(stderr, "Failed to init subsystem: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_AudioSpec want = {
        .freq = SAMPLE_RATE,
        .format = AUDIO_S16LSB, // Sint16, little-endian
        .channels = 1,
        .size = AUDIO_BUF_SIZE,
        .callback = audio_callback,
    };

    SDL_AudioDeviceID dev = SDL_OpenAudioDevice(NULL, 0, &want, NULL, SDL_AUDIO_ALLOW_ANY_CHANGE);
    if (dev < 1)
    {
        fprintf(stderr, "Failed to open audio device: %s\n", SDL_GetError());
        exit(1);
    }
    // Unpause audio (start playback)
    SDL_PauseAudioDevice(dev, 0);
    printf("Successfully initialized audio\n");
}
