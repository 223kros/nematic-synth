#pragma once
#include "Params.h"
#include <array>
#include <initializer_list>
#include <utility>

// Secciones: 0 = ATMOSFERA (ambient oscuro tipo Travis Scott), 1 = ROMANTICO (reggaeton romantico actual)
struct Preset
{
    const char* name;
    int section;
    const char* cat;
    std::array<float, P_COUNT> v;
};

inline Preset mk (int section, const char* cat, const char* name,
                  std::initializer_list<std::pair<const char*, float>> overrides)
{
    Preset p { name, section, cat, {} };
    const auto& defs = paramDefs();
    for (size_t i = 0; i < defs.size(); ++i) p.v[i] = defs[i].def;
    for (const auto& kv : overrides)
    {
        const int i = paramIndexOf (kv.first);
        jassert (i >= 0);
        if (i >= 0) p.v[(size_t) i] = kv.second;
    }
    return p;
}

inline const std::vector<Preset>& presets()
{
    // w: 0 sine, 1 triangle, 2 saw, 3 square.  ftype: 0 LP, 1 BP, 2 HP
    static const std::vector<Preset> list = {

        // =====================  SECCION 0 : ATMOSFERA  =====================
        // ---- PAD
        mk (0, "PAD", "Telekinesis Pad", { {"w1",2},{"w2",2},{"semi2",12},{"lvl2",0.4f},{"uni",5},{"det",22},{"spread",1},
            {"cutoff",1400},{"reso",0.15f},{"fenv",0.25f},{"fA",2.5f},{"fD",4},{"fS",0.6f},
            {"aA",1.6f},{"aD",2},{"aS",0.85f},{"aR",4.5f},{"lfoR",0.15f},{"lfoC",0.25f},
            {"chorus",0.5f},{"dMix",0.25f},{"dTime",480},{"dFb",0.5f},{"vMix",0.5f},{"vSize",0.85f},{"vol",0.6f} }),
        mk (0, "PAD", "My Eyes Haze", { {"w1",1},{"w2",2},{"semi2",-12},{"lvl2",0.5f},{"uni",4},{"det",14},{"spread",1},
            {"cutoff",900},{"reso",0.1f},{"aA",2.2f},{"aD",2},{"aS",0.9f},{"aR",5},{"lfoR",0.3f},{"lfoP",0.08f},
            {"chorus",0.6f},{"dMix",0.2f},{"dTime",520},{"vMix",0.6f},{"vSize",0.9f},{"vol",0.6f} }),
        mk (0, "PAD", "Utopia Choir", { {"w1",2},{"uni",6},{"det",18},{"spread",1},{"noise",0.08f},
            {"cutoff",900},{"reso",0.55f},{"ftype",1},{"aA",1.2f},{"aS",0.9f},{"aR",4},
            {"lfoR",5.2f},{"lfoP",0.12f},{"chorus",0.4f},{"vMix",0.55f},{"vSize",0.8f},{"vol",0.7f} }),
        mk (0, "PAD", "Nebula Drift", { {"w1",0},{"w2",1},{"semi2",19},{"lvl2",0.5f},{"sub",0.3f},{"uni",3},{"det",10},{"spread",1},
            {"cutoff",5000},{"lfoR",0.22f},{"lfoC",0.35f},{"aA",3.5f},{"aS",0.9f},{"aR",6},
            {"chorus",0.7f},{"dMix",0.35f},{"dTime",600},{"dFb",0.6f},{"vMix",0.65f},{"vSize",0.9f},{"vol",0.6f} }),
        mk (0, "PAD", "Cold Ether", { {"w1",2},{"uni",7},{"det",30},{"spread",1},{"noise",0.12f},
            {"cutoff",3200},{"reso",0.25f},{"aA",2.8f},{"aD",3},{"aS",0.7f},{"aR",6},{"lfoR",0.1f},{"lfoC",0.2f},
            {"chorus",0.6f},{"dMix",0.25f},{"dTime",450},{"vMix",0.75f},{"vSize",0.95f},{"vol",0.55f} }),
        mk (0, "PAD", "Dark Matter", { {"w1",2},{"w2",3},{"semi2",-12},{"lvl2",0.3f},{"sub",0.5f},{"uni",3},{"det",12},{"spread",0.9f},
            {"cutoff",500},{"reso",0.2f},{"fenv",0.3f},{"fA",3},{"fD",5},{"fS",0.5f},{"drive",0.15f},
            {"aA",1},{"aS",0.9f},{"aR",5},{"chorus",0.3f},{"vMix",0.6f},{"vSize",0.9f},{"vol",0.6f} }),

        // ---- BASS
        mk (0, "BASS", "Astro 808", { {"w1",0},{"cutoff",1200},{"reso",0.1f},{"pEnv",14},{"pDec",0.07f},
            {"aA",0.002f},{"aD",2.2f},{"aS",0},{"aR",0.25f},{"mono",1},{"glide",0.06f},{"drive",0.35f},{"vMix",0.05f},{"vol",0.75f} }),
        mk (0, "BASS", "Rage 808", { {"w1",0},{"w2",0},{"semi2",12},{"lvl2",0.15f},{"cutoff",2500},{"pEnv",18},{"pDec",0.06f},
            {"aA",0.002f},{"aD",1.6f},{"aS",0},{"aR",0.2f},{"mono",1},{"glide",0.09f},{"drive",0.7f},{"vMix",0.05f},{"vol",0.7f} }),
        mk (0, "BASS", "Sub Cloud", { {"w1",0},{"sub",0.6f},{"cutoff",400},{"aA",0.02f},{"aD",0.5f},{"aS",0.9f},{"aR",0.6f},
            {"mono",1},{"glide",0.04f},{"drive",0.1f},{"vMix",0.1f},{"vol",0.75f} }),
        mk (0, "BASS", "Dirty Growl", { {"w1",2},{"w2",3},{"semi2",-12},{"lvl2",0.5f},{"uni",2},{"det",8},{"cutoff",300},{"reso",0.35f},
            {"fenv",0.5f},{"fD",0.3f},{"fS",0.2f},{"drive",0.5f},{"aD",0.8f},{"aS",0.7f},{"aR",0.3f},{"mono",1},{"glide",0.03f},{"vMix",0.1f},{"vol",0.6f} }),

        // ---- SYNTH
        mk (0, "SYNTH", "Hyperspace Lead", { {"w1",2},{"w2",2},{"semi2",12},{"lvl2",0.3f},{"uni",3},{"det",14},{"cutoff",3800},{"fenv",0.2f},{"fD",0.5f},
            {"aA",0.02f},{"aS",0.8f},{"aR",1},{"lfoR",5.5f},{"lfoP",0.06f},{"mono",1},{"glide",0.05f},
            {"chorus",0.4f},{"dMix",0.35f},{"dTime",375},{"dFb",0.45f},{"vMix",0.4f},{"vSize",0.7f},{"vol",0.6f} }),
        mk (0, "SYNTH", "Neon Arp", { {"w1",3},{"uni",2},{"det",10},{"cutoff",1800},{"fenv",0.6f},{"fD",0.18f},{"fS",0.1f},
            {"aA",0.003f},{"aD",0.22f},{"aS",0.15f},{"aR",0.35f},{"chorus",0.3f},{"dMix",0.4f},{"dTime",280},{"dFb",0.5f},{"vMix",0.4f},{"vol",0.6f} }),
        mk (0, "SYNTH", "Glass Keys", { {"w1",1},{"w2",0},{"semi2",12},{"lvl2",0.5f},{"fm",0.6f},{"fmr",2},{"fD",0.5f},
            {"aD",1.2f},{"aS",0.2f},{"aR",1.4f},{"chorus",0.35f},{"vMix",0.5f},{"vSize",0.75f},{"vol",0.65f} }),
        mk (0, "SYNTH", "Wide Stack", { {"w1",2},{"uni",7},{"det",28},{"spread",1},{"cutoff",2400},{"reso",0.1f},
            {"aA",0.08f},{"aS",0.85f},{"aR",1.6f},{"chorus",0.5f},{"dMix",0.2f},{"vMix",0.45f},{"vSize",0.8f},{"vol",0.55f} }),
        mk (0, "SYNTH", "Dream Sweep", { {"w1",2},{"uni",5},{"det",20},{"spread",1},{"cutoff",300},{"fenv",0.9f},{"fA",2.5f},{"fD",3},{"fS",0.6f},
            {"aA",0.8f},{"aS",0.9f},{"aR",3},{"chorus",0.4f},{"dMix",0.3f},{"dTime",450},{"vMix",0.6f},{"vSize",0.85f},{"vol",0.6f} }),

        // ---- PLUCK
        mk (0, "PLUCK", "Echo Pluck", { {"w1",2},{"w2",1},{"semi2",12},{"lvl2",0.3f},{"uni",2},{"det",8},{"cutoff",500},{"fenv",0.65f},{"fD",0.22f},
            {"aD",0.5f},{"aS",0},{"aR",0.4f},{"chorus",0.2f},{"dMix",0.5f},{"dTime",420},{"dFb",0.55f},{"vMix",0.45f},{"vSize",0.8f},{"vol",0.65f} }),
        mk (0, "PLUCK", "Dark Kalimba", { {"w1",0},{"fm",2.5f},{"fmr",4},{"fA",0.001f},{"fD",0.18f},{"fS",0},
            {"aD",0.9f},{"aS",0},{"aR",0.6f},{"dMix",0.35f},{"dTime",375},{"vMix",0.5f},{"vSize",0.8f},{"vol",0.65f} }),
        mk (0, "PLUCK", "Soft Harp", { {"w1",1},{"w2",0},{"semi2",12},{"lvl2",0.6f},{"cutoff",3000},{"fenv",0.3f},{"fD",0.5f},
            {"aD",1.4f},{"aS",0},{"aR",1.2f},{"chorus",0.3f},{"vMix",0.6f},{"vSize",0.85f},{"vol",0.65f} }),
        mk (0, "PLUCK", "Lo-Fi Strum", { {"w1",2},{"uni",3},{"det",12},{"noise",0.02f},{"cutoff",700},{"reso",0.2f},{"fenv",0.5f},{"fD",0.15f},
            {"aD",0.35f},{"aS",0},{"aR",0.3f},{"lfoR",0.8f},{"lfoP",0.05f},{"chorus",0.5f},{"vMix",0.35f},{"vol",0.65f} }),

        // ---- BELL
        mk (0, "BELL", "Ice Bell", { {"w1",0},{"fm",2.5f},{"fmr",3.5f},{"fD",1.5f},{"fS",0},
            {"aD",3},{"aS",0},{"aR",3},{"dMix",0.3f},{"dTime",500},{"vMix",0.6f},{"vSize",0.9f},{"vol",0.6f} }),
        mk (0, "BELL", "Moonlight Chime", { {"w1",0},{"w2",0},{"semi2",19},{"lvl2",0.4f},{"fm",1.2f},{"fmr",5.07f},{"fD",2},{"fS",0},
            {"aD",4},{"aS",0},{"aR",4},{"dMix",0.4f},{"dTime",520},{"dFb",0.5f},{"vMix",0.7f},{"vSize",0.95f},{"vol",0.55f} }),
        mk (0, "BELL", "Dream Glock", { {"w1",1},{"fm",1.5f},{"fmr",4},{"fD",0.6f},{"fS",0},
            {"aD",1.4f},{"aS",0},{"aR",1.4f},{"chorus",0.25f},{"vMix",0.5f},{"vSize",0.8f},{"vol",0.6f} }),
        mk (0, "BELL", "Cathedral Bell", { {"w1",0},{"sub",0.1f},{"fm",4},{"fmr",1.41f},{"fD",2.5f},{"fS",0},
            {"aD",6},{"aS",0},{"aR",6},{"vMix",0.8f},{"vSize",0.97f},{"vol",0.55f} }),
        mk (0, "BELL", "Star Dust", { {"w1",0},{"uni",3},{"det",6},{"spread",1},{"fm",0.8f},{"fmr",7},{"fD",0.4f},{"fS",0},
            {"aA",0.01f},{"aD",2.5f},{"aS",0},{"aR",3},{"chorus",0.5f},{"dMix",0.45f},{"dTime",520},{"dFb",0.55f},{"vMix",0.65f},{"vSize",0.9f},{"vol",0.55f} }),

        // ---- TEXTURE
        mk (0, "TEXTURE", "Black Hole Noise", { {"lvl1",0},{"noise",0.7f},{"ftype",1},{"cutoff",600},{"reso",0.6f},{"lfoR",0.08f},{"lfoC",0.5f},
            {"aA",3},{"aS",1},{"aR",6},{"vMix",0.8f},{"vSize",0.95f},{"vol",0.95f} }),
        mk (0, "TEXTURE", "Wind Tunnel", { {"lvl1",0},{"noise",0.8f},{"ftype",1},{"cutoff",1500},{"reso",0.3f},{"lfoR",0.15f},{"lfoC",0.4f},
            {"aA",2.5f},{"aS",1},{"aR",5},{"chorus",0.5f},{"vMix",0.7f},{"vSize",0.9f},{"vol",0.95f} }),
        mk (0, "TEXTURE", "Tape Air", { {"lvl1",0},{"noise",0.15f},{"ftype",2},{"cutoff",4000},{"aA",0.5f},{"aS",1},{"aR",1},{"vMix",0.1f},{"vol",0.95f} }),
        mk (0, "TEXTURE", "Ghost Drone", { {"w1",2},{"uni",7},{"det",40},{"spread",1},{"cutoff",350},{"lfoR",0.07f},{"lfoC",0.4f},{"drive",0.1f},
            {"aA",5},{"aS",1},{"aR",8},{"chorus",0.7f},{"dMix",0.3f},{"dTime",600},{"vMix",0.9f},{"vSize",0.98f},{"vol",0.95f} }),

        // =====================  SECCION 1 : ROMANTICO  =====================
        // ---- PAD
        mk (1, "PAD", "Saiko Pad", { {"w1",2},{"w2",1},{"lvl2",0.5f},{"uni",4},{"det",12},{"spread",1},{"cutoff",2200},{"fenv",0.2f},{"fA",0.6f},{"fD",1.5f},{"fS",0.7f},
            {"aA",0.5f},{"aD",1},{"aS",0.85f},{"aR",1.6f},{"chorus",0.5f},{"dMix",0.15f},{"dTime",333},{"vMix",0.35f},{"vSize",0.7f},{"vol",0.6f} }),
        mk (1, "PAD", "Mora Haze", { {"w1",1},{"w2",0},{"lvl2",0.5f},{"uni",3},{"det",9},{"spread",1},{"cutoff",1800},
            {"aA",0.9f},{"aS",0.9f},{"aR",2.2f},{"lfoR",0.4f},{"lfoP",0.05f},{"chorus",0.55f},{"dMix",0.2f},{"dTime",333},{"vMix",0.45f},{"vSize",0.8f},{"vol",0.6f} }),
        mk (1, "PAD", "Tainy Air", { {"w1",2},{"noise",0.04f},{"uni",5},{"det",16},{"spread",1},{"cutoff",3500},
            {"aA",0.7f},{"aS",0.9f},{"aR",2.4f},{"chorus",0.4f},{"vMix",0.5f},{"vSize",0.75f},{"vol",0.55f} }),
        mk (1, "PAD", "Velvet Choir", { {"w1",2},{"uni",5},{"det",14},{"spread",1},{"noise",0.05f},{"ftype",1},{"cutoff",1100},{"reso",0.4f},
            {"aA",0.6f},{"aS",0.9f},{"aR",1.8f},{"lfoR",5},{"lfoP",0.1f},{"chorus",0.4f},{"vMix",0.45f},{"vol",0.65f} }),

        // ---- BASS (808 con slide)
        mk (1, "BASS", "808 Romance", { {"w1",0},{"cutoff",900},{"pEnv",6},{"pDec",0.05f},{"aA",0.002f},{"aD",2},{"aS",0},{"aR",0.25f},
            {"mono",1},{"glide",0.07f},{"drive",0.25f},{"vMix",0},{"vol",0.75f} }),
        mk (1, "BASS", "Perreo Sub", { {"w1",0},{"w2",1},{"semi2",12},{"lvl2",0.12f},{"cutoff",1400},{"pEnv",5},{"pDec",0.04f},
            {"aA",0.002f},{"aD",1.2f},{"aS",0.2f},{"aR",0.25f},{"mono",1},{"glide",0.05f},{"drive",0.3f},{"vMix",0},{"vol",0.75f} }),
        mk (1, "BASS", "Slide 808", { {"w1",0},{"cutoff",1100},{"pEnv",10},{"pDec",0.05f},{"aA",0.002f},{"aD",2.4f},{"aS",0},{"aR",0.3f},
            {"mono",1},{"glide",0.15f},{"drive",0.4f},{"vMix",0},{"vol",0.75f} }),
        mk (1, "BASS", "Soft Sub", { {"w1",0},{"cutoff",350},{"aA",0.005f},{"aD",0.6f},{"aS",0.8f},{"aR",0.3f},
            {"mono",1},{"glide",0.03f},{"drive",0.05f},{"vMix",0},{"vol",0.8f} }),
        mk (1, "BASS", "Boom Warm", { {"w1",1},{"sub",0.4f},{"cutoff",700},{"pEnv",7},{"pDec",0.06f},{"aA",0.003f},{"aD",1.4f},{"aS",0.1f},{"aR",0.25f},
            {"mono",1},{"glide",0.06f},{"drive",0.35f},{"vMix",0},{"vol",0.7f} }),

        // ---- SYNTH / LEAD
        mk (1, "SYNTH", "Mora Lead", { {"w1",2},{"w2",1},{"semi2",12},{"lvl2",0.25f},{"uni",3},{"det",10},{"cutoff",2800},{"reso",0.12f},{"fenv",0.15f},
            {"aA",0.01f},{"aS",0.8f},{"aR",0.6f},{"lfoR",5.2f},{"lfoP",0.07f},{"mono",1},{"glide",0.05f},
            {"chorus",0.3f},{"dMix",0.35f},{"dTime",500},{"vMix",0.3f},{"vol",0.6f} }),
        mk (1, "SYNTH", "Soft Lead", { {"w1",1},{"w2",0},{"lvl2",0.4f},{"cutoff",4000},{"aA",0.02f},{"aS",0.85f},{"aR",0.5f},
            {"lfoR",5},{"lfoP",0.05f},{"mono",1},{"glide",0.04f},{"chorus",0.3f},{"dMix",0.3f},{"dTime",333},{"vMix",0.3f},{"vol",0.65f} }),
        mk (1, "SYNTH", "Saiko Whistle", { {"w1",0},{"w2",0},{"semi2",12},{"lvl2",0.2f},{"fm",0.3f},{"fmr",2},{"fS",0.5f},
            {"aA",0.04f},{"aS",0.85f},{"aR",0.5f},{"lfoR",5.5f},{"lfoP",0.15f},{"mono",1},{"glide",0.06f},
            {"chorus",0.2f},{"dMix",0.35f},{"dTime",500},{"vMix",0.3f},{"vol",0.6f} }),
        mk (1, "SYNTH", "Tainy Pluck Lead", { {"w1",2},{"uni",2},{"det",8},{"cutoff",900},{"fenv",0.5f},{"fD",0.3f},{"fS",0.3f},
            {"aA",0.005f},{"aD",0.5f},{"aS",0.5f},{"aR",0.4f},{"dMix",0.3f},{"dTime",500},{"vMix",0.3f},{"vol",0.6f} }),
        mk (1, "SYNTH", "Glide Synth", { {"w1",2},{"w2",3},{"semi2",-12},{"lvl2",0.3f},{"cutoff",2000},{"reso",0.2f},
            {"aA",0.01f},{"aS",0.8f},{"aR",0.5f},{"mono",1},{"glide",0.1f},{"chorus",0.4f},{"vMix",0.3f},{"vol",0.6f} }),

        // ---- PLUCK (guitarra / marimba)
        mk (1, "PLUCK", "Nylon Pluck", { {"w1",1},{"w2",2},{"semi2",12},{"lvl2",0.15f},{"cutoff",700},{"reso",0.1f},{"fenv",0.6f},{"fD",0.25f},
            {"aA",0.002f},{"aD",0.7f},{"aS",0},{"aR",0.5f},{"chorus",0.15f},{"dMix",0.2f},{"dTime",333},{"vMix",0.25f},{"vSize",0.55f},{"vol",0.65f} }),
        mk (1, "PLUCK", "Marimba Soft", { {"w1",0},{"w2",0},{"semi2",12},{"lvl2",0.2f},{"fm",1.8f},{"fmr",4},{"fD",0.12f},{"fS",0},
            {"aD",0.55f},{"aS",0},{"aR",0.35f},{"dMix",0.2f},{"dTime",333},{"vMix",0.25f},{"vol",0.65f} }),
        mk (1, "PLUCK", "Kalimba Love", { {"w1",0},{"fm",2},{"fmr",3},{"fD",0.22f},{"fS",0},
            {"aD",1.1f},{"aS",0},{"aR",0.8f},{"dMix",0.3f},{"dTime",333},{"vMix",0.35f},{"vol",0.65f} }),
        mk (1, "PLUCK", "Muted Guitar", { {"w1",2},{"uni",2},{"det",6},{"cutoff",600},{"fenv",0.5f},{"fD",0.18f},
            {"aD",0.3f},{"aS",0},{"aR",0.2f},{"drive",0.1f},{"chorus",0.2f},{"vMix",0.2f},{"vol",0.65f} }),
        mk (1, "PLUCK", "Harp Glow", { {"w1",1},{"w2",0},{"semi2",12},{"lvl2",0.5f},{"cutoff",3500},{"fenv",0.25f},{"fD",0.5f},
            {"aD",1.2f},{"aS",0},{"aR",1},{"chorus",0.3f},{"dMix",0.3f},{"dTime",500},{"vMix",0.45f},{"vol",0.65f} }),

        // ---- BELL
        mk (1, "BELL", "Candy Bell", { {"w1",0},{"fm",1.6f},{"fmr",3.5f},{"fD",0.9f},{"fS",0},
            {"aD",1.8f},{"aS",0},{"aR",1.6f},{"dMix",0.3f},{"dTime",333},{"vMix",0.35f},{"vol",0.6f} }),
        mk (1, "BELL", "Soft Glock", { {"w1",1},{"w2",0},{"semi2",24},{"lvl2",0.3f},{"fm",0.6f},{"fmr",4},{"fD",0.5f},{"fS",0},
            {"aD",1},{"aS",0},{"aR",0.9f},{"vMix",0.3f},{"vol",0.6f} }),
        mk (1, "BELL", "Heart Chime", { {"w1",0},{"w2",0},{"semi2",19},{"lvl2",0.4f},
            {"aD",2.2f},{"aS",0},{"aR",2},{"chorus",0.2f},{"dMix",0.3f},{"dTime",500},{"vMix",0.45f},{"vol",0.6f} }),
        mk (1, "BELL", "Music Box", { {"w1",0},{"fm",1.2f},{"fmr",6},{"fD",0.3f},{"fS",0},
            {"aD",0.9f},{"aS",0},{"aR",0.7f},{"dMix",0.25f},{"dTime",500},{"vMix",0.3f},{"vol",0.6f} }),

        // ---- KEYS
        mk (1, "KEYS", "Rhodes Love", { {"w1",0},{"w2",0},{"semi2",12},{"lvl2",0.15f},{"fm",1.3f},{"fmr",1},{"fA",0.001f},{"fD",0.6f},{"fS",0.1f},
            {"aA",0.003f},{"aD",1.8f},{"aS",0.25f},{"aR",0.5f},{"drive",0.08f},{"chorus",0.55f},{"vMix",0.3f},{"vol",0.65f} }),
        mk (1, "KEYS", "Soft Piano", { {"w1",1},{"w2",2},{"lvl2",0.1f},{"fm",0.5f},{"fmr",3},{"fD",0.08f},{"fS",0},{"cutoff",3000},
            {"aA",0.002f},{"aD",1.5f},{"aS",0.1f},{"aR",0.5f},{"vMix",0.25f},{"vol",0.65f} }),
        mk (1, "KEYS", "Wurli Night", { {"w1",1},{"w2",3},{"semi2",12},{"lvl2",0.15f},{"cutoff",1800},{"fenv",0.2f},{"fD",0.5f},{"drive",0.15f},
            {"aA",0.003f},{"aD",1.2f},{"aS",0.3f},{"aR",0.4f},{"chorus",0.4f},{"vMix",0.3f},{"vol",0.65f} }),
        mk (1, "KEYS", "Dreamy EP", { {"w1",0},{"w2",1},{"lvl2",0.3f},{"fm",0.9f},{"fmr",1},{"fA",0.001f},{"fD",1},{"fS",0.15f},
            {"aD",2},{"aS",0.4f},{"aR",0.8f},{"chorus",0.7f},{"dMix",0.3f},{"dTime",500},{"vMix",0.45f},{"vol",0.65f} }),
    };
    return list;
}

inline juce::StringArray categoriesFor (int section)
{
    juce::StringArray c;
    for (const auto& p : presets())
        if (p.section == section) c.addIfNotAlreadyThere (p.cat);
    return c;
}
