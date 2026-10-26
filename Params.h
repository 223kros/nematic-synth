#pragma once
#include <juce_audio_processors/juce_audio_processors.h>
#include <vector>
#include <cstring>

// X(enum, id, nombre, min, max, default, paso, skew)
#define NEM_PARAMS(X) \
    X(P_W1,    "w1",     "Osc1 Wave",   0.f,    3.f,     2.f,   1.f,   1.f)  \
    X(P_W2,    "w2",     "Osc2 Wave",   0.f,    3.f,     2.f,   1.f,   1.f)  \
    X(P_SEMI2, "semi2",  "Osc2 Semi",  -24.f,   24.f,    0.f,   1.f,   1.f)  \
    X(P_LVL1,  "lvl1",   "Osc1 Level",  0.f,    1.f,     1.f,   0.f,   1.f)  \
    X(P_LVL2,  "lvl2",   "Osc2 Level",  0.f,    1.f,     0.f,   0.f,   1.f)  \
    X(P_SUB,   "sub",    "Sub",         0.f,    1.f,     0.f,   0.f,   1.f)  \
    X(P_NOISE, "noise",  "Noise",       0.f,    1.f,     0.f,   0.f,   1.f)  \
    X(P_FM,    "fm",     "FM Amount",   0.f,    8.f,     0.f,   0.f,   1.f)  \
    X(P_FMR,   "fmr",    "FM Ratio",    0.25f,  12.f,    1.f,   0.f,   1.f)  \
    X(P_UNI,   "uni",    "Unison",      1.f,    7.f,     1.f,   1.f,   1.f)  \
    X(P_DET,   "det",    "Detune",      0.f,    60.f,    0.f,   0.f,   1.f)  \
    X(P_SPREAD,"spread", "Spread",      0.f,    1.f,     0.6f,  0.f,   1.f)  \
    X(P_CUTOFF,"cutoff", "Cutoff",      40.f,   18000.f, 18000.f,0.f,  0.3f) \
    X(P_RESO,  "reso",   "Resonance",   0.f,    1.f,     0.1f,  0.f,   1.f)  \
    X(P_FTYPE, "ftype",  "Filter Type", 0.f,    2.f,     0.f,   1.f,   1.f)  \
    X(P_FENV,  "fenv",   "Filter Env", -1.f,    1.f,     0.f,   0.f,   1.f)  \
    X(P_AA,    "aA",     "Attack",      0.001f, 8.f,     0.01f, 0.f,   0.35f)\
    X(P_AD,    "aD",     "Decay",       0.01f,  8.f,     0.3f,  0.f,   0.35f)\
    X(P_AS,    "aS",     "Sustain",     0.f,    1.f,     0.8f,  0.f,   1.f)  \
    X(P_AR,    "aR",     "Release",     0.01f,  10.f,    0.3f,  0.f,   0.35f)\
    X(P_FA,    "fA",     "Flt Attack",  0.001f, 8.f,     0.01f, 0.f,   0.35f)\
    X(P_FD,    "fD",     "Flt Decay",   0.01f,  8.f,     0.4f,  0.f,   0.35f)\
    X(P_FS,    "fS",     "Flt Sustain", 0.f,    1.f,     0.f,   0.f,   1.f)  \
    X(P_LFOR,  "lfoR",   "LFO Rate",    0.05f,  12.f,    4.f,   0.f,   0.4f) \
    X(P_LFOP,  "lfoP",   "LFO Pitch",   0.f,    1.f,     0.f,   0.f,   1.f)  \
    X(P_LFOC,  "lfoC",   "LFO Cutoff",  0.f,    1.f,     0.f,   0.f,   1.f)  \
    X(P_GLIDE, "glide",  "Glide",       0.f,    0.5f,    0.f,   0.f,   0.5f) \
    X(P_MONO,  "mono",   "Mono",        0.f,    1.f,     0.f,   1.f,   1.f)  \
    X(P_PENV,  "pEnv",   "Pitch Env",   0.f,    48.f,    0.f,   0.f,   1.f)  \
    X(P_PDEC,  "pDec",   "Pitch Decay", 0.005f, 1.f,     0.08f, 0.f,   0.4f) \
    X(P_DRIVE, "drive",  "Drive",       0.f,    1.f,     0.f,   0.f,   1.f)  \
    X(P_CHORUS,"chorus", "Chorus",      0.f,    1.f,     0.f,   0.f,   1.f)  \
    X(P_DMIX,  "dMix",   "Delay",       0.f,    1.f,     0.f,   0.f,   1.f)  \
    X(P_DTIME, "dTime",  "Delay Time",  50.f,   900.f,   375.f, 0.f,   1.f)  \
    X(P_DFB,   "dFb",    "Delay Fdbk",  0.f,    0.9f,    0.35f, 0.f,   1.f)  \
    X(P_VMIX,  "vMix",   "Reverb",      0.f,    1.f,     0.15f, 0.f,   1.f)  \
    X(P_VSIZE, "vSize",  "Reverb Size", 0.f,    1.f,     0.5f,  0.f,   1.f)  \
    X(P_VOL,   "vol",    "Volume",      0.f,    1.f,     0.7f,  0.f,   1.f)

enum ParamIdx
{
#define X(e, id, nm, mn, mx, df, st, sk) e,
    NEM_PARAMS(X)
#undef X
    P_COUNT
};

struct PDef { const char* id; const char* name; float mn, mx, def, step, skew; };

inline const std::vector<PDef>& paramDefs()
{
    static const std::vector<PDef> d = {
#define X(e, id, nm, mn, mx, df, st, sk) { id, nm, mn, mx, df, st, sk },
        NEM_PARAMS(X)
#undef X
    };
    return d;
}

inline int paramIndexOf (const char* id)
{
    const auto& d = paramDefs();
    for (size_t i = 0; i < d.size(); ++i)
        if (std::strcmp (d[i].id, id) == 0) return (int) i;
    return -1;
}
