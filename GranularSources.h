#pragma once
#include <juce_audio_basics/juce_audio_basics.h>
#include <memory>
#include <vector>
#include <cmath>
#include <algorithm>

// Material de audio para la seccion granular.
struct SampleData
{
    juce::AudioBuffer<float> buf;   // 1 o 2 canales
    double rate = 44100.0;
    juce::String name;
    int length() const { return buf.getNumSamples(); }
};

// Fuentes incluidas (se generan por codigo, no hace falta ningun archivo).
// El indice 8 (kBuiltIn) es "tu sample" cargado desde un archivo.
namespace granular_sources
{
    constexpr int kBuiltIn = 8;

    inline const char* nameOf (int i)
    {
        static const char* n[] = { "Choir Air", "Glass Bells", "Warm Pad", "Vinyl Dust", "Rain Wash",
                                   "Sub Drone", "Tropical Pluck", "Space Shimmer", "TU SAMPLE" };
        return n[juce::jlimit (0, kBuiltIn, i)];
    }

    inline void finish (SampleData& s)
    {
        const int n = s.buf.getNumSamples();
        float peak = 0.0001f;
        for (int c = 0; c < s.buf.getNumChannels(); ++c)
            peak = std::max (peak, s.buf.getMagnitude (c, 0, n));
        s.buf.applyGain (0.85f / peak);
        const int fade = (int) (0.05 * s.rate);
        for (int c = 0; c < s.buf.getNumChannels(); ++c)
        {
            s.buf.applyGainRamp (c, 0, fade, 0.f, 1.f);
            s.buf.applyGainRamp (c, n - fade, fade, 1.f, 0.f);
        }
    }

    inline std::shared_ptr<SampleData> make (int idx)
    {
        auto s = std::make_shared<SampleData>();
        const double sr = 44100.0;
        const int N = (int) (5.0 * sr);
        const float twoPi = juce::MathConstants<float>::twoPi;
        s->rate = sr;
        s->name = nameOf (idx);
        s->buf.setSize (2, N);
        s->buf.clear();
        auto* L = s->buf.getWritePointer (0);
        auto* R = s->buf.getWritePointer (1);
        juce::Random rng (1234 + idx);
        auto frand = [&] { return rng.nextFloat() * 2.f - 1.f; };

        switch (idx)
        {
            case 0: // Choir Air: acorde de "ahh" con formantes
            {
                const float notes[3] = { 220.f, 277.18f, 329.63f };
                const float form[3] = { 800.f, 1150.f, 2900.f };
                for (int k = 0; k < 3; ++k)
                    for (int h = 1; h <= 10; ++h)
                    {
                        const float f = notes[k] * (float) h;
                        float a = 0.f;
                        for (int q = 0; q < 3; ++q) { const float d = (f - form[q]) / (form[q] * 0.28f); a += std::exp (-d * d); }
                        a = a / (float) h * 1.5f + 0.02f / (float) h;
                        const float ph0 = rng.nextFloat() * twoPi, ph1 = rng.nextFloat() * twoPi;
                        for (int i = 0; i < N; ++i)
                        {
                            const float t = (float) i / (float) sr;
                            const float vib = 1.f + 0.004f * std::sin (twoPi * 5.2f * t);
                            const float sw = 0.6f + 0.4f * std::sin (twoPi * 0.25f * t + (float) k);
                            L[i] += a * sw * std::sin (twoPi * f * 1.001f * vib * t + ph0);
                            R[i] += a * sw * std::sin (twoPi * f * 0.999f * vib * t + ph1);
                        }
                    }
                float lp = 0.f;
                for (int i = 0; i < N; ++i) { lp += 0.2f * (frand() - lp); L[i] += lp * 0.15f; R[i] += lp * 0.15f; }
                break;
            }
            case 1: // Glass Bells
            {
                const float notes[6] = { 880.f, 1108.7f, 1318.5f, 987.77f, 1760.f, 659.25f };
                const float ratios[4] = { 1.f, 2.76f, 5.4f, 8.93f };
                for (int hit = 0; hit < 8; ++hit)
                {
                    const int start = (int) ((0.1 + hit * 0.55) * sr);
                    const float f = notes[hit % 6];
                    const float pan = 0.5f + 0.4f * frand();
                    for (int p = 0; p < 4; ++p)
                    {
                        const float a = 0.5f / (1.f + (float) p * 1.3f);
                        const float dec = 1.f / (0.9f + 0.4f * (float) (3 - p));
                        for (int i = start; i < N; ++i)
                        {
                            const float t = (float) (i - start) / (float) sr;
                            const float e = std::exp (-t * dec * 2.f);
                            if (e < 0.002f) break;
                            const float v = a * e * std::sin (twoPi * f * ratios[p] * t);
                            L[i] += v * (1.f - pan); R[i] += v * pan;
                        }
                    }
                }
                break;
            }
            case 2: // Warm Pad: sierras desafinadas filtradas
            {
                const float notes[5] = { 110.f, 164.81f, 220.f, 277.18f, 329.63f };
                for (int k = 0; k < 5; ++k)
                    for (int ch = 0; ch < 2; ++ch)
                    {
                        float ph = rng.nextFloat(), ph2 = rng.nextFloat(), lp = 0.f;
                        const float det = ch == 0 ? 1.004f : 0.996f;
                        float* o = ch == 0 ? L : R;
                        for (int i = 0; i < N; ++i)
                        {
                            const float t = (float) i / (float) sr;
                            ph += notes[k] * det / (float) sr; ph -= std::floor (ph);
                            ph2 += notes[k] * det * 1.006f / (float) sr; ph2 -= std::floor (ph2);
                            const float saw = (2.f * ph - 1.f) + (2.f * ph2 - 1.f);
                            lp += 0.06f * (saw - lp);
                            o[i] += lp * (0.7f + 0.3f * std::sin (twoPi * 0.18f * t + (float) k)) * 0.5f;
                        }
                    }
                break;
            }
            case 3: // Vinyl Dust
            {
                float envL = 0.f, envR = 0.f, hissLp = 0.f;
                for (int i = 0; i < N; ++i)
                {
                    if (rng.nextFloat() < 0.0009f) envL = frand() * 0.9f;
                    if (rng.nextFloat() < 0.0009f) envR = frand() * 0.9f;
                    envL *= 0.93f; envR *= 0.93f;
                    const float n = frand();
                    hissLp += 0.5f * (n - hissLp);
                    const float hiss = (n - hissLp) * 0.05f;
                    const float hum = 0.04f * std::sin (twoPi * 55.f * (float) i / (float) sr);
                    L[i] = envL * (frand() * 0.8f) + hiss + hum;
                    R[i] = envR * (frand() * 0.8f) + hiss * 0.9f + hum;
                }
                break;
            }
            case 4: // Rain Wash
            {
                float lpL = 0.f, lpR = 0.f, hpL = 0.f, hpR = 0.f, lfoPh = rng.nextFloat();
                for (int i = 0; i < N; ++i)
                {
                    const float t = (float) i / (float) sr;
                    const float amp = 0.55f + 0.35f * std::sin (twoPi * 0.17f * t) * std::sin (twoPi * 0.071f * t + 1.f);
                    const float nL = frand(), nR = frand();
                    lpL += 0.45f * (nL - lpL); lpR += 0.45f * (nR - lpR);
                    hpL += 0.06f * (lpL - hpL); hpR += 0.06f * (lpR - hpR);
                    float dropL = 0.f, dropR = 0.f;
                    if (rng.nextFloat() < 0.0012f) dropL = frand() * 0.7f;
                    if (rng.nextFloat() < 0.0012f) dropR = frand() * 0.7f;
                    L[i] = (lpL - hpL) * amp + dropL;
                    R[i] = (lpR - hpR) * amp + dropR;
                    lfoPh += 0.f;
                }
                break;
            }
            case 5: // Sub Drone
            {
                const float f[4] = { 55.f, 55.35f, 82.41f, 110.2f };
                for (int k = 0; k < 4; ++k)
                    for (int i = 0; i < N; ++i)
                    {
                        const float t = (float) i / (float) sr;
                        const float a = (k < 2 ? 0.6f : 0.25f) * (0.75f + 0.25f * std::sin (twoPi * (0.07f + 0.03f * (float) k) * t));
                        const float v = a * (std::sin (twoPi * f[k] * t) + 0.18f * std::sin (twoPi * f[k] * 2.f * t) + 0.07f * std::sin (twoPi * f[k] * 3.f * t));
                        L[i] += v * (k % 2 ? 0.8f : 1.f); R[i] += v * (k % 2 ? 1.f : 0.8f);
                    }
                break;
            }
            case 6: // Tropical Pluck: arpegio de cuerdas Karplus-Strong
            {
                const float notes[8] = { 220.f, 261.63f, 329.63f, 392.f, 493.88f, 392.f, 329.63f, 261.63f };
                const int step = (int) (0.3 * sr);
                for (int n = 0; n * step < N; ++n)
                {
                    const float f = notes[n % 8];
                    const int len = std::max (2, (int) ((float) sr / f));
                    std::vector<float> line ((size_t) len);
                    for (auto& x : line) x = frand();
                    const float pan = (n % 2) ? 0.7f : 0.3f;
                    int pos = 0;
                    float prev = 0.f;
                    for (int i = n * step; i < N; ++i)
                    {
                        const float cur = line[(size_t) pos];
                        const float nxt = 0.5f * (cur + prev) * 0.997f;
                        line[(size_t) pos] = nxt;
                        prev = cur;
                        pos = (pos + 1) % len;
                        if (i - n * step > (int) (2.2 * sr)) break;
                        L[i] += cur * (1.f - pan) * 0.6f;
                        R[i] += cur * pan * 0.6f;
                    }
                }
                break;
            }
            default: // Space Shimmer
            {
                const float f[5] = { 440.f, 659.25f, 880.f, 1108.7f, 1318.5f };
                for (int k = 0; k < 5; ++k)
                    for (int i = 0; i < N; ++i)
                    {
                        const float t = (float) i / (float) sr;
                        const float a = 0.4f / (1.f + 0.4f * (float) k) * (0.55f + 0.45f * std::sin (twoPi * (0.11f + 0.05f * (float) k) * t + (float) k * 1.7f));
                        L[i] += a * std::sin (twoPi * f[k] * 1.0015f * t);
                        R[i] += a * std::sin (twoPi * f[k] * 0.9985f * t + 0.7f);
                    }
                break;
            }
        }
        finish (*s);
        return s;
    }
}
