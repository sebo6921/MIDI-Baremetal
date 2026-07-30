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

- Onboard DAC output on PA4/PA5 (button and LED need to move to new pins first, since those are the DAC pins)
- RC low-pass filter, DC-blocking cap, and 3.5mm jack, to get clean analog audio out
  - Parts: 1kΩ resistor, 10nF ceramic cap x2, 10µF tantalum cap (mind the polarity, positive leg toward the DAC side)
- microSD card over SPI (FatFS) for sample storage
- Pad matrix (row/column scan) to replace the 3 single-EXTI buttons, since that approach doesn't scale past a handful of pins
- LCD (I2C 16x2 to start) for a sample-select menu

### Build order 

1. **DAC + Timer/DMA test tone.** Hardcoded buffer, no SD card yet. Proves the audio output path works on its own.
2. **SD card + FatFS.** Read and parse a WAV file, verify contents over UART. No DAC involved yet.
3. **Combine 1 and 2.** Stream real PCM from the SD card into the DAC via double-buffered DMA.
4. **Pad matrix scanning.**
5. **LCD menu.** Browse the SD card, assign a sample to a pad.
6. **Beat recording engine.** A step sequencer (tempo timer plus a per-step bitmask of which pad fired), not audio recording.

### Planned effects (after the core sampler works)

- **Pitch shift per voice.** Resample via a fractional phase accumulator plus linear interpolation. Speed and pitch are coupled (the "record slowed down" sound, same as MPC or SP-404 style samplers).
- **Delay/echo** on the mixed output first. Real reverb (parallel comb plus allpass filters) later if wanted. True reverb costs meaningful RAM, roughly 3.5KB per 40ms of delay at 22kHz, so it's a deliberate later upgrade, not part of the initial v2 build.


*Last updated: July 15, 2026. Update this as v2 progresses.*
