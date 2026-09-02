# STM32F446RE Groovebox

Bare-metal STM32F446RE project. Started as a MIDI controller (v1), now moving into a standalone dawless sampler/groovebox (v2). No HAL, register-level throughout.

## Status: v1 complete, v2 in progress

---

## v1: MIDI controller (done)

- Bare-metal C/C++, register-level, no HAL
- 3 buttons on PA4, PB7, PC8, each on its own EXTI line, debounced in the ISR
- Sends real MIDI Note On messages (0x90) over UART3 via a ring buffer TX
- Onboard LED (PA5) toggles on note trigger

---

## v2: Dawless groovebox (in progress)
<img width="670" height="830" alt="image" src="https://github.com/user-attachments/assets/b22c2c84-bd1e-4494-a1c6-cdffcf9c0944" />

**Goal:** turn this from a MIDI controller that needs a computer or DAW into a standalone box. Load sample sounds onto it, assign them to pads, play them, and record a beat, all with no computer involved.

### What v2 adds, hardware-wise

v2: Dawless groovebox (in progress)

Goal: turn this from a MIDI controller that needs a computer or DAW into a standalone box. Load sample sounds onto it, assign them to pads, play them, and record a beat, all with no computer involved.


### Planned effects (after the core sampler works)

- **Pitch shift per voice.** Resample via a fractional phase accumulator plus linear interpolation. Speed and pitch are coupled (the "record slowed down" sound, same as MPC or SP-404 style samplers).
- **Delay/echo** on the mixed output first. Real reverb (parallel comb plus allpass filters) later if wanted. True reverb costs meaningful RAM, roughly 3.5KB per 40ms of delay at 22kHz, so it's a deliberate later upgrade, not part of the initial v2 build.


*Last updated: July 15, 2026. Update this as v2 progresses.*
