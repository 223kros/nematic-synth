// ROMANTICO: reggaeton romantico actual (estilo Mora, Saiko, Tainy): suave, calido, brillante.
inline void addRomanticoPresets (std::vector<Preset>& L)
{
#define ADD(cat, name, ...) L.push_back (mk (1, cat, name, { __VA_ARGS__ }))

    // ---------------------------------------------------------------- PAD
    ADD ("PAD", "Silk Pad", {"w1",1}, {"w2",2}, {"lvl2",0.3f}, UNI(4,10), FLT(2400,0.08f), ENV(0.8f,1,0.9f,2), {"chorus",0.55f}, DLY(0.15f,333,0.4f), RV(0.4f,0.75f), {"vol",0.6f});
    ADD ("PAD", "Candle Light", {"w1",0}, {"w2",1}, {"semi2",12}, {"lvl2",0.45f}, UNI(3,8), FLT(3500,0.05f), ENV(0.6f,1,0.9f,2), {"lfoR",0.3f}, {"lfoC",0.2f}, {"chorus",0.5f}, RV(0.5f,0.8f), {"vol",0.6f});
    ADD ("PAD", "Warm Glow", {"w1",2}, {"w2",1}, {"semi2",-12}, {"lvl2",0.5f}, UNI(4,12), FLT(1600,0.1f), FEN(0.2f,0.5f,1.5f,0.7f), ENV(0.7f,1,0.9f,2.2f), {"chorus",0.5f}, RV(0.45f,0.78f), {"vol",0.6f});
    ADD ("PAD", "Love Air", {"w1",2}, {"noise",0.05f}, UNI(5,15), FLT(4200,0.05f), ENV(0.9f,1,0.9f,2.4f), {"chorus",0.4f}, RV(0.55f,0.82f), {"vol",0.55f});
    ADD ("PAD", "Blush Pad", {"w1",1}, {"w2",0}, {"lvl2",0.4f}, UNI(3,9), FLT(2000,0.08f), ENV(0.5f,1,0.9f,1.8f), {"lfoR",0.35f}, {"lfoP",0.04f}, {"chorus",0.6f}, DLY(0.2f,333,0.4f), RV(0.45f,0.8f), {"vol",0.62f});
    ADD ("PAD", "Slow Dance", {"w1",2}, {"w2",2}, {"semi2",7}, {"lvl2",0.25f}, UNI(5,13), FLT(1500,0.1f), FEN(0.25f,0.8f,2,0.6f), ENV(1.1f,1,0.9f,2.8f), {"chorus",0.55f}, RV(0.5f,0.85f), {"vol",0.58f});

    // ---------------------------------------------------------------- BASS
    ADD ("BASS", "808 Corazon", {"w1",0}, FLT(800,0.05f), {"pEnv",5}, {"pDec",0.05f}, ENV(0.002f,2.2f,0,0.25f), {"mono",1}, {"glide",0.07f}, {"drive",0.2f}, {"vol",0.75f});
    ADD ("BASS", "Dembow Sub", {"w1",0}, {"w2",1}, {"semi2",12}, {"lvl2",0.1f}, FLT(1000,0.05f), {"pEnv",7}, {"pDec",0.04f}, ENV(0.002f,0.9f,0.1f,0.2f), {"mono",1}, {"glide",0.04f}, {"drive",0.25f}, {"vol",0.75f});
    ADD ("BASS", "Slide Love", {"w1",0}, {"sub",0.15f}, FLT(950,0.05f), {"pEnv",9}, {"pDec",0.05f}, ENV(0.002f,2.6f,0,0.3f), {"mono",1}, {"glide",0.18f}, {"drive",0.3f}, {"vol",0.75f});
    ADD ("BASS", "Round Bass", {"w1",1}, {"sub",0.3f}, FLT(500,0.05f), FEN(0.2f,0.003f,0.2f,0.3f), ENV(0.004f,0.6f,0.5f,0.25f), {"mono",1}, {"glide",0.03f}, {"drive",0.1f}, {"vol",0.75f});
    ADD ("BASS", "Soft 808 Short", {"w1",0}, FLT(700,0), {"pEnv",4}, {"pDec",0.04f}, ENV(0.002f,0.8f,0,0.15f), {"mono",1}, {"glide",0.04f}, {"drive",0.15f}, {"vol",0.78f});
    ADD ("BASS", "Velvet Sub", {"w1",0}, {"w2",0}, {"semi2",12}, {"lvl2",0.1f}, FLT(400,0), ENV(0.01f,0.5f,0.85f,0.35f), {"mono",1}, {"glide",0.05f}, {"vol",0.8f});

    // ---------------------------------------------------------------- SYNTH
    ADD ("SYNTH", "Sweet Lead", {"w1",1}, {"w2",2}, {"semi2",12}, {"lvl2",0.12f}, FLT(4200,0.08f), ENV(0.015f,0.4f,0.85f,0.5f), {"lfoR",5.2f}, {"lfoP",0.06f}, {"mono",1}, {"glide",0.05f}, {"chorus",0.3f}, DLY(0.3f,333,0.4f), RV(0.35f,0.7f), {"vol",0.62f});
    ADD ("SYNTH", "Pop Whistle", {"w1",0}, {"w2",0}, {"semi2",12}, {"lvl2",0.2f}, ENV(0.03f,0.4f,0.9f,0.5f), {"lfoR",5.6f}, {"lfoP",0.14f}, {"mono",1}, {"glide",0.07f}, DLY(0.3f,500,0.4f), RV(0.3f,0.7f), {"vol",0.62f});
    ADD ("SYNTH", "Bright Stab", {"w1",2}, {"w2",1}, {"semi2",12}, {"lvl2",0.3f}, {"uni",2}, {"det",9}, FLT(2500,0.12f), FEN(0.4f,0.003f,0.25f,0.2f), ENV(0.004f,0.35f,0.25f,0.45f), {"chorus",0.3f}, DLY(0.25f,333,0.4f), RV(0.35f,0.7f), {"vol",0.6f});
    ADD ("SYNTH", "Airy Saw Lead", {"w1",2}, UNI(3,10), FLT(3800,0.1f), ENV(0.02f,0.4f,0.8f,0.6f), {"lfoR",5}, {"lfoP",0.05f}, {"mono",1}, {"glide",0.05f}, {"chorus",0.35f}, DLY(0.3f,375,0.45f), RV(0.4f,0.75f), {"vol",0.58f});
    ADD ("SYNTH", "Sunset Synth", {"w1",2}, {"w2",3}, {"semi2",-12}, {"lvl2",0.2f}, UNI(3,11), FLT(2100,0.15f), FEN(0.3f,0.01f,0.6f,0.4f), ENV(0.02f,0.5f,0.7f,0.8f), {"chorus",0.45f}, DLY(0.3f,333,0.4f), RV(0.4f,0.75f), {"vol",0.6f});
    ADD ("SYNTH", "Heart Lead", {"w1",1}, {"w2",0}, {"lvl2",0.35f}, FLT(3500,0.05f), ENV(0.02f,0.35f,0.85f,0.5f), {"lfoR",5.4f}, {"lfoP",0.07f}, {"mono",1}, {"glide",0.06f}, DLY(0.25f,375,0.4f), RV(0.35f,0.7f), {"vol",0.65f});

    // ---------------------------------------------------------------- PLUCK
    ADD ("PLUCK", "Nylon Guitar", {"w1",1}, {"w2",2}, {"semi2",12}, {"lvl2",0.13f}, FLT(850,0.1f), FEN(0.6f,0.002f,0.22f,0.05f), ENV(0.002f,0.9f,0,0.5f), {"chorus",0.12f}, DLY(0.18f,333,0.35f), RV(0.3f,0.65f), {"vol",0.65f});
    ADD ("PLUCK", "Soft Strum", {"w1",2}, {"uni",3}, {"det",9}, FLT(700,0.12f), FEN(0.55f,0.002f,0.2f,0.05f), ENV(0.003f,0.6f,0,0.4f), {"chorus",0.25f}, RV(0.3f,0.65f), {"vol",0.62f});
    ADD ("PLUCK", "Pop Pluck", {"w1",2}, {"w2",1}, {"semi2",12}, {"lvl2",0.3f}, FLT(1500,0.15f), FEN(0.5f,0.001f,0.15f,0.05f), ENV(0.001f,0.35f,0,0.3f), DLY(0.25f,333,0.4f), RV(0.3f,0.65f), {"vol",0.62f});
    ADD ("PLUCK", "Love Harp", {"w1",1}, {"w2",0}, {"semi2",12}, {"lvl2",0.5f}, FLT(3500,0.05f), ENV(0.002f,1.3f,0,1), {"chorus",0.3f}, DLY(0.3f,500,0.45f), RV(0.45f,0.8f), {"vol",0.62f});
    ADD ("PLUCK", "Sweet Pluck Short", {"w1",0}, {"w2",2}, {"semi2",12}, {"lvl2",0.12f}, FLT(2200,0.05f), ENV(0.001f,0.28f,0,0.25f), RV(0.3f,0.6f), {"vol",0.65f});
    ADD ("PLUCK", "Muted Pluck Warm", {"w1",3}, FLT(550,0.1f), FEN(0.5f,0.001f,0.12f,0.05f), ENV(0.001f,0.22f,0,0.2f), {"drive",0.08f}, RV(0.25f,0.6f), {"vol",0.65f});

    // ---------------------------------------------------------------- BELL
    ADD ("BELL", "Love Bell", {"w1",0}, {"fm",1.5f}, {"fmr",3.5f}, ENV(0.001f,2,0,1.8f), DLY(0.3f,333,0.4f), RV(0.4f,0.75f), {"vol",0.6f});
    ADD ("BELL", "Twinkle", {"w1",1}, {"w2",0}, {"semi2",24}, {"lvl2",0.3f}, {"fm",0.5f}, {"fmr",4}, ENV(0.001f,1,0,0.9f), RV(0.35f,0.7f), {"vol",0.6f});
    ADD ("BELL", "Soft Chime", {"w1",0}, {"w2",0}, {"semi2",19}, {"lvl2",0.35f}, ENV(0.001f,2.2f,0,2), {"chorus",0.2f}, DLY(0.3f,500,0.4f), RV(0.45f,0.8f), {"vol",0.6f});
    ADD ("BELL", "Pearl Bell", {"w1",0}, {"fm",1}, {"fmr",5}, ENV(0.001f,1.4f,0,1.2f), RV(0.35f,0.7f), {"vol",0.6f});

    // ---------------------------------------------------------------- KEYS
    ADD ("KEYS", "Romantic Rhodes", {"w1",0}, {"w2",0}, {"semi2",12}, {"lvl2",0.14f}, {"fm",1.2f}, {"fmr",1}, FEN(0,0.001f,0.6f,0.1f), ENV(0.003f,1.8f,0.28f,0.5f), {"drive",0.08f}, {"chorus",0.55f}, RV(0.3f,0.7f), {"vol",0.65f});
    ADD ("KEYS", "Felt Piano", {"w1",1}, {"w2",0}, {"lvl2",0.2f}, {"fm",0.4f}, {"fmr",3}, FLT(2200,0.05f), ENV(0.003f,1.6f,0.1f,0.6f), {"lofi",0.12f}, RV(0.3f,0.65f), {"vol",0.65f});
    ADD ("KEYS", "Dreamy Keys", {"w1",0}, {"w2",1}, {"lvl2",0.3f}, {"fm",0.9f}, {"fmr",1}, ENV(0.003f,2,0.35f,0.8f), {"chorus",0.65f}, DLY(0.3f,500,0.45f), RV(0.45f,0.8f), {"vol",0.65f});
    ADD ("KEYS", "Wurli Love", {"w1",1}, {"w2",3}, {"semi2",12}, {"lvl2",0.14f}, FLT(1800,0.1f), ENV(0.003f,1.2f,0.3f,0.4f), {"drive",0.12f}, {"chorus",0.4f}, RV(0.3f,0.65f), {"vol",0.65f});
    ADD ("KEYS", "Bright Piano", {"w1",2}, {"w2",1}, {"semi2",12}, {"lvl2",0.2f}, {"fm",0.6f}, {"fmr",2}, FLT(4500,0.05f), ENV(0.002f,1.4f,0.1f,0.5f), RV(0.3f,0.65f), {"vol",0.62f});
    ADD ("KEYS", "Chill EP", {"w1",0}, {"w2",1}, {"semi2",12}, {"lvl2",0.2f}, {"fm",0.8f}, {"fmr",2}, ENV(0.003f,1.6f,0.3f,0.6f), {"lfoR",4.5f}, {"lfoA",0.1f}, {"chorus",0.5f}, RV(0.35f,0.7f), {"vol",0.65f});

    // ---------------------------------------------------------------- MALLET
    ADD ("MALLET", "Soft Marimba", {"w1",0}, {"fm",1.6f}, {"fmr",4}, FEN(0,0.001f,0.1f,0), ENV(0.001f,0.55f,0,0.35f), DLY(0.2f,333,0.35f), RV(0.3f,0.65f), {"vol",0.65f});
    ADD ("MALLET", "Warm Vibes", {"w1",0}, {"fm",0.8f}, {"fmr",4}, ENV(0.002f,2,0,1.2f), {"lfoR",5}, {"lfoA",0.35f}, RV(0.35f,0.7f), {"vol",0.62f});
    ADD ("MALLET", "Kalimba Love 2", {"w1",0}, {"fm",2}, {"fmr",3}, FEN(0,0.001f,0.2f,0), ENV(0.001f,1,0,0.8f), DLY(0.3f,333,0.4f), RV(0.35f,0.7f), {"vol",0.65f});
    ADD ("MALLET", "Steel Drum Soft", {"w1",0}, {"w2",0}, {"semi2",12}, {"lvl2",0.3f}, {"fm",1.3f}, {"fmr",1.5f}, ENV(0.002f,0.8f,0,0.6f), {"chorus",0.25f}, RV(0.3f,0.65f), {"vol",0.62f});
    ADD ("MALLET", "Glockenspiel Pop", {"w1",1}, {"w2",0}, {"semi2",24}, {"lvl2",0.3f}, {"fm",0.6f}, {"fmr",4}, ENV(0.001f,0.8f,0,0.7f), RV(0.35f,0.7f), {"vol",0.6f});
    ADD ("MALLET", "Wooden Marimba", {"w1",0}, {"w2",1}, {"semi2",12}, {"lvl2",0.2f}, {"fm",2.2f}, {"fmr",4}, FEN(0,0.001f,0.08f,0), ENV(0.001f,0.4f,0,0.25f), FLT(2800,0.05f), RV(0.25f,0.6f), {"vol",0.65f});

    // ---------------------------------------------------------------- STRINGS
    ADD ("STRINGS", "Warm Strings", {"w1",2}, UNI(5,11), FLT(2600,0.08f), ENV(0.5f,1,0.9f,1.6f), {"lfoR",5.2f}, {"lfoP",0.04f}, {"chorus",0.45f}, RV(0.45f,0.78f), {"vol",0.6f});
    ADD ("STRINGS", "Love Violins", {"w1",2}, UNI(4,10), FLT(3500,0.1f), FEN(0.15f,0.2f,1,0.8f), ENV(0.3f,1,0.9f,1.4f), {"lfoR",5.5f}, {"lfoP",0.06f}, {"chorus",0.35f}, RV(0.5f,0.8f), {"vol",0.6f});
    ADD ("STRINGS", "Soft Cello", {"w1",2}, {"w2",1}, {"semi2",-12}, {"lvl2",0.3f}, {"uni",3}, {"det",7}, FLT(1100,0.1f), ENV(0.3f,1,0.9f,1.2f), {"lfoR",5}, {"lfoP",0.05f}, {"mono",1}, {"glide",0.05f}, RV(0.4f,0.75f), {"vol",0.62f});
    ADD ("STRINGS", "Ballad Ensemble", {"w1",2}, UNI(7,14), FLT(2800,0.08f), ENV(0.7f,1,0.9f,2), {"lfoR",5.4f}, {"lfoP",0.04f}, {"chorus",0.5f}, RV(0.5f,0.82f), {"vol",0.56f});
    ADD ("STRINGS", "Pizzicato Pop", {"w1",2}, {"uni",2}, {"det",7}, FLT(1400,0.1f), FEN(0.5f,0.001f,0.12f,0.05f), ENV(0.001f,0.25f,0,0.2f), RV(0.3f,0.65f), {"vol",0.65f});
    ADD ("STRINGS", "Tremolo Love", {"w1",2}, UNI(5,10), FLT(2400,0.08f), ENV(0.3f,1,0.9f,1.5f), {"lfoR",6.5f}, {"lfoA",0.5f}, {"chorus",0.35f}, RV(0.45f,0.78f), {"vol",0.6f});
    ADD ("STRINGS", "Silk Strings", {"w1",1}, {"w2",2}, {"semi2",12}, {"lvl2",0.25f}, UNI(5,12), FLT(3200,0.08f), ENV(0.6f,1,0.9f,1.8f), {"lfoR",5}, {"lfoP",0.03f}, {"chorus",0.5f}, RV(0.5f,0.8f), {"vol",0.58f});
    ADD ("STRINGS", "Soft Quartet", {"w1",2}, {"w2",2}, {"semi2",7}, {"lvl2",0.3f}, {"uni",3}, {"det",8}, FLT(2300,0.1f), ENV(0.4f,1,0.9f,1.5f), {"lfoR",5.3f}, {"lfoP",0.05f}, {"chorus",0.4f}, RV(0.45f,0.78f), {"vol",0.6f});

    // ---------------------------------------------------------------- RISER
    ADD ("RISER", "Soft Rise", {"lvl1",0}, {"noise",0.6f}, {"ftype",1}, FLT(400,0.3f), FEN(1,4,1,1), ENV(3,1,1,1.5f), RV(0.4f,0.75f), {"vol",0.85f});
    ADD ("RISER", "Pad Swell", {"w1",2}, UNI(5,16), FLT(500,0.15f), FEN(0.9f,3,1,1), ENV(3,1,1,2), {"chorus",0.4f}, RV(0.5f,0.82f), {"vol",0.55f});
    ADD ("RISER", "Air Uplifter", {"lvl1",0}, {"noise",0.5f}, {"ftype",2}, FLT(800,0.25f), FEN(0.8f,2.5f,1,1), ENV(2,1,1,1), RV(0.35f,0.7f), {"vol",0.85f});
    ADD ("RISER", "Pitch Climb", {"w1",1}, {"w2",2}, {"lvl2",0.3f}, {"pEnv",-12}, {"pDec",3}, FLT(2000,0.1f), ENV(2,1,1,1.2f), RV(0.4f,0.75f), {"vol",0.6f});
    ADD ("RISER", "Soft Downlifter", {"lvl1",0}, {"noise",0.6f}, {"ftype",1}, FLT(5000,0.3f), FEN(-0.8f,0.01f,2.5f,0), ENV(0.02f,2.5f,0,1), RV(0.4f,0.75f), {"vol",0.85f});
    ADD ("RISER", "Love Impact", {"w1",0}, {"noise",0.25f}, FLT(1200,0.1f), {"pEnv",30}, {"pDec",0.25f}, ENV(0.001f,2.5f,0,1.2f), RV(0.45f,0.82f), {"vol",0.75f});

    // ---------------------------------------------------------------- ARP
    ADD ("ARP", "Pop Arp", {"w1",2}, {"w2",1}, {"semi2",12}, {"lvl2",0.3f}, FLT(1800,0.12f), FEN(0.5f,0.002f,0.15f,0.05f), ENV(0.002f,0.25f,0,0.3f), DLY(0.3f,333,0.4f), RV(0.35f,0.7f), {"vol",0.6f});
    ADD ("ARP", "Sweet Bell Arp", {"w1",0}, {"fm",1}, {"fmr",3.5f}, ENV(0.001f,0.5f,0,0.4f), DLY(0.35f,333,0.45f), RV(0.35f,0.7f), {"vol",0.6f});
    ADD ("ARP", "Glow Arp", {"w1",1}, {"w2",0}, {"semi2",12}, {"lvl2",0.45f}, ENV(0.002f,0.45f,0,0.4f), {"chorus",0.3f}, DLY(0.35f,333,0.45f), RV(0.4f,0.75f), {"vol",0.6f});
    ADD ("ARP", "Pluck Arp Warm", {"w1",2}, {"uni",2}, {"det",8}, FLT(900,0.15f), FEN(0.55f,0.001f,0.12f,0.05f), ENV(0.001f,0.22f,0,0.25f), DLY(0.3f,333,0.4f), RV(0.35f,0.7f), {"vol",0.62f});
    ADD ("ARP", "Square Tender", {"w1",3}, FLT(1100,0.15f), FEN(0.5f,0.001f,0.12f,0.05f), ENV(0.001f,0.2f,0,0.2f), DLY(0.3f,333,0.4f), RV(0.3f,0.65f), {"vol",0.58f});
    ADD ("ARP", "Dream Pluck Arp", {"w1",0}, {"w2",2}, {"semi2",12}, {"lvl2",0.12f}, {"fm",0.6f}, {"fmr",2}, ENV(0.001f,0.4f,0,0.4f), {"chorus",0.3f}, DLY(0.4f,375,0.5f), RV(0.45f,0.8f), {"vol",0.6f});

    // ---------------------------------------------------------------- VOX
    ADD ("VOX", "Soft Ooh", {"w1",2}, UNI(4,10), {"ftype",1}, FLT(600,0.4f), ENV(0.4f,1,0.9f,1.8f), {"lfoR",5},{"lfoP",0.06f}, {"chorus",0.35f}, RV(0.45f,0.8f), {"vol",0.7f});
    ADD ("VOX", "Sweet Ahh", {"w1",2}, UNI(5,12), {"ftype",1}, FLT(1200,0.4f), ENV(0.5f,1,0.9f,2), {"lfoR",5.2f}, {"lfoP",0.07f}, {"chorus",0.35f}, RV(0.5f,0.82f), {"vol",0.7f});
    ADD ("VOX", "Breathy Whisper", {"w1",2}, {"noise",0.22f}, {"ftype",1}, FLT(1000,0.35f), ENV(0.3f,1,0.9f,1.4f), RV(0.45f,0.8f), {"vol",0.7f});
    ADD ("VOX", "Choir Love", {"w1",2}, UNI(6,15), {"noise",0.05f}, {"ftype",1}, FLT(900,0.45f), ENV(0.8f,1,0.9f,2.5f), {"lfoR",4.8f}, {"lfoP",0.08f}, {"chorus",0.45f}, RV(0.55f,0.85f), {"vol",0.68f});

#undef ADD
}
