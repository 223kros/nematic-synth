// SAMPLER: texturas granulares. Cada sonido usa una fuente (0-7 incluidas, 8 = TU SAMPLE) cortada en granos.
// Fuentes: 0 Choir Air, 1 Glass Bells, 2 Warm Pad, 3 Vinyl Dust, 4 Rain Wash, 5 Sub Drone, 6 Tropical Pluck, 7 Space Shimmer, 8 Tu sample.
inline void addSamplerPresets (std::vector<Preset>& L)
{
// G(fuente, posicion, azar de posicion, tamano de grano ms, densidad granos/seg)
#define G(src, pos, posr, size, dens) {"lvl1",0}, {"gMix",1}, {"gSrc",src}, {"gPos",pos}, {"gPosR",posr}, {"gSize",size}, {"gDens",dens}
#define ADD(cat, name, ...) L.push_back (mk (3, cat, name, { __VA_ARGS__ }))

    // ---------------------------------------------------------------- CLOUD (nubes suaves)
    ADD ("CLOUD", "Choir Cloud", G(0,0.3f,0.3f,250,30), {"gShape",0.2f}, ENV(1.5f,1,0.9f,3), {"chorus",0.4f}, RV(0.6f,0.9f), {"vol",0.7f});
    ADD ("CLOUD", "Warm Cloud", G(2,0.4f,0.4f,300,28), {"gShape",0.15f}, FLT(4500,0.05f), ENV(1.8f,1,0.9f,3.5f), {"chorus",0.5f}, RV(0.6f,0.9f), {"vol",0.7f});
    ADD ("CLOUD", "Bell Cloud", G(1,0.4f,0.6f,300,20), {"gShape",0.25f}, ENV(1,1,0.9f,3), DLY(0.3f,420,0.5f), RV(0.65f,0.92f), {"vol",0.7f});
    ADD ("CLOUD", "Pad Fog", G(2,0.5f,0.6f,420,40), {"gShape",0.1f}, FLT(2600,0.1f), ENV(2.5f,1,0.9f,4), {"chorus",0.6f}, RV(0.75f,0.94f), {"vol",0.7f});
    ADD ("CLOUD", "Rain Cloud", G(4,0.5f,0.8f,200,40), {"gKey",0}, {"gSpr",1}, ENV(1.5f,1,0.9f,3), RV(0.7f,0.93f), {"vol",0.8f});
    ADD ("CLOUD", "Summer Cloud", G(6,0.35f,0.5f,260,22), {"gShape",0.2f}, {"chorus",0.4f}, ENV(1.2f,1,0.9f,3), DLY(0.25f,333,0.45f), RV(0.6f,0.88f), {"vol",0.7f});
    ADD ("CLOUD", "Your Sample Cloud", G(8,0.4f,0.4f,260,30), {"gShape",0.2f}, {"gKey",1}, ENV(1,1,0.9f,3), {"chorus",0.4f}, RV(0.6f,0.9f), {"vol",0.7f});
    ADD ("CLOUD", "Silk Cloud", G(0,0.2f,0.2f,350,35), {"gShape",0.1f}, {"gPitch",-12}, FLT(2400,0.05f), ENV(2,1,0.9f,3.5f), {"chorus",0.5f}, RV(0.65f,0.92f), {"vol",0.7f});

    // ---------------------------------------------------------------- SHIMMER (octava arriba, brillo)
    ADD ("SHIMMER", "Angel Shimmer", G(7,0.4f,0.5f,300,30), {"gPitch",12}, {"gScat",8}, {"gShape",0.15f}, ENV(1.5f,1,0.9f,4), {"chorus",0.5f}, DLY(0.3f,500,0.5f), RV(0.75f,0.95f), {"vol",0.65f});
    ADD ("SHIMMER", "Choir Octave Up", G(0,0.3f,0.4f,260,32), {"gPitch",12}, {"gScat",10}, ENV(1.2f,1,0.9f,3.5f), {"chorus",0.4f}, RV(0.7f,0.94f), {"vol",0.65f});
    ADD ("SHIMMER", "Glass Rain", G(1,0.5f,0.8f,70,60), {"gPitch",12}, {"gScat",15}, {"gSpr",1}, ENV(0.5f,1,0.9f,3), DLY(0.35f,375,0.55f), RV(0.7f,0.94f), {"vol",0.65f});
    ADD ("SHIMMER", "Fifth Shimmer", G(7,0.5f,0.4f,350,28), {"gPitch",7}, {"gScat",6}, ENV(2,1,0.9f,4), {"chorus",0.55f}, RV(0.8f,0.96f), {"vol",0.65f});
    ADD ("SHIMMER", "Starlight", G(7,0.2f,0.7f,120,50), {"gPitch",19}, {"gScat",20}, {"gSpr",1}, ENV(1.5f,1,0.9f,4), DLY(0.4f,420,0.55f), RV(0.8f,0.96f), {"vol",0.6f});
    ADD ("SHIMMER", "Double Octave", G(1,0.3f,0.5f,200,35), {"gPitch",24}, {"gScat",10}, ENV(1,1,0.9f,3.5f), {"chorus",0.4f}, RV(0.75f,0.95f), {"vol",0.6f});

    // ---------------------------------------------------------------- TEXTURE
    ADD ("TEXTURE", "Vinyl Dust Bed", G(3,0.5f,0.9f,80,30), {"gKey",0}, {"gSpr",1}, ENV(0.8f,1,1,2), {"lofi",0.15f}, RV(0.3f,0.7f), {"vol",0.9f});
    ADD ("TEXTURE", "Rain Wash", G(4,0.4f,0.9f,300,35), {"gKey",0}, {"gSpr",1}, FLT(6000,0.1f), ENV(2,1,1,3), RV(0.7f,0.93f), {"vol",0.85f});
    ADD ("TEXTURE", "Crackle Drift", G(3,0.2f,0.5f,40,45), {"gKey",0}, {"gScan",0.4f}, {"gScat",300}, ENV(0.5f,1,1,2), RV(0.4f,0.75f), {"vol",0.9f});
    ADD ("TEXTURE", "Space Dust", G(7,0.5f,1,60,70), {"gScat",600}, {"gSpr",1}, ENV(1.5f,1,0.9f,3.5f), {"chorus",0.4f}, RV(0.8f,0.96f), {"vol",0.65f});
    ADD ("TEXTURE", "Grain Fog", G(2,0.5f,1,180,60), {"gScat",120}, {"gShape",0.5f}, FLT(3000,0.1f), ENV(2,1,0.9f,4), {"chorus",0.5f}, RV(0.8f,0.96f), {"vol",0.7f});
    ADD ("TEXTURE", "Tape Ghosts", G(0,0.3f,0.7f,150,25), {"gScat",50}, {"gRev",0.4f}, {"lofi",0.2f}, ENV(1.5f,1,0.9f,3.5f), DLY(0.3f,480,0.5f), RV(0.7f,0.93f), {"vol",0.7f});

    // ---------------------------------------------------------------- PLUCK (granos cortos, tocables)
    ADD ("PLUCK", "Tropical Grains", G(6,0.2f,0.1f,120,12), {"gShape",0.4f}, ENV(0.002f,0.7f,0,0.6f), DLY(0.3f,333,0.4f), RV(0.4f,0.75f), {"vol",0.7f});
    ADD ("PLUCK", "Pluck Cloud", G(6,0.3f,0.4f,250,25), {"gShape",0.3f}, ENV(0.005f,1,0.4f,0.8f), {"chorus",0.3f}, RV(0.5f,0.82f), {"vol",0.7f});
    ADD ("PLUCK", "Bell Scatter", G(1,0.4f,0.8f,90,10), {"gShape",0.4f}, {"gSpr",1}, ENV(0.003f,1.2f,0,1), DLY(0.4f,375,0.5f), RV(0.6f,0.9f), {"vol",0.7f});
    ADD ("PLUCK", "Sparkle Pluck", G(1,0.3f,0.2f,60,18), {"gPitch",12}, {"gShape",0.6f}, ENV(0.002f,0.6f,0,0.6f), DLY(0.35f,333,0.5f), RV(0.5f,0.85f), {"vol",0.65f});
    ADD ("PLUCK", "Your Sample Pluck", G(8,0.2f,0.1f,100,14), {"gShape",0.5f}, ENV(0.002f,0.8f,0,0.6f), DLY(0.3f,333,0.4f), RV(0.45f,0.8f), {"vol",0.7f});

    // ---------------------------------------------------------------- KEYS (sonido continuo, tocable en el teclado)
    ADD ("KEYS", "Grain Keys Choir", G(0,0.3f,0.05f,180,40), {"gShape",0.7f}, ENV(0.05f,1,0.9f,1.5f), {"chorus",0.3f}, RV(0.5f,0.82f), {"vol",0.7f});
    ADD ("KEYS", "Grain Keys Warm", G(2,0.4f,0.05f,200,40), {"gShape",0.6f}, FLT(3500,0.05f), ENV(0.08f,1,0.9f,1.8f), {"chorus",0.4f}, RV(0.5f,0.82f), {"vol",0.7f});
    ADD ("KEYS", "Glass Grain Keys", G(1,0.35f,0.1f,120,30), {"gShape",0.6f}, ENV(0.02f,1.2f,0.5f,1.2f), DLY(0.3f,375,0.45f), RV(0.55f,0.85f), {"vol",0.7f});
    ADD ("KEYS", "Your Sample Keys", G(8,0.4f,0.05f,160,40), {"gShape",0.6f}, ENV(0.05f,1,0.9f,1.5f), {"chorus",0.3f}, RV(0.5f,0.82f), {"vol",0.7f});

    // ---------------------------------------------------------------- DRONE (oscuro, profundo)
    ADD ("DRONE", "Sub Cloud Drone", G(5,0.5f,0.3f,500,30), {"gPitch",-12}, {"gShape",0.1f}, FLT(1200,0.1f), ENV(3,1,1,6), RV(0.8f,0.96f), {"vol",0.85f});
    ADD ("DRONE", "Dark Choir Drone", G(0,0.4f,0.4f,600,25), {"gPitch",-12}, {"gShape",0.1f}, FLT(1800,0.1f), ENV(3,1,1,6), {"chorus",0.5f}, RV(0.85f,0.97f), {"vol",0.8f});
    ADD ("DRONE", "Slow Scan Pad", G(2,0.1f,0.1f,400,35), {"gScan",0.15f}, {"gShape",0.1f}, ENV(3,1,1,5), {"chorus",0.5f}, RV(0.8f,0.96f), {"vol",0.7f});
    ADD ("DRONE", "Frozen Bell", G(1,0.35f,0.02f,500,25), {"gShape",0.1f}, {"gPitch",-5}, ENV(3,1,1,6), RV(0.85f,0.97f), {"vol",0.75f});

    // ---------------------------------------------------------------- GLITCH
    ADD ("GLITCH", "Stutter Bells", G(1,0.4f,0.3f,30,50), {"gScat",400}, {"gRev",0.3f}, {"gShape",0.8f}, ENV(0.002f,1,0.7f,0.6f), DLY(0.4f,250,0.5f), RV(0.4f,0.75f), {"vol",0.65f});
    ADD ("GLITCH", "Reverse Bells", G(1,0.4f,0.3f,250,20), {"gRev",1}, {"gShape",0.2f}, ENV(0.8f,1,0.9f,2.5f), DLY(0.3f,420,0.5f), RV(0.7f,0.94f), {"vol",0.7f});
    ADD ("GLITCH", "Scan Choir", G(0,0.1f,0.05f,100,45), {"gScan",0.45f}, {"gShape",0.5f}, ENV(0.4f,1,0.9f,2.5f), {"chorus",0.4f}, RV(0.65f,0.92f), {"vol",0.7f});
    ADD ("GLITCH", "Micro Freeze", G(6,0.3f,0.01f,35,70), {"gShape",0.8f}, {"gSpr",1}, ENV(0.01f,1,0.9f,0.8f), DLY(0.3f,333,0.4f), RV(0.5f,0.82f), {"vol",0.65f});
    ADD ("GLITCH", "Chaos Grains", G(1,0.5f,1,25,90), {"gScat",900}, {"gRev",0.5f}, {"gSpr",1}, {"gShape",0.8f}, ENV(0.01f,1,0.9f,1), RV(0.55f,0.85f), {"vol",0.6f});
    ADD ("GLITCH", "Your Sample Glitch", G(8,0.4f,0.3f,40,45), {"gScat",300}, {"gRev",0.3f}, {"gShape",0.7f}, ENV(0.005f,1,0.8f,0.8f), DLY(0.35f,333,0.45f), RV(0.5f,0.82f), {"vol",0.7f});

#undef ADD
#undef G
}
