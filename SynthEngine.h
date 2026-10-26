#pragma once
#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_dsp/juce_dsp.h>
#include <array>
#include <cmath>
#include <vector>
#include <algorithm>
#include "Params.h"

class NematicEngine
{
public:
    using Snap = std::array<float, P_COUNT>;

    void prepare (double sr)
    {
        sampleRate = sr;
        juce::dsp::ProcessSpec spec { sr, 512u, 2u };
        for (auto& v : voices)
        {
            v.filt.prepare (spec);
            v.filt.reset();
            v.amp.setSampleRate (sr);
            v.flt.setSampleRate (sr);
            v.active = false;
        }
        chorus.prepare (spec);
        chorus.reset();
        chorus.setRate (0.6f);
        chorus.setDepth (0.3f);
        chorus.setCentreDelay (9.0f);
        chorus.setFeedback (0.0f);
        chorus.setMix (0.0f);

        reverb.setSampleRate (sr);
        reverb.reset();

        delaySize = (int) (sr * 2.0) + 8;
        dlBuf.assign ((size_t) delaySize, 0.f);
        drBuf.assign ((size_t) delaySize, 0.f);
        wp = 0;
        lpL = lpR = 0.f;
        heldNotes.clear();
        bend = 0.f;
    }

    // ---- MIDI -------------------------------------------------------------
    void handleMidi (const juce::MidiMessage& m, const Snap& p)
    {
        if (m.isNoteOn())            noteOn (m.getNoteNumber(), m.getFloatVelocity(), p);
        else if (m.isNoteOff())      noteOff (m.getNoteNumber());
        else if (m.isPitchWheel())   bend = (float) (m.getPitchWheelValue() - 8192) / 8192.f;
        else if (m.isAllNotesOff() || m.isAllSoundOff()) allOff();
    }

    // ---- Audio ------------------------------------------------------------
    void render (juce::AudioBuffer<float>& out, int start, int num, const Snap& p)
    {
        const int nch = out.getNumChannels();
        while (num > 0)
        {
            const int n = std::min (num, kChunk);
            float* l = out.getWritePointer (0, start);
            float* r = nch > 1 ? out.getWritePointer (1, start) : nullptr;
            renderChunk (l, r, n, p);
            start += n;
            num -= n;
        }
    }

private:
    static constexpr int kChunk = 512;

    struct Voice
    {
        bool active = false, held = false;
        int note = -1;
        float vel = 0.f;
        unsigned long long order = 0;
        double curFreq = 440.0, tgtFreq = 440.0;
        double ph1[7] {}, ph2[7] {}, phSub = 0.0, phMod = 0.0;
        float pEnvVal = 0.f;
        juce::ADSR amp, flt;
        juce::dsp::StateVariableTPTFilter<float> filt;
    };

    static float blep (float t, float dt)
    {
        if (t < dt)       { t /= dt; return t + t - t * t - 1.f; }
        if (t > 1.f - dt) { t = (t - 1.f) / dt; return t * t + t + t + 1.f; }
        return 0.f;
    }

    static float wave (int w, float p, float dt)
    {
        switch (w)
        {
            case 0:  return std::sin (juce::MathConstants<float>::twoPi * p);
            case 1:  return 4.f * std::abs (p - 0.5f) - 1.f;
            case 2:  return (2.f * p - 1.f) - blep (p, dt);
            default:
            {
                float p2 = p + 0.5f; if (p2 >= 1.f) p2 -= 1.f;
                return (p < 0.5f ? 1.f : -1.f) + blep (p, dt) - blep (p2, dt);
            }
        }
    }

    static double noteToFreq (int note) { return 440.0 * std::pow (2.0, (note - 69) / 12.0); }

    void setEnv (Voice& v, const Snap& p)
    {
        v.amp.setParameters ({ p[P_AA], p[P_AD], p[P_AS], p[P_AR] });
        v.flt.setParameters ({ p[P_FA], p[P_FD], p[P_FS], p[P_AR] });
    }

    void trigger (Voice& v, double f, const Snap& p)
    {
        const bool unison = p[P_UNI] > 1.5f;
        v.active = true;
        v.held = true;
        v.order = ++orderCounter;
        v.tgtFreq = f;
        v.curFreq = f;
        for (int i = 0; i < 7; ++i)
        {
            v.ph1[i] = unison ? rng.nextDouble() : 0.0;
            v.ph2[i] = unison ? rng.nextDouble() : 0.0;
        }
        v.phSub = 0.0;
        v.phMod = 0.0;
        v.pEnvVal = p[P_PENV];
        v.filt.reset();
        setEnv (v, p);
        v.amp.reset();
        v.flt.reset();
        v.amp.noteOn();
        v.flt.noteOn();
    }

    void release (Voice& v)
    {
        v.held = false;
        v.amp.noteOff();
        v.flt.noteOff();
    }

    void noteOn (int note, float vel, const Snap& p)
    {
        const double f = noteToFreq (note);
        if (p[P_MONO] > 0.5f)
        {
            heldNotes.push_back (note);
            for (size_t k = 1; k < voices.size(); ++k)
                if (voices[k].active && voices[k].held) release (voices[k]);

            Voice& v = voices[0];
            const bool legato = v.active && v.held;
            v.note = note;
            v.vel = vel;
            if (legato) v.tgtFreq = f;
            else        trigger (v, f, p);
            return;
        }

        Voice* t = nullptr;
        for (auto& v : voices) if (! v.active) { t = &v; break; }
        if (t == nullptr)
        {
            t = &voices[0];
            for (auto& v : voices) if (v.order < t->order) t = &v;
        }
        t->note = note;
        t->vel = vel;
        trigger (*t, f, p);
    }

    void noteOff (int note)
    {
        for (int i = (int) heldNotes.size() - 1; i >= 0; --i)
            if (heldNotes[(size_t) i] == note) { heldNotes.erase (heldNotes.begin() + i); break; }

        Voice& m = voices[0];
        if (m.active && m.held && m.note == note && ! heldNotes.empty() && monoActive)
        {
            m.note = heldNotes.back();
            m.tgtFreq = noteToFreq (m.note);
            return;
        }
        for (auto& v : voices)
            if (v.active && v.held && v.note == note)
                release (v);
    }

    void allOff()
    {
        heldNotes.clear();
        for (auto& v : voices) { v.active = false; v.held = false; }
    }

    // ---- Render -----------------------------------------------------------
    void renderChunk (float* outL, float* outR, int n, const Snap& p)
    {
        monoActive = p[P_MONO] > 0.5f;
        std::fill (tmpL, tmpL + n, 0.f);
        std::fill (tmpR, tmpR + n, 0.f);

        const float lfoInc = p[P_LFOR] / (float) sampleRate;
        for (int i = 0; i < n; ++i)
        {
            lfoPhase += lfoInc;
            if (lfoPhase >= 1.f) lfoPhase -= 1.f;
            lfoBuf[i] = std::sin (juce::MathConstants<float>::twoPi * lfoPhase);
        }

        for (auto& v : voices)
            if (v.active)
            {
                setEnv (v, p);
                renderVoice (v, n, p);
            }

        // drive
        const float drive = p[P_DRIVE];
        if (drive > 0.001f)
        {
            const float g = 1.f + drive * 7.f;
            const float comp = 1.f / (1.f + drive * 2.f);
            for (int i = 0; i < n; ++i)
            {
                tmpL[i] = std::tanh (tmpL[i] * g) * comp;
                tmpR[i] = std::tanh (tmpR[i] * g) * comp;
            }
        }

        // chorus
        {
            float* chans[2] = { tmpL, tmpR };
            juce::dsp::AudioBlock<float> blk (chans, 2, (size_t) n);
            juce::dsp::ProcessContextReplacing<float> ctx (blk);
            chorus.setMix (p[P_CHORUS]);
            chorus.process (ctx);
        }

        // ping-pong delay
        const float dmix = p[P_DMIX];
        if (dmix > 0.001f)
        {
            const float fb = p[P_DFB];
            const int dtS = juce::jlimit (1, delaySize - 1, (int) (p[P_DTIME] * 0.001 * sampleRate));
            for (int i = 0; i < n; ++i)
            {
                int rp = wp - dtS; if (rp < 0) rp += delaySize;
                const float oL = dlBuf[(size_t) rp], oR = drBuf[(size_t) rp];
                lpL += 0.35f * (oL - lpL);
                lpR += 0.35f * (oR - lpR);
                dlBuf[(size_t) wp] = (tmpL[i] + tmpR[i]) * 0.5f + lpR * fb;
                drBuf[(size_t) wp] = lpL * fb;
                tmpL[i] += oL * dmix;
                tmpR[i] += oR * dmix;
                if (++wp >= delaySize) wp = 0;
            }
        }
        else
        {
            std::fill (dlBuf.begin(), dlBuf.end(), 0.f);
            std::fill (drBuf.begin(), drBuf.end(), 0.f);
        }

        // reverb
        {
            juce::Reverb::Parameters rp;
            rp.roomSize = p[P_VSIZE];
            rp.damping = 0.45f;
            rp.wetLevel = p[P_VMIX] * 0.33f;
            rp.dryLevel = 1.f - p[P_VMIX] * 0.35f;
            rp.width = 1.f;
            rp.freezeMode = 0.f;
            reverb.setParameters (rp);
            reverb.processStereo (tmpL, tmpR, n);
        }

        // volumen + limitador suave
        const float g = p[P_VOL] * p[P_VOL] * 1.6f;
        for (int i = 0; i < n; ++i)
        {
            outL[i] = std::tanh (tmpL[i] * g);
            if (outR != nullptr) outR[i] = std::tanh (tmpR[i] * g);
        }
    }

    void renderVoice (Voice& v, int n, const Snap& p)
    {
        const int uni = juce::jlimit (1, 7, (int) std::round (p[P_UNI]));
        const float det = p[P_DET], spread = p[P_SPREAD];
        const int w1 = (int) std::round (p[P_W1]), w2 = (int) std::round (p[P_W2]);
        const float lvl1 = p[P_LVL1], lvl2 = p[P_LVL2], sub = p[P_SUB], noiseLvl = p[P_NOISE];
        const double ratio2 = std::exp2 ((double) p[P_SEMI2] / 12.0);
        const float fmIdx = p[P_FM], fmr = p[P_FMR];
        const float norm = 1.f / std::sqrt ((float) uni);
        const double gCoef = p[P_GLIDE] > 0.0005f ? 1.0 - std::exp (-1.0 / ((double) p[P_GLIDE] * sampleRate)) : 1.0;
        const float pDecCoef = (float) std::exp (-1.0 / ((double) std::max (0.001f, p[P_PDEC]) * sampleRate));
        const int ftype = (int) std::round (p[P_FTYPE]);
        const float maxCut = (float) std::min (20000.0, sampleRate * 0.45);
        const float twoPi = juce::MathConstants<float>::twoPi;
        const double invSr = 1.0 / sampleRate;

        v.filt.setType (ftype == 0 ? juce::dsp::StateVariableTPTFilterType::lowpass
                       : ftype == 1 ? juce::dsp::StateVariableTPTFilterType::bandpass
                                    : juce::dsp::StateVariableTPTFilterType::highpass);
        v.filt.setResonance (0.707f + p[P_RESO] * 7.5f);

        const float velGain = 0.25f + 0.75f * v.vel;

        for (int i = 0; i < n; ++i)
        {
            const float aE = v.amp.getNextSample();
            if (! v.amp.isActive()) { v.active = false; break; }
            const float fE = v.flt.getNextSample();

            v.curFreq += (v.tgtFreq - v.curFreq) * gCoef;
            const double semis = (double) bend * 2.0 + (double) (lfoBuf[i] * p[P_LFOP]) + (double) v.pEnvVal;
            v.pEnvVal *= pDecCoef;
            const double f = v.curFreq * std::exp2 (semis / 12.0);

            float mod = 0.f;
            if (fmIdx > 0.001f)
            {
                v.phMod += f * (double) fmr * invSr;
                v.phMod -= std::floor (v.phMod);
                mod = std::sin (twoPi * (float) v.phMod) * fmIdx * fE;
            }

            float sL = 0.f, sR = 0.f;
            for (int u = 0; u < uni; ++u)
            {
                const float off = uni > 1 ? (2.f * (float) u / (float) (uni - 1) - 1.f) : 0.f;
                const double fi = f * std::exp2 ((double) (off * det) / 1200.0);
                const float dt = (float) (fi * invSr);

                v.ph1[u] += fi * invSr;
                v.ph1[u] -= std::floor (v.ph1[u]);
                float pp = (float) v.ph1[u] + mod / twoPi;
                pp -= std::floor (pp);
                float o = lvl1 * wave (w1, pp, dt);

                if (lvl2 > 0.001f)
                {
                    v.ph2[u] += fi * ratio2 * invSr;
                    v.ph2[u] -= std::floor (v.ph2[u]);
                    o += lvl2 * wave (w2, (float) v.ph2[u], dt * (float) ratio2);
                }

                const float pn = off * spread;
                sL += o * std::sqrt (0.5f * (1.f - pn));
                sR += o * std::sqrt (0.5f * (1.f + pn));
            }
            sL *= norm;
            sR *= norm;

            if (sub > 0.001f)
            {
                v.phSub += f * 0.5 * invSr;
                v.phSub -= std::floor (v.phSub);
                const float s = std::sin (twoPi * (float) v.phSub) * sub * 0.7f;
                sL += s; sR += s;
            }
            if (noiseLvl > 0.001f)
            {
                sL += (rng.nextFloat() * 2.f - 1.f) * noiseLvl * 0.5f;
                sR += (rng.nextFloat() * 2.f - 1.f) * noiseLvl * 0.5f;
            }

            const float oct = p[P_FENV] * fE * 5.f + lfoBuf[i] * p[P_LFOC] * 2.f;
            v.filt.setCutoffFrequency (juce::jlimit (20.f, maxCut, p[P_CUTOFF] * std::exp2 (oct)));
            const float yL = v.filt.processSample (0, sL);
            const float yR = v.filt.processSample (1, sR);

            const float g = aE * velGain * 0.5f;
            tmpL[i] += yL * g;
            tmpR[i] += yR * g;
        }
    }

    double sampleRate = 44100.0;
    std::array<Voice, 8> voices;
    unsigned long long orderCounter = 0;
    std::vector<int> heldNotes;
    bool monoActive = false;
    float bend = 0.f;
    float lfoPhase = 0.f;
    juce::Random rng;

    float tmpL[kChunk] {}, tmpR[kChunk] {}, lfoBuf[kChunk] {};

    juce::dsp::Chorus<float> chorus;
    juce::Reverb reverb;
    std::vector<float> dlBuf, drBuf;
    int delaySize = 0, wp = 0;
    float lpL = 0.f, lpR = 0.f;
};
