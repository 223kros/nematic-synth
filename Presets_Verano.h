// VERANO: calido, tropical, soleado, con aire de playa (estilo "Un Verano Sin Ti" y reggaeton de verano)
inline void addVeranoPresets (std::vector<Preset>& L)
{
#define ADD(cat, name, ...) L.push_back (mk (2, cat, name, { __VA_ARGS__ }))

    // ---------------------------------------------------------------- PAD
    ADD ("PAD", "Sunset Beach Pad", {"w1",2}, {"w2",1}, {"semi2",12}, {"lvl2",0.35f}, UNI(5,14), FLT(3000,0.08f), ENV(1,1,0.9f,2.5f), {"chorus",0.55f}, DLY(0.2f,333,0.4f), RV(0.55f,0.85f), {"vol",0.58f});
    ADD ("PAD", "Golden Hour", {"w1",1}, {"w2",2}, {"lvl2",0.3f}, UNI(4,12), FLT(2400,0.08f), FEN(0.3f,0.8f,2,0.6f), ENV(1.2f,1,0.9f,2.8f), {"lfoR",0.25f}, {"lfoC",0.2f}, {"chorus",0.6f}, RV(0.5f,0.82f), {"vol",0.6f});
    ADD ("PAD", "Ocean Breeze", {"w1",0}, {"w2",1}, {"semi2",12}, {"lvl2",0.5f}, UNI(4,10), FLT(5000,0.05f), ENV(1.5f,1,0.9f,3), {"noise",0.04f}, {"lfoR",0.2f}, {"lfoC",0.25f}, {"chorus",0.6f}, DLY(0.25f,375,0.45f), RV(0.6f,0.88f), {"vol",0.58f});
    ADD ("PAD", "Palm Haze", {"w1",2}, UNI(6,16), FLT(2000,0.1f), ENV(1.4f,1,0.9f,3), {"lfoR",0.18f}, {"lfoC",0.3f}, {"chorus",0.55f}, RV(0.6f,0.88f), {"vol",0.56f});
    ADD ("PAD", "Coral Dream", {"w1",1}, {"w2",0}, {"semi2",19}, {"lvl2",0.35f}, UNI(3,9), FLT(3800,0.06f), ENV(1,1,0.9f,2.5f), {"lfoR",0.3f}, {"lfoP",0.04f}, {"chorus",0.65f}, DLY(0.3f,420,0.5f), RV(0.6f,0.9f), {"vol",0.6f});
    ADD ("PAD", "Salty Air", {"w1",2}, {"noise",0.08f}, UNI(5,18), FLT(4200,0.08f), ENV(1.2f,1,0.85f,2.5f), {"lofi",0.12f}, {"chorus",0.4f}, RV(0.55f,0.85f), {"vol",0.56f});
    ADD ("PAD", "Warm Tide", {"w1",2}, {"w2",1}, {"semi2",-12}, {"lvl2",0.45f}, UNI(4,12), FLT(1500,0.1f), FEN(0.25f,1,2,0.7f), ENV(1,1,0.9f,2.5f), {"chorus",0.5f}, RV(0.5f,0.82f), {"vol",0.6f});
    ADD ("PAD", "Neon Palm", {"w1",2}, {"w2",2}, {"semi2",7}, {"lvl2",0.3f}, UNI(6,18), FLT(2600,0.12f), FEN(0.3f,1,2,0.6f), ENV(1.5f,1,0.9f,3), {"lfoR",0.2f}, {"lfoC",0.3f}, {"chorus",0.6f}, DLY(0.25f,333,0.45f), RV(0.6f,0.88f), {"vol",0.55f});

    // ---------------------------------------------------------------- BASS
    ADD ("BASS", "Moscow Sub", {"w1",0}, {"sub",0.1f}, FLT(800,0.05f), {"pEnv",6}, {"pDec",0.05f}, ENV(0.002f,2.2f,0,0.25f), {"mono",1}, {"glide",0.08f}, {"drive",0.22f}, {"vol",0.75f});
    ADD ("BASS", "Dembow 808", {"w1",0}, FLT(1000,0.05f), {"pEnv",8}, {"pDec",0.045f}, ENV(0.002f,1,0.05f,0.2f), {"mono",1}, {"glide",0.04f}, {"drive",0.3f}, {"vol",0.75f});
    ADD ("BASS", "Island Bass", {"w1",1}, {"w2",0}, {"semi2",-12}, {"lvl2",0.5f}, FLT(600,0.1f), FEN(0.3f,0.003f,0.2f,0.3f), ENV(0.004f,0.5f,0.6f,0.25f), {"mono",1}, {"glide",0.03f}, {"drive",0.12f}, {"vol",0.75f});
    ADD ("BASS", "Reggae Sub", {"w1",0}, {"sub",0.2f}, FLT(350,0), ENV(0.005f,0.5f,0.7f,0.3f), {"mono",1}, {"glide",0.02f}, {"drive",0.1f}, {"vol",0.8f});
    ADD ("BASS", "Sunny 808 Slide", {"w1",0}, FLT(950,0.05f), {"pEnv",9}, {"pDec",0.05f}, ENV(0.002f,2.8f,0,0.3f), {"mono",1}, {"glide",0.2f}, {"drive",0.3f}, {"vol",0.75f});
    ADD ("BASS", "Warm Pluck Bass", {"w1",2}, {"w2",1}, {"semi2",-12}, {"lvl2",0.5f}, FLT(500,0.15f), FEN(0.6f,0.002f,0.15f,0.1f), ENV(0.002f,0.35f,0.15f,0.2f), {"mono",1}, {"glide",0.03f}, {"drive",0.15f}, {"vol",0.7f});
    ADD ("BASS", "Beach Boom", {"w1",0}, {"sub",0.15f}, FLT(1100,0), {"pEnv",12}, {"pDec",0.06f}, ENV(0.002f,1.6f,0,0.25f), {"mono",1}, {"glide",0.05f}, {"drive",0.35f}, {"vol",0.75f});
    ADD ("BASS", "Funk Sub", {"w1",1}, {"sub",0.4f}, FLT(550,0.15f), FEN(0.35f,0.003f,0.12f,0.2f), ENV(0.003f,0.3f,0.4f,0.15f), {"mono",1}, {"glide",0.03f}, {"drive",0.15f}, {"vol",0.75f});

    // ---------------------------------------------------------------- SYNTH
    ADD ("SYNTH", "Summer Lead", {"w1",2}, {"w2",1}, {"semi2",12}, {"lvl2",0.15f}, {"uni",2}, {"det",9}, FLT(4000,0.1f), ENV(0.015f,0.4f,0.85f,0.5f), {"lfoR",5.3f}, {"lfoP",0.06f}, {"mono",1}, {"glide",0.05f}, {"chorus",0.3f}, DLY(0.3f,333,0.4f), RV(0.35f,0.7f), {"vol",0.6f});
    ADD ("SYNTH", "Tropical Whistle", {"w1",0}, {"w2",0}, {"semi2",12}, {"lvl2",0.2f}, ENV(0.03f,0.4f,0.9f,0.5f), {"lfoR",5.6f}, {"lfoP",0.15f}, {"mono",1}, {"glide",0.07f}, DLY(0.3f,500,0.4f), RV(0.3f,0.7f), {"vol",0.62f});
    ADD ("SYNTH", "Brass Stab Sun", {"w1",2}, {"w2",2}, {"semi2",0}, {"lvl2",0.5f}, {"det",12}, {"uni",3}, FLT(1200,0.1f), FEN(0.6f,0.03f,0.3f,0.5f), ENV(0.02f,0.3f,0.6f,0.35f), RV(0.3f,0.65f), {"vol",0.58f});
    ADD ("SYNTH", "Breeze Flute", {"w1",0}, {"noise",0.1f}, {"w2",1}, {"semi2",12}, {"lvl2",0.12f}, ENV(0.07f,0.4f,0.85f,0.5f), {"lfoR",5}, {"lfoP",0.07f}, {"mono",1}, {"glide",0.06f}, DLY(0.25f,375,0.4f), RV(0.4f,0.75f), {"vol",0.65f});
    ADD ("SYNTH", "Reggaeton Saw", {"w1",2}, {"w2",3}, {"semi2",-12}, {"lvl2",0.2f}, {"uni",2}, {"det",10}, FLT(1800,0.15f), FEN(0.4f,0.004f,0.3f,0.25f), ENV(0.005f,0.35f,0.4f,0.35f), {"chorus",0.35f}, DLY(0.25f,333,0.4f), RV(0.35f,0.7f), {"vol",0.6f});
    ADD ("SYNTH", "Horn Pad Bright", {"w1",2}, UNI(4,12), FLT(2200,0.1f), FEN(0.4f,0.12f,0.5f,0.7f), ENV(0.12f,0.5f,0.85f,0.9f), {"lfoR",5}, {"lfoP",0.04f}, {"chorus",0.3f}, RV(0.4f,0.75f), {"vol",0.58f});
    ADD ("SYNTH", "Moscow Lead", {"w1",1}, {"w2",2}, {"semi2",12}, {"lvl2",0.12f}, FLT(3600,0.1f), ENV(0.02f,0.4f,0.8f,0.6f), {"lfoR",5}, {"lfoP",0.07f}, {"mono",1}, {"glide",0.08f}, {"chorus",0.35f}, DLY(0.35f,375,0.45f), RV(0.4f,0.75f), {"vol",0.62f});
    ADD ("SYNTH", "Sunny Stab", {"w1",2}, {"w2",1}, {"semi2",12}, {"lvl2",0.3f}, {"uni",2}, {"det",8}, FLT(2400,0.1f), FEN(0.4f,0.003f,0.22f,0.15f), ENV(0.004f,0.3f,0.2f,0.4f), {"chorus",0.3f}, DLY(0.25f,333,0.4f), RV(0.35f,0.7f), {"vol",0.6f});

    // ---------------------------------------------------------------- PLUCK
    ADD ("PLUCK", "Beach Guitar", {"w1",1}, {"w2",2}, {"semi2",12}, {"lvl2",0.13f}, FLT(900,0.1f), FEN(0.6f,0.002f,0.22f,0.05f), ENV(0.002f,0.9f,0,0.5f), {"chorus",0.15f}, DLY(0.2f,333,0.35f), RV(0.3f,0.65f), {"vol",0.65f});
    ADD ("PLUCK", "Nylon Sol", {"w1",1}, {"w2",2}, {"semi2",12}, {"lvl2",0.1f}, FLT(1000,0.08f), FEN(0.55f,0.002f,0.25f,0.05f), ENV(0.002f,1.1f,0,0.6f), {"chorus",0.12f}, RV(0.3f,0.65f), {"vol",0.65f});
    ADD ("PLUCK", "Bright Strum", {"w1",2}, {"uni",3}, {"det",10}, FLT(1200,0.12f), FEN(0.55f,0.002f,0.2f,0.05f), ENV(0.003f,0.6f,0,0.4f), {"chorus",0.25f}, DLY(0.2f,333,0.35f), RV(0.3f,0.65f), {"vol",0.62f});
    ADD ("PLUCK", "Cuatro Pluck", {"w1",2}, {"w2",1}, {"semi2",12}, {"lvl2",0.3f}, FLT(1500,0.15f), FEN(0.5f,0.001f,0.14f,0.05f), ENV(0.001f,0.4f,0,0.3f), DLY(0.2f,333,0.35f), RV(0.3f,0.65f), {"vol",0.65f});
    ADD ("PLUCK", "Tres Pluck", {"w1",1}, {"w2",3}, {"semi2",12}, {"lvl2",0.12f}, FLT(1300,0.1f), FEN(0.5f,0.001f,0.16f,0.05f), ENV(0.001f,0.5f,0,0.35f), {"chorus",0.2f}, RV(0.3f,0.65f), {"vol",0.65f});
    ADD ("PLUCK", "Palm Harp", {"w1",1}, {"w2",0}, {"semi2",12}, {"lvl2",0.5f}, FLT(3500,0.05f), ENV(0.002f,1.4f,0,1), {"chorus",0.3f}, DLY(0.3f,500,0.45f), RV(0.45f,0.8f), {"vol",0.62f});
    ADD ("PLUCK", "Sunny Pluck", {"w1",0}, {"w2",2}, {"semi2",12}, {"lvl2",0.12f}, FLT(2400,0.05f), ENV(0.001f,0.3f,0,0.25f), RV(0.3f,0.6f), {"vol",0.65f});
    ADD ("PLUCK", "Sand Pluck Lo-Fi", {"w1",1}, {"w2",2}, {"semi2",12}, {"lvl2",0.12f}, FLT(750,0.1f), FEN(0.5f,0.002f,0.2f,0.05f), ENV(0.002f,0.6f,0,0.4f), {"lofi",0.3f}, {"chorus",0.3f}, RV(0.3f,0.65f), {"vol",0.65f});

    // ---------------------------------------------------------------- BELL
    ADD ("BELL", "Sun Bell", {"w1",0}, {"fm",1.5f}, {"fmr",3.5f}, ENV(0.001f,2,0,1.8f), DLY(0.3f,333,0.4f), RV(0.4f,0.75f), {"vol",0.6f});
    ADD ("BELL", "Coconut Chime", {"w1",0}, {"fm",2}, {"fmr",2.3f}, ENV(0.001f,0.8f,0,0.6f), RV(0.35f,0.7f), {"vol",0.6f});
    ADD ("BELL", "Seashell Bell", {"w1",1}, {"w2",0}, {"semi2",19}, {"lvl2",0.35f}, {"fm",0.8f}, {"fmr",4}, ENV(0.001f,1.8f,0,1.6f), {"chorus",0.25f}, DLY(0.3f,420,0.4f), RV(0.45f,0.8f), {"vol",0.58f});
    ADD ("BELL", "Cowbell Soft", {"w1",3}, {"w2",3}, {"semi2",7}, {"lvl2",0.8f}, {"ftype",1}, FLT(900,0.4f), ENV(0.001f,0.25f,0,0.18f), RV(0.2f,0.5f), {"vol",0.6f});

    // ---------------------------------------------------------------- KEYS
    ADD ("KEYS", "Skank Organ", {"w1",3}, {"w2",1}, {"semi2",12}, {"lvl2",0.4f}, FLT(2000,0.1f), ENV(0.003f,0.2f,0.8f,0.08f), {"chorus",0.3f}, RV(0.25f,0.6f), {"vol",0.55f});
    ADD ("KEYS", "Beach Rhodes", {"w1",0}, {"w2",0}, {"semi2",12}, {"lvl2",0.14f}, {"fm",1.2f}, {"fmr",1}, FEN(0,0.001f,0.6f,0.1f), ENV(0.003f,1.8f,0.3f,0.5f), {"drive",0.08f}, {"chorus",0.55f}, RV(0.3f,0.7f), {"vol",0.65f});
    ADD ("KEYS", "Sunny Piano", {"w1",2}, {"w2",1}, {"semi2",12}, {"lvl2",0.2f}, {"fm",0.6f}, {"fmr",2}, FLT(4000,0.05f), ENV(0.002f,1.4f,0.1f,0.5f), RV(0.3f,0.65f), {"vol",0.62f});
    ADD ("KEYS", "Wurli Summer", {"w1",1}, {"w2",3}, {"semi2",12}, {"lvl2",0.14f}, FLT(1900,0.1f), ENV(0.003f,1.2f,0.3f,0.4f), {"drive",0.12f}, {"chorus",0.4f}, RV(0.3f,0.65f), {"vol",0.65f});
    ADD ("KEYS", "Reggae Piano", {"w1",1}, {"w2",2}, {"lvl2",0.1f}, {"fm",0.5f}, {"fmr",3}, FLT(2800,0.05f), ENV(0.002f,0.35f,0.05f,0.15f), RV(0.25f,0.6f), {"vol",0.65f});
    ADD ("KEYS", "Lounge Organ", {"w1",0}, {"w2",1}, {"semi2",12}, {"lvl2",0.5f}, {"sub",0.2f}, FLT(2600,0.05f), ENV(0.02f,0.4f,0.95f,0.4f), {"lfoR",6}, {"lfoA",0.12f}, {"chorus",0.4f}, RV(0.4f,0.75f), {"vol",0.58f});

    // ---------------------------------------------------------------- MALLET
    ADD ("MALLET", "Beach Marimba", {"w1",0}, {"fm",1.6f}, {"fmr",4}, FEN(0,0.001f,0.1f,0), ENV(0.001f,0.55f,0,0.35f), DLY(0.2f,333,0.35f), RV(0.3f,0.65f), {"vol",0.65f});
    ADD ("MALLET", "Steel Drum Sun", {"w1",0}, {"w2",0}, {"semi2",12}, {"lvl2",0.3f}, {"fm",1.3f}, {"fmr",1.5f}, ENV(0.002f,0.85f,0,0.65f), {"chorus",0.25f}, DLY(0.2f,333,0.35f), RV(0.3f,0.65f), {"vol",0.62f});
    ADD ("MALLET", "Vibes Warm", {"w1",0}, {"fm",0.8f}, {"fmr",4}, ENV(0.002f,2,0,1.2f), {"lfoR",5}, {"lfoA",0.35f}, RV(0.35f,0.7f), {"vol",0.62f});
    ADD ("MALLET", "Kalimba Sol", {"w1",0}, {"fm",2}, {"fmr",3}, FEN(0,0.001f,0.2f,0), ENV(0.001f,1,0,0.8f), DLY(0.3f,333,0.4f), RV(0.35f,0.7f), {"vol",0.65f});
    ADD ("MALLET", "Xylophone Bright", {"w1",1}, {"w2",0}, {"semi2",19}, {"lvl2",0.3f}, {"fm",0.9f}, {"fmr",6}, ENV(0.001f,0.3f,0,0.25f), RV(0.3f,0.65f), {"vol",0.62f});
    ADD ("MALLET", "Steel Pan Duo", {"w1",0}, {"w2",0}, {"semi2",7}, {"lvl2",0.3f}, {"fm",1.6f}, {"fmr",1.5f}, {"uni",2}, {"det",7}, ENV(0.002f,0.7f,0,0.5f), {"chorus",0.3f}, RV(0.3f,0.65f), {"vol",0.6f});
    ADD ("MALLET", "Wood Marimba Deep", {"w1",0}, {"w2",1}, {"semi2",-12}, {"lvl2",0.3f}, {"fm",1.8f}, {"fmr",4}, FEN(0,0.001f,0.1f,0), ENV(0.001f,0.6f,0,0.4f), FLT(2200,0.05f), RV(0.3f,0.65f), {"vol",0.68f});
    ADD ("MALLET", "Music Box Tropical", {"w1",0}, {"fm",1.2f}, {"fmr",6}, ENV(0.001f,0.9f,0,0.7f), DLY(0.25f,500,0.4f), RV(0.35f,0.7f), {"vol",0.6f});

    // ---------------------------------------------------------------- STRINGS
    ADD ("STRINGS", "Sun Strings", {"w1",2}, UNI(5,11), FLT(2800,0.08f), ENV(0.5f,1,0.9f,1.6f), {"lfoR",5.2f}, {"lfoP",0.04f}, {"chorus",0.45f}, RV(0.45f,0.78f), {"vol",0.6f});
    ADD ("STRINGS", "Island Violins", {"w1",2}, UNI(4,10), FLT(3600,0.1f), FEN(0.15f,0.2f,1,0.8f), ENV(0.3f,1,0.9f,1.4f), {"lfoR",5.5f}, {"lfoP",0.06f}, {"chorus",0.35f}, RV(0.5f,0.8f), {"vol",0.6f});
    ADD ("STRINGS", "Pizzicato Beach", {"w1",2}, {"uni",2}, {"det",7}, FLT(1400,0.1f), FEN(0.5f,0.001f,0.12f,0.05f), ENV(0.001f,0.25f,0,0.2f), RV(0.3f,0.65f), {"vol",0.65f});
    ADD ("STRINGS", "Mariachi Swell", {"w1",2}, {"w2",2}, {"semi2",12}, {"lvl2",0.3f}, UNI(5,13), FLT(2800,0.08f), ENV(0.9f,1,0.9f,2), {"lfoR",5.4f}, {"lfoP",0.05f}, {"chorus",0.45f}, RV(0.5f,0.8f), {"vol",0.56f});

    // ---------------------------------------------------------------- RISER
    ADD ("RISER", "Wave Rise", {"lvl1",0}, {"noise",0.6f}, {"ftype",1}, FLT(400,0.3f), FEN(1,4,1,1), ENV(3,1,1,1.5f), {"lfoR",0.4f}, {"lfoA",0.2f}, RV(0.5f,0.82f), {"vol",0.85f});
    ADD ("RISER", "Sun Uplifter", {"w1",2}, UNI(5,16), {"pEnv",-12}, {"pDec",3.5f}, FLT(1800,0.1f), FEN(0.7f,3,1,1), ENV(3,1,1,1.5f), {"chorus",0.4f}, RV(0.5f,0.82f), {"vol",0.55f});
    ADD ("RISER", "Breeze Sweep", {"lvl1",0}, {"noise",0.5f}, {"ftype",2}, FLT(700,0.25f), FEN(0.9f,3,1,1), ENV(2.5f,1,1,1.2f), RV(0.4f,0.75f), {"vol",0.85f});
    ADD ("RISER", "Tide Out", {"lvl1",0}, {"noise",0.6f}, {"ftype",1}, FLT(5000,0.3f), FEN(-0.8f,0.01f,3,0), ENV(0.02f,3,0,1.2f), RV(0.5f,0.82f), {"vol",0.85f});
    ADD ("RISER", "Summer Impact", {"w1",0}, {"noise",0.25f}, FLT(1200,0.1f), {"pEnv",30}, {"pDec",0.25f}, ENV(0.001f,2.5f,0,1.2f), RV(0.45f,0.82f), {"vol",0.75f});
    ADD ("RISER", "Tropical Whoosh", {"lvl1",0}, {"noise",0.7f}, {"ftype",1}, FLT(300,0.5f), FEN(1,1.5f,0.8f,0), ENV(1.2f,0.8f,0,0.6f), RV(0.45f,0.8f), {"vol",0.85f});

    // ---------------------------------------------------------------- ARP
    ADD ("ARP", "Marimba Arp", {"w1",0}, {"fm",1.6f}, {"fmr",4}, ENV(0.001f,0.4f,0,0.3f), DLY(0.3f,333,0.4f), RV(0.3f,0.65f), {"vol",0.65f});
    ADD ("ARP", "Sun Pluck Arp", {"w1",2}, {"w2",1}, {"semi2",12}, {"lvl2",0.3f}, FLT(1500,0.12f), FEN(0.5f,0.002f,0.15f,0.05f), ENV(0.002f,0.25f,0,0.3f), DLY(0.3f,333,0.4f), RV(0.35f,0.7f), {"vol",0.6f});
    ADD ("ARP", "Bell Arp Beach", {"w1",0}, {"fm",1}, {"fmr",3.5f}, ENV(0.001f,0.5f,0,0.4f), DLY(0.35f,333,0.45f), RV(0.35f,0.7f), {"vol",0.6f});
    ADD ("ARP", "Warm Square Arp", {"w1",3}, FLT(1100,0.15f), FEN(0.5f,0.001f,0.12f,0.05f), ENV(0.001f,0.2f,0,0.2f), DLY(0.3f,333,0.4f), RV(0.3f,0.65f), {"vol",0.58f});
    ADD ("ARP", "Glow Arp Sun", {"w1",1}, {"w2",0}, {"semi2",12}, {"lvl2",0.45f}, ENV(0.002f,0.45f,0,0.4f), {"chorus",0.3f}, DLY(0.35f,333,0.45f), RV(0.4f,0.75f), {"vol",0.6f});
    ADD ("ARP", "Steel Arp", {"w1",0}, {"w2",0}, {"semi2",12}, {"lvl2",0.3f}, {"fm",1.3f}, {"fmr",1.5f}, ENV(0.002f,0.4f,0,0.3f), DLY(0.3f,333,0.4f), RV(0.3f,0.65f), {"vol",0.6f});

    // ---------------------------------------------------------------- FX
    ADD ("FX", "Wave Wash", {"lvl1",0}, {"noise",0.5f}, {"ftype",1}, FLT(600,0.3f), {"lfoR",0.15f}, {"lfoC",0.5f}, {"lfoA",0.4f}, ENV(1.5f,1,1,3), RV(0.6f,0.9f), {"vol",0.9f});
    ADD ("FX", "Seagull Bleep", {"w1",0}, {"pEnv",-12}, {"pDec",0.15f}, {"lfoR",8}, {"lfoP",0.2f}, ENV(0.01f,0.3f,0,0.3f), RV(0.4f,0.75f), {"vol",0.6f});
    ADD ("FX", "Sunset Shimmer", {"w1",0}, {"w2",0}, {"semi2",19}, {"lvl2",0.5f}, UNI(4,9), FLT(7000,0.1f), {"lfoR",0.2f}, {"lfoA",0.3f}, ENV(2,1,1,4), {"chorus",0.6f}, DLY(0.35f,420,0.5f), RV(0.7f,0.93f), {"vol",0.65f});
    ADD ("FX", "Heat Haze", {"lvl1",0}, {"noise",0.3f}, {"ftype",2}, FLT(4500,0.15f), {"lfoR",0.3f}, {"lfoC",0.3f}, ENV(1,1,1,2), {"lofi",0.15f}, RV(0.5f,0.82f), {"vol",0.9f});

    // ---------------------------------------------------------------- VOX
    ADD ("VOX", "Summer Ooh", {"w1",2}, UNI(4,10), {"ftype",1}, FLT(650,0.4f), ENV(0.4f,1,0.9f,1.8f), {"lfoR",5}, {"lfoP",0.06f}, {"chorus",0.35f}, RV(0.45f,0.8f), {"vol",0.7f});
    ADD ("VOX", "Sun Ahh", {"w1",2}, UNI(5,12), {"ftype",1}, FLT(1250,0.4f), ENV(0.5f,1,0.9f,2), {"lfoR",5.2f}, {"lfoP",0.07f}, {"chorus",0.35f}, RV(0.5f,0.82f), {"vol",0.7f});
    ADD ("VOX", "Coro Playa", {"w1",2}, UNI(6,15), {"noise",0.05f}, {"ftype",1}, FLT(950,0.45f), ENV(0.7f,1,0.9f,2.2f), {"lfoR",4.8f}, {"lfoP",0.08f}, {"chorus",0.45f}, RV(0.5f,0.82f), {"vol",0.68f});
    ADD ("VOX", "Warm Hum", {"w1",1}, {"sub",0.1f}, {"ftype",1}, FLT(500,0.35f), ENV(0.5f,1,0.9f,2), {"lfoR",4.5f}, {"lfoP",0.05f}, {"chorus",0.3f}, RV(0.4f,0.75f), {"vol",0.7f});

#undef ADD
}
