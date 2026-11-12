// ATMOSFERA: oscuro, espacial, envolvente (estilo Travis Scott / Don Toliver)
// Se incluye desde Presets.h (usa mk y los atajos RV, DLY, ENV, FEN, UNI, FLT definidos alli).
inline void addAtmosPresets (std::vector<Preset>& L)
{
#define ADD(cat, name, ...) L.push_back (mk (0, cat, name, { __VA_ARGS__ }))

    // ---------------------------------------------------------------- PAD
    ADD ("PAD", "Orbit Pad", {"w1",2}, {"w2",2}, {"semi2",7}, {"lvl2",0.35f}, UNI(6,24), FLT(1100,0.12f), FEN(0.3f,3,4,0.5f), ENV(2,2,0.9f,5),
         {"lfoR",0.12f}, {"lfoC",0.3f}, {"chorus",0.6f}, DLY(0.3f,500,0.55f), RV(0.65f,0.92f), {"vol",0.58f});
    ADD ("PAD", "Event Horizon", {"w1",2}, {"sub",0.25f}, UNI(7,35), FLT(600,0.18f), FEN(0.5f,5,6,0.4f), ENV(3,3,0.85f,7),
         {"lfoR",0.07f}, {"lfoC",0.35f}, {"drive",0.1f}, {"chorus",0.5f}, RV(0.8f,0.96f), {"vol",0.55f});
    ADD ("PAD", "Violet Smoke", {"w1",1}, {"w2",2}, {"semi2",-12}, {"lvl2",0.45f}, UNI(5,18), FLT(1500,0.1f), ENV(1.8f,2,0.9f,4.5f),
         {"lfoR",0.2f}, {"lfoP",0.05f}, {"chorus",0.7f}, DLY(0.25f,480,0.5f), RV(0.6f,0.9f), {"vol",0.6f});
    ADD ("PAD", "Lunar Haze", {"w1",0}, {"w2",1}, {"semi2",12}, {"lvl2",0.5f}, UNI(4,12), FLT(4500,0.05f), ENV(3,2,0.9f,6),
         {"lfoR",0.18f}, {"lfoC",0.25f}, {"chorus",0.65f}, DLY(0.3f,560,0.55f), RV(0.75f,0.94f), {"vol",0.6f});
    ADD ("PAD", "Cosmic Dust", {"w1",2}, {"noise",0.1f}, UNI(7,30), FLT(2800,0.2f), ENV(2.5f,3,0.7f,6),
         {"lfoR",0.1f}, {"lfoC",0.3f}, {"chorus",0.6f}, RV(0.8f,0.95f), {"vDamp",0.7f}, {"vol",0.55f});
    ADD ("PAD", "Midnight Drive Pad", {"w1",2}, {"w2",3}, {"semi2",-12}, {"lvl2",0.25f}, UNI(4,14), FLT(900,0.2f), FEN(0.35f,1.2f,3,0.5f), ENV(1,1.5f,0.85f,3),
         {"lfoR",0.25f}, {"lfoC",0.3f}, {"drive",0.15f}, {"chorus",0.55f}, DLY(0.25f,420,0.45f), RV(0.55f,0.88f), {"vol",0.6f});
    ADD ("PAD", "Void Choir", {"w1",2}, UNI(6,20), {"noise",0.07f}, {"ftype",1}, FLT(850,0.5f), ENV(2,2,0.9f,5),
         {"lfoR",4.8f}, {"lfoP",0.09f}, {"lfoA",0.2f}, {"chorus",0.45f}, RV(0.7f,0.93f), {"vol",0.68f});
    ADD ("PAD", "Gravity Well", {"w1",2}, {"w2",2}, {"semi2",-24}, {"lvl2",0.5f}, {"sub",0.4f}, UNI(3,10), FLT(380,0.25f), FEN(0.6f,4,5,0.3f), ENV(2,3,0.9f,6),
         {"lfoR",0.06f}, {"lfoC",0.4f}, {"drive",0.2f}, RV(0.7f,0.94f), {"vol",0.58f});

    // ---------------------------------------------------------------- BASS
    ADD ("BASS", "Trap 808 Long", {"w1",0}, FLT(1100,0.1f), {"pEnv",12}, {"pDec",0.06f}, ENV(0.002f,3,0,0.35f), {"mono",1}, {"glide",0.08f}, {"drive",0.3f}, RV(0.05f,0.4f), {"vol",0.75f});
    ADD ("BASS", "Dark 808", {"w1",0}, {"sub",0.2f}, FLT(700,0.1f), {"pEnv",16}, {"pDec",0.05f}, ENV(0.002f,2.4f,0,0.3f), {"mono",1}, {"glide",0.1f}, {"drive",0.45f}, {"vol",0.75f});
    ADD ("BASS", "Distorted 808", {"w1",0}, {"w2",3}, {"semi2",-12}, {"lvl2",0.1f}, FLT(3000,0.15f), {"pEnv",20}, {"pDec",0.05f}, ENV(0.002f,1.8f,0,0.25f), {"mono",1}, {"glide",0.08f}, {"drive",0.85f}, {"vol",0.65f});
    ADD ("BASS", "Clean Sub", {"w1",0}, FLT(300,0), ENV(0.01f,0.4f,1,0.3f), {"mono",1}, {"glide",0.03f}, {"vol",0.8f});
    ADD ("BASS", "Rage Reese", {"w1",2}, {"w2",2}, {"semi2",0}, {"lvl2",0.9f}, {"det",14}, {"uni",2}, FLT(500,0.3f), {"lfoR",0.3f}, {"lfoC",0.3f}, ENV(0.01f,0.8f,0.8f,0.3f), {"mono",1}, {"drive",0.6f}, {"vol",0.55f});
    ADD ("BASS", "Floating Sub", {"w1",0}, {"w2",1}, {"semi2",12}, {"lvl2",0.1f}, FLT(450,0.1f), {"pEnv",5}, {"pDec",0.04f}, ENV(0.005f,1.4f,0.4f,0.5f), {"mono",1}, {"glide",0.18f}, {"vol",0.78f});
    ADD ("BASS", "Gritty Bit 808", {"w1",0}, FLT(1500,0.1f), {"pEnv",12}, {"pDec",0.06f}, ENV(0.002f,2,0,0.25f), {"mono",1}, {"glide",0.06f}, {"drive",0.4f}, {"lofi",0.35f}, {"vol",0.72f});
    ADD ("BASS", "Boom Fall", {"w1",0}, FLT(900,0), {"pEnv",36}, {"pDec",0.45f}, ENV(0.002f,2.5f,0,0.4f), {"mono",1}, {"drive",0.3f}, {"vol",0.78f});

    // ---------------------------------------------------------------- SYNTH
    ADD ("SYNTH", "Neon Lead", {"w1",2}, {"w2",3}, {"semi2",12}, {"lvl2",0.2f}, UNI(3,12), FLT(3600,0.15f), FEN(0.25f,0.01f,0.5f,0.3f), ENV(0.02f,0.4f,0.8f,0.8f),
         {"lfoR",5.4f}, {"lfoP",0.06f}, {"mono",1}, {"glide",0.06f}, {"chorus",0.35f}, DLY(0.35f,375,0.45f), RV(0.4f,0.75f), {"vol",0.6f});
    ADD ("SYNTH", "Spaceship Lead", {"w1",3}, {"w2",2}, {"semi2",-12}, {"lvl2",0.4f}, {"det",10}, {"uni",2}, FLT(2200,0.3f), FEN(0.4f,0.05f,0.8f,0.4f), ENV(0.03f,0.5f,0.75f,1.2f),
         {"lfoR",0.4f}, {"lfoC",0.3f}, {"mono",1}, {"glide",0.1f}, {"chorus",0.3f}, DLY(0.4f,420,0.55f), RV(0.55f,0.85f), {"vol",0.55f});
    ADD ("SYNTH", "Supersaw Dream", {"w1",2}, UNI(7,26), FLT(3000,0.1f), ENV(0.15f,0.8f,0.85f,1.8f), {"chorus",0.5f}, DLY(0.2f,450,0.4f), RV(0.5f,0.85f), {"vol",0.52f});
    ADD ("SYNTH", "Hollow Stab", {"w1",3}, {"w2",1}, {"semi2",12}, {"lvl2",0.3f}, {"uni",2}, {"det",8}, FLT(1300,0.2f), FEN(0.5f,0.005f,0.25f,0.1f), ENV(0.004f,0.35f,0.2f,0.5f),
         DLY(0.35f,333,0.45f), RV(0.45f,0.8f), {"vol",0.6f});
    ADD ("SYNTH", "Warp Bass Synth", {"w1",2}, {"w2",3}, {"semi2",-12}, {"lvl2",0.6f}, {"uni",2}, {"det",9}, FLT(450,0.35f), FEN(0.7f,0.005f,0.3f,0.2f), ENV(0.005f,0.5f,0.7f,0.25f),
         {"mono",1}, {"glide",0.04f}, {"drive",0.4f}, {"vol",0.6f});
    ADD ("SYNTH", "Cyber Pluck Lead", {"w1",2}, {"uni",3}, {"det",14}, FLT(1000,0.2f), FEN(0.6f,0.003f,0.3f,0.15f), ENV(0.003f,0.6f,0.35f,0.7f),
         {"chorus",0.35f}, DLY(0.45f,375,0.5f), RV(0.45f,0.8f), {"vol",0.6f});
    ADD ("SYNTH", "Ghost Whistle", {"w1",0}, {"w2",0}, {"semi2",12}, {"lvl2",0.25f}, {"fm",0.2f}, {"fmr",2}, ENV(0.15f,0.5f,0.9f,1.5f),
         {"lfoR",5.5f}, {"lfoP",0.18f}, {"mono",1}, {"glide",0.1f}, DLY(0.4f,500,0.5f), RV(0.6f,0.9f), {"vol",0.6f});
    ADD ("SYNTH", "Dark Wobble", {"w1",2}, {"w2",3}, {"semi2",-12}, {"lvl2",0.4f}, {"uni",2}, {"det",10}, FLT(500,0.4f), {"lfoR",2}, {"lfoS",1}, {"lfoC",0.6f},
         ENV(0.01f,0.5f,0.9f,0.4f), {"mono",1}, {"drive",0.35f}, RV(0.2f,0.6f), {"vol",0.55f});

    // ---------------------------------------------------------------- PLUCK
    ADD ("PLUCK", "Cave Pluck", {"w1",2}, {"w2",1}, {"semi2",12}, {"lvl2",0.3f}, {"uni",2}, {"det",8}, FLT(450,0.15f), FEN(0.7f,0.002f,0.25f,0.05f), ENV(0.002f,0.7f,0,0.6f),
         {"chorus",0.2f}, DLY(0.5f,420,0.55f), RV(0.55f,0.9f), {"vol",0.65f});
    ADD ("PLUCK", "Moon Harp", {"w1",1}, {"w2",0}, {"semi2",12}, {"lvl2",0.5f}, FLT(3200,0.05f), FEN(0.3f,0.001f,0.5f,0.1f), ENV(0.002f,1.6f,0,1.4f),
         {"chorus",0.3f}, DLY(0.35f,480,0.5f), RV(0.65f,0.9f), {"vol",0.62f});
    ADD ("PLUCK", "Reverse Pluck", {"w1",2}, {"uni",2}, {"det",10}, FLT(1200,0.2f), FEN(0.6f,0.002f,0.18f,0.1f), ENV(0.002f,0.45f,0,0.3f),
         {"pEnv",-5}, {"pDec",0.08f}, DLY(0.5f,375,0.6f), RV(0.6f,0.9f), {"vol",0.62f});
    ADD ("PLUCK", "Frozen String", {"w1",3}, {"w2",2}, {"semi2",12}, {"lvl2",0.2f}, FLT(900,0.25f), FEN(0.5f,0.001f,0.15f,0.05f), ENV(0.001f,0.55f,0,0.5f),
         {"drive",0.1f}, DLY(0.45f,420,0.5f), RV(0.6f,0.9f), {"vDamp",0.7f}, {"vol",0.62f});
    ADD ("PLUCK", "Echo Drops", {"w1",0}, {"fm",1.6f}, {"fmr",3}, FEN(0,0.001f,0.2f,0), ENV(0.001f,0.5f,0,0.5f), DLY(0.6f,333,0.65f), RV(0.55f,0.9f), {"vol",0.62f});
    ADD ("PLUCK", "Lo-Fi Nylon", {"w1",1}, {"w2",2}, {"semi2",12}, {"lvl2",0.12f}, FLT(650,0.12f), FEN(0.55f,0.002f,0.2f,0.05f), ENV(0.002f,0.7f,0,0.5f),
         {"lofi",0.25f}, {"chorus",0.25f}, RV(0.35f,0.75f), {"vol",0.65f});

    // ---------------------------------------------------------------- BELL
    ADD ("BELL", "Nebula Bell", {"w1",0}, {"fm",2},  {"fmr",3.5f}, ENV(0.001f,3.5f,0,3.5f), FEN(0,0.001f,1.5f,0), DLY(0.35f,500,0.55f), RV(0.7f,0.95f), {"vol",0.58f});
    ADD ("BELL", "Dark Chime", {"w1",0}, {"w2",0}, {"semi2",12}, {"lvl2",0.3f}, {"fm",1.4f}, {"fmr",2.76f}, ENV(0.001f,3,0,3), DLY(0.3f,560,0.5f), RV(0.7f,0.95f), {"vDamp",0.65f}, {"vol",0.58f});
    ADD ("BELL", "Crystal Rain", {"w1",1}, {"fm",1.2f}, {"fmr",6}, {"uni",3}, {"det",6}, {"spread",1}, ENV(0.001f,1.8f,0,2), {"chorus",0.4f}, DLY(0.5f,375,0.6f), RV(0.65f,0.92f), {"vol",0.55f});
    ADD ("BELL", "Temple Gong", {"w1",0}, {"sub",0.15f}, {"fm",3.5f}, {"fmr",1.41f}, ENV(0.002f,6,0,6), {"drive",0.1f}, RV(0.75f,0.97f), {"vol",0.55f});
    ADD ("BELL", "Frost Glock", {"w1",1}, {"w2",0}, {"semi2",24}, {"lvl2",0.3f}, {"fm",0.7f}, {"fmr",4}, ENV(0.001f,1.2f,0,1.2f), DLY(0.3f,420,0.5f), RV(0.6f,0.9f), {"vol",0.6f});
    ADD ("BELL", "Underwater Bell", {"w1",0}, {"fm",2.6f}, {"fmr",2}, ENV(0.001f,3,0,3), FLT(1400,0.1f), {"lfoR",0.3f}, {"lfoC",0.4f}, {"chorus",0.7f}, RV(0.75f,0.95f), {"vol",0.6f});

    // ---------------------------------------------------------------- KEYS
    ADD ("KEYS", "Night Rhodes", {"w1",0}, {"w2",0}, {"semi2",12}, {"lvl2",0.12f}, {"fm",1.2f}, {"fmr",1}, FEN(0,0.001f,0.6f,0.1f), ENV(0.003f,2,0.3f,0.8f),
         {"drive",0.1f}, {"chorus",0.6f}, {"lfoR",4.5f}, {"lfoA",0.12f}, RV(0.5f,0.85f), {"vol",0.65f});
    ADD ("KEYS", "Space Piano", {"w1",1}, {"w2",2}, {"lvl2",0.08f}, {"fm",0.5f}, {"fmr",3}, FLT(2800,0.05f), ENV(0.002f,2,0.1f,0.8f), DLY(0.3f,480,0.45f), RV(0.65f,0.92f), {"vol",0.65f});
    ADD ("KEYS", "Dusty EP", {"w1",1}, {"w2",3}, {"semi2",12}, {"lvl2",0.12f}, FLT(1600,0.1f), FEN(0.2f,0.003f,0.5f,0.1f), ENV(0.003f,1.4f,0.3f,0.5f),
         {"lofi",0.3f}, {"chorus",0.5f}, RV(0.4f,0.75f), {"vol",0.65f});
    ADD ("KEYS", "Cathedral Organ", {"w1",1}, {"w2",1}, {"semi2",12}, {"lvl2",0.5f}, {"sub",0.2f}, FLT(2400,0.05f), ENV(0.03f,0.5f,0.95f,0.6f),
         {"lfoR",5.5f}, {"lfoP",0.03f}, {"chorus",0.4f}, RV(0.75f,0.96f), {"vol",0.6f});
    ADD ("KEYS", "Ambient Wurli", {"w1",1}, {"w2",3}, {"semi2",12}, {"lvl2",0.15f}, FLT(1900,0.1f), ENV(0.003f,1.5f,0.35f,0.6f),
         {"drive",0.15f}, {"chorus",0.45f}, DLY(0.3f,420,0.45f), RV(0.55f,0.88f), {"vol",0.65f});
    ADD ("KEYS", "Glass Piano", {"w1",0}, {"w2",1}, {"semi2",12}, {"lvl2",0.35f}, {"fm",0.9f}, {"fmr",5}, ENV(0.002f,1.8f,0.05f,0.9f), {"chorus",0.3f}, RV(0.65f,0.93f), {"vol",0.62f});

    // ---------------------------------------------------------------- MALLET
    ADD ("MALLET", "Dark Marimba", {"w1",0}, {"fm",1.8f}, {"fmr",4}, FEN(0,0.001f,0.12f,0), ENV(0.001f,0.6f,0,0.4f), FLT(2500,0.05f), DLY(0.3f,375,0.5f), RV(0.55f,0.85f), {"vol",0.65f});
    ADD ("MALLET", "Cold Vibes", {"w1",0}, {"fm",0.9f}, {"fmr",4}, ENV(0.002f,2.4f,0,1.6f), {"lfoR",5}, {"lfoA",0.4f}, DLY(0.25f,420,0.4f), RV(0.6f,0.9f), {"vol",0.62f});
    ADD ("MALLET", "Kalimba Void", {"w1",0}, {"fm",2.4f}, {"fmr",3.5f}, FEN(0,0.001f,0.2f,0), ENV(0.001f,1.2f,0,0.9f), DLY(0.45f,500,0.55f), RV(0.65f,0.92f), {"vol",0.65f});
    ADD ("MALLET", "Ice Xylo", {"w1",1}, {"w2",0}, {"semi2",19}, {"lvl2",0.25f}, {"fm",0.8f}, {"fmr",6}, ENV(0.001f,0.35f,0,0.3f), DLY(0.3f,333,0.45f), RV(0.5f,0.85f), {"vol",0.62f});
    ADD ("MALLET", "Steel Pan Night", {"w1",0}, {"w2",0}, {"semi2",12}, {"lvl2",0.3f}, {"fm",1.4f}, {"fmr",1.5f}, ENV(0.002f,0.9f,0,0.7f), {"chorus",0.3f}, DLY(0.35f,420,0.5f), RV(0.5f,0.85f), {"vol",0.62f});
    ADD ("MALLET", "Wood Block Soft", {"w1",0}, {"fm",3}, {"fmr",2.3f}, ENV(0.001f,0.18f,0,0.15f), FLT(1800,0.1f), RV(0.35f,0.7f), {"vol",0.65f});

    // ---------------------------------------------------------------- STRINGS
    ADD ("STRINGS", "Dark Ensemble", {"w1",2}, UNI(6,14), FLT(1800,0.1f), FEN(0.2f,0.5f,2,0.7f), ENV(0.9f,1,0.9f,2.5f), {"lfoR",5.2f}, {"lfoP",0.04f}, {"chorus",0.5f}, RV(0.6f,0.88f), {"vol",0.6f});
    ADD ("STRINGS", "Cinema Swell", {"w1",2}, UNI(7,16), FLT(1200,0.12f), FEN(0.5f,3,2,0.7f), ENV(2.5f,1,0.9f,3.5f), {"lfoR",5.5f}, {"lfoP",0.04f}, {"chorus",0.5f}, RV(0.7f,0.92f), {"vol",0.58f});
    ADD ("STRINGS", "Slow Cello", {"w1",2}, {"w2",3}, {"semi2",-12}, {"lvl2",0.15f}, {"uni",3}, {"det",8}, FLT(900,0.15f), FEN(0.25f,0.3f,1.5f,0.6f), ENV(0.4f,1,0.9f,1.5f),
         {"lfoR",5}, {"lfoP",0.05f}, {"mono",1}, {"glide",0.05f}, RV(0.5f,0.85f), {"vol",0.62f});
    ADD ("STRINGS", "Lonely Violin", {"w1",2}, {"uni",2}, {"det",6}, FLT(3200,0.12f), FEN(0.2f,0.2f,1,0.8f), ENV(0.25f,0.8f,0.9f,1.2f),
         {"lfoR",5.5f}, {"lfoP",0.09f}, {"mono",1}, {"glide",0.06f}, {"chorus",0.25f}, DLY(0.25f,420,0.4f), RV(0.6f,0.9f), {"vol",0.6f});
    ADD ("STRINGS", "Tremolo Strings", {"w1",2}, UNI(5,12), FLT(2200,0.1f), ENV(0.35f,1,0.9f,1.8f), {"lfoR",7}, {"lfoA",0.55f}, {"chorus",0.4f}, RV(0.6f,0.88f), {"vol",0.6f});
    ADD ("STRINGS", "Pizzicato Dark", {"w1",2}, {"uni",3}, {"det",8}, FLT(800,0.15f), FEN(0.6f,0.001f,0.14f,0.05f), ENV(0.001f,0.3f,0,0.3f), RV(0.45f,0.8f), {"vol",0.65f});
    ADD ("STRINGS", "Glass Orchestra", {"w1",1}, {"w2",2}, {"semi2",12}, {"lvl2",0.3f}, UNI(5,18), FLT(4000,0.1f), ENV(1.2f,1,0.9f,3), {"lfoR",5}, {"lfoP",0.03f}, {"chorus",0.6f}, RV(0.75f,0.94f), {"vol",0.55f});
    ADD ("STRINGS", "Drone Strings", {"w1",2}, {"sub",0.2f}, UNI(7,22), FLT(700,0.2f), FEN(0.4f,3,3,0.6f), ENV(3,2,1,5), {"lfoR",0.1f}, {"lfoC",0.3f}, {"chorus",0.5f}, RV(0.8f,0.96f), {"vol",0.55f});

    // ---------------------------------------------------------------- RISER
    ADD ("RISER", "Noise Rise 8s", {"lvl1",0}, {"noise",0.8f}, {"ftype",1}, FLT(300,0.35f), FEN(1,7,2,1), ENV(6,1,1,2), {"lfoR",8}, {"lfoA",0.1f}, RV(0.5f,0.85f), {"vol",0.9f});
    ADD ("RISER", "Pitch Rise", {"w1",2}, UNI(5,20), {"pEnv",-24}, {"pDec",4.5f}, FLT(1500,0.2f), FEN(0.6f,5,2,1), ENV(4,1,1,1.5f), {"chorus",0.4f}, RV(0.5f,0.85f), {"vol",0.55f});
    ADD ("RISER", "Dark Uplifter", {"w1",2}, {"w2",3}, {"semi2",-12}, {"lvl2",0.5f}, UNI(4,25), {"pEnv",-12}, {"pDec",5}, FLT(400,0.3f), FEN(0.9f,6,2,1), ENV(5,1,1,2),
         {"drive",0.25f}, RV(0.6f,0.9f), {"vol",0.55f});
    ADD ("RISER", "Tension Tremolo", {"lvl1",0}, {"noise",0.7f}, {"ftype",2}, FLT(500,0.3f), FEN(0.7f,6,2,1), ENV(5,1,1,2), {"lfoR",9}, {"lfoS",3}, {"lfoA",0.6f}, RV(0.5f,0.85f), {"vol",0.9f});
    ADD ("RISER", "Reverse Swell", {"w1",2}, UNI(7,28), FLT(250,0.2f), FEN(1,4,2,1), ENV(4,1,1,3), {"chorus",0.5f}, RV(0.8f,0.96f), {"vol",0.55f});
    ADD ("RISER", "Downlifter", {"lvl1",0}, {"noise",0.8f}, {"ftype",1}, FLT(6000,0.35f), FEN(-0.85f,0.01f,3,0), ENV(0.02f,3,0,1.5f), RV(0.6f,0.9f), {"vol",0.9f});
    ADD ("RISER", "Sub Drop", {"w1",0}, {"sub",0.2f}, {"pEnv",48}, {"pDec",1.4f}, FLT(500,0), ENV(0.002f,3,0,1.5f), {"drive",0.2f}, RV(0.3f,0.7f), {"vol",0.8f});
    ADD ("RISER", "Impact Boom", {"w1",0}, {"noise",0.35f}, FLT(900,0.2f), {"pEnv",36}, {"pDec",0.35f}, ENV(0.001f,4,0,2), {"drive",0.4f}, RV(0.6f,0.95f), {"vol",0.8f});
    ADD ("RISER", "Sweep Up Bright", {"lvl1",0}, {"noise",0.6f}, {"ftype",2}, FLT(200,0.4f), FEN(1,3,1,1), ENV(2.5f,1,1,1.5f), RV(0.45f,0.8f), {"vol",0.9f});
    ADD ("RISER", "Choir Rise", {"w1",2}, UNI(6,18), {"ftype",1}, FLT(700,0.5f), FEN(0.6f,5,2,1), ENV(4,1,1,3), {"pEnv",-12}, {"pDec",4}, {"lfoR",5}, {"lfoP",0.1f}, RV(0.7f,0.92f), {"vol",0.6f});

    // ---------------------------------------------------------------- TEXTURE
    ADD ("TEXTURE", "Distant Storm", {"lvl1",0}, {"noise",0.8f}, {"ftype",1}, FLT(450,0.4f), {"lfoR",0.09f}, {"lfoC",0.55f}, ENV(3,1,1,6), RV(0.8f,0.96f), {"vol",0.95f});
    ADD ("TEXTURE", "Static Fog", {"lvl1",0}, {"noise",0.5f}, {"ftype",2}, FLT(3000,0.15f), {"lfoR",0.2f}, {"lfoC",0.3f}, ENV(2,1,1,4), {"lofi",0.4f}, RV(0.6f,0.9f), {"vol",0.9f});
    ADD ("TEXTURE", "Alien Drone", {"w1",2}, {"w2",3}, {"semi2",7}, {"lvl2",0.3f}, UNI(5,45), FLT(500,0.4f), {"lfoR",0.12f}, {"lfoS",4}, {"lfoC",0.5f}, ENV(4,1,1,7),
         {"drive",0.2f}, RV(0.85f,0.97f), {"vol",0.85f});
    ADD ("TEXTURE", "Cave Breath", {"lvl1",0}, {"noise",0.6f}, {"ftype",1}, FLT(900,0.6f), {"lfoR",0.12f}, {"lfoS",1}, {"lfoC",0.6f}, {"lfoA",0.3f}, ENV(2,1,1,4), RV(0.85f,0.97f), {"vDamp",0.7f}, {"vol",0.95f});
    ADD ("TEXTURE", "Magnetic Hum", {"w1",0}, {"sub",0.5f}, {"fm",0.4f}, {"fmr",0.5f}, {"uni",3}, {"det",18}, FLT(900,0.2f), {"lfoR",0.08f}, {"lfoA",0.3f}, ENV(3,1,1,6), RV(0.8f,0.96f), {"vol",0.85f});
    ADD ("TEXTURE", "Dream Shimmer", {"w1",0}, {"w2",0}, {"semi2",19}, {"lvl2",0.5f}, UNI(5,9), FLT(7000,0.1f), {"lfoR",0.17f}, {"lfoA",0.35f}, ENV(3.5f,1,1,6), {"chorus",0.7f}, DLY(0.4f,600,0.6f), RV(0.85f,0.97f), {"vol",0.7f});
    ADD ("TEXTURE", "Tape Hiss Air", {"lvl1",0}, {"noise",0.12f}, {"ftype",2}, FLT(5000,0.1f), ENV(0.5f,1,1,1), {"lofi",0.2f}, {"vol",0.95f});
    ADD ("TEXTURE", "Black Ocean", {"lvl1",0}, {"noise",0.7f}, {"sub",0.4f}, FLT(260,0.35f), {"lfoR",0.07f}, {"lfoC",0.7f}, ENV(4,1,1,7), RV(0.85f,0.98f), {"vol",0.95f});

    // ---------------------------------------------------------------- ARP
    ADD ("ARP", "Neon Arp Saw", {"w1",2}, {"uni",2}, {"det",10}, FLT(1500,0.25f), FEN(0.65f,0.002f,0.16f,0.05f), ENV(0.002f,0.2f,0.1f,0.3f), {"chorus",0.3f}, DLY(0.45f,280,0.5f), RV(0.4f,0.8f), {"vol",0.6f});
    ADD ("ARP", "Glass Arp", {"w1",1}, {"w2",0}, {"semi2",12}, {"lvl2",0.5f}, {"fm",0.7f}, {"fmr",3}, ENV(0.002f,0.4f,0,0.5f), DLY(0.5f,333,0.55f), RV(0.55f,0.88f), {"vol",0.6f});
    ADD ("ARP", "Square Pulse Arp", {"w1",3}, FLT(1200,0.3f), FEN(0.6f,0.002f,0.12f,0.05f), ENV(0.002f,0.18f,0,0.2f), DLY(0.4f,250,0.5f), RV(0.35f,0.75f), {"vol",0.58f});
    ADD ("ARP", "Dream Arp", {"w1",2}, {"w2",1}, {"semi2",12}, {"lvl2",0.4f}, UNI(3,12), FLT(2600,0.12f), FEN(0.3f,0.002f,0.3f,0.1f), ENV(0.003f,0.5f,0.1f,0.6f), {"chorus",0.5f}, DLY(0.4f,375,0.55f), RV(0.6f,0.9f), {"vol",0.58f});
    ADD ("ARP", "Retro Bleep", {"w1",3}, {"w2",3}, {"semi2",12}, {"lvl2",0.3f}, {"det",6}, {"uni",2}, FLT(2400,0.2f), ENV(0.001f,0.15f,0,0.15f), {"lofi",0.2f}, DLY(0.35f,250,0.45f), RV(0.3f,0.7f), {"vol",0.55f});
    ADD ("ARP", "Hyper Pluck Arp", {"w1",2}, {"w2",2}, {"semi2",7}, {"lvl2",0.3f}, {"uni",2}, {"det",9}, FLT(800,0.2f), FEN(0.7f,0.001f,0.1f,0.05f), ENV(0.001f,0.22f,0,0.25f), DLY(0.5f,300,0.55f), RV(0.45f,0.8f), {"vol",0.6f});

    // ---------------------------------------------------------------- VOX
    ADD ("VOX", "Ghost Ooh", {"w1",2}, UNI(4,12), {"ftype",1}, FLT(550,0.45f), ENV(0.6f,1,0.9f,2.5f), {"lfoR",5}, {"lfoP",0.07f}, {"chorus",0.4f}, DLY(0.25f,420,0.45f), RV(0.65f,0.92f), {"vol",0.7f});
    ADD ("VOX", "Angel Ahh", {"w1",2}, UNI(5,16), {"noise",0.05f}, {"ftype",1}, FLT(1100,0.45f), ENV(0.8f,1,0.9f,3), {"lfoR",5.2f}, {"lfoP",0.08f}, {"chorus",0.4f}, RV(0.7f,0.93f), {"vol",0.7f});
    ADD ("VOX", "Breath Vox", {"w1",2}, {"noise",0.25f}, {"uni",3}, {"det",10}, {"ftype",1}, FLT(900,0.35f), ENV(0.4f,1,0.9f,1.8f), {"lfoR",0.3f}, {"lfoC",0.3f}, RV(0.65f,0.9f), {"vol",0.7f});
    ADD ("VOX", "Choir Stack Dark", {"w1",2}, {"w2",2}, {"semi2",-12}, {"lvl2",0.5f}, UNI(7,20), {"ftype",1}, FLT(700,0.5f), ENV(1.5f,1,0.9f,4), {"lfoR",4.6f}, {"lfoP",0.1f}, {"chorus",0.5f}, RV(0.75f,0.95f), {"vol",0.65f});
    ADD ("VOX", "Autotune Lead Vox", {"w1",2}, {"w2",3}, {"semi2",12}, {"lvl2",0.1f}, {"ftype",1}, FLT(1300,0.55f), ENV(0.02f,0.4f,0.85f,0.6f), {"lfoR",5.5f}, {"lfoP",0.05f}, {"mono",1}, {"glide",0.04f}, DLY(0.3f,375,0.45f), RV(0.45f,0.8f), {"vol",0.6f});
    ADD ("VOX", "Whisper Pad", {"lvl1",0}, {"noise",0.45f}, {"ftype",1}, FLT(1700,0.6f), {"lfoR",0.25f}, {"lfoC",0.4f}, ENV(1,1,1,2.5f), RV(0.75f,0.94f), {"vol",0.95f});

#undef ADD
}
