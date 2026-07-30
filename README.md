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

What v2 adds, hardware-wise
PCM5102A I2S DAC module for audio output (switched from the onboard DAC to get better resolution, a lower noise floor, and built-in output filtering)
Talks over I2S2: PB12 = LCK (word select), PB13 = BCK (bit clock), PB15 = DIN (data)
Other module pins are hardwired once and left alone: SCK → GND, FMT → GND, FLT → GND, DEMP → GND, XSMT → 3.3V (important, this one mutes the output if left floating or grounded)
Board comes with its own 3.5mm jack, no separate RC filter or DC-blocking cap needed this time
Since this uses PB12/13/15 instead of the onboard DAC, PA4 and PA5 no longer need to move, the existing button and LED stay right where they are
microSD card over SPI (FatFS) for sample storage
Pad matrix (row/column scan) to replace the 3 single-EXTI buttons, since that approach doesn't scale past a handful of pins
LCD (I2C 16x2 to start) for a sample-select menu

### Planned effects (after the core sampler works)

- **Pitch shift per voice.** Resample via a fractional phase accumulator plus linear interpolation. Speed and pitch are coupled (the "record slowed down" sound, same as MPC or SP-404 style samplers).
- **Delay/echo** on the mixed output first. Real reverb (parallel comb plus allpass filters) later if wanted. True reverb costs meaningful RAM, roughly 3.5KB per 40ms of delay at 22kHz, so it's a deliberate later upgrade, not part of the initial v2 build.


*Last updated: July 15, 2026. Update this as v2 progresses.*
