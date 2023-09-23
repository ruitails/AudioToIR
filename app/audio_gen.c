#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "alsa/asoundlib.h"

// Parameters
#define SAMPLE_RATE 44100
#define DURATION 10.0
#define AMPLITUDE 0.5
#define FREQUENCY 5000.0
#define M_PI 3.14159265358979323846

int audio_gen() {
    int err;
    snd_pcm_t *handle;
    snd_pcm_sframes_t frames;
    double t, phase_increment;
    short sample;
    int scale = (1 << 15) - 1; // 16-bit audio, signed

    // Initialize the ALSA PCM handle
    if ((err = snd_pcm_open(&handle, "default", SND_PCM_STREAM_PLAYBACK, 0)) < 0) {
        printf("Error opening PCM device: %s\n", snd_strerror(err));
        return EXIT_FAILURE;
    }

    if ((err = snd_pcm_set_params(handle, SND_PCM_FORMAT_S16_LE, SND_PCM_ACCESS_RW_INTERLEAVED, 1, SAMPLE_RATE, 1, 500000)) < 0) {
        printf("Error setting PCM parameters: %s\n", snd_strerror(err));
        return EXIT_FAILURE;
    }

    // Calculate phase increment based on desired frequency
    phase_increment = 2.0 * M_PI * FREQUENCY / SAMPLE_RATE;

    // Generate and play the sine wave
    for (t = 0; t < DURATION; t += 1.0 / SAMPLE_RATE) {
        sample = AMPLITUDE * scale * sin(t * phase_increment);
        frames = snd_pcm_writei(handle, &sample, 1);

        if (frames < 0)
            frames = snd_pcm_recover(handle, frames, 0);
        if (frames < 0) {
            printf("Error writing to PCM device: %s\n", snd_strerror(frames));
            break;
        }
    }

    snd_pcm_close(handle);
    printf("\n\nDONE!\n\n");
    return EXIT_SUCCESS;
}
