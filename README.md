# Embedded Training Journey

This is my personal training repository containing a structured full-time curriculum built while job searching to bridge the gap between STM32 support/validation work and embedded software development.
 
Each phase lives in its own folder. Phases 1 and 2 contain weekly exercise folders for isolated concept work. From Phase 3 onward, all work lives in a single evolving `project/` named after the capstone and grows into it eventually.
 
The companion site documenting the full curriculum from weekly breakdowns, code references, hardware BOM, and interview prep can be found it at **[blackthreatt.github.io/embedded-training](https://blackthreatt.github.io/embedded-training)**.
 
---

## Structure
 
```
embedded-training/
  phase-1/                     ← Foundations (6 weeks)
    week1/                    ← Exercises: pointers, memory model, UB
    week2/                    ← Exercises: volatile, layered UART driver
    stm32-cli-driver/         ← Evolving codebase from week 3 → capstone
      Makefile
      README.md
 
  phase-2/                     ← RTOS and real-time design (8 weeks)
    project/
      Makefile
      README.md
 
  phase-3/                     ← Bootloader design (9 weeks)
    project/ 
      Makefile
      README.md
 
  phase-4/                     ← CAN bus and automotive protocols (9 weeks)
    project/
      Makefile
      README.md
 
  phase-5/                     ← Professional readiness (5 weeks)
    README.md
  
  LICENSE
  README.md
```
---

## Build 

Every phase project contains a `Makefile` used to ease the compilation with `arm-none-eabi-gcc`.

---
 
## Related
 
- **Curriculum site:** [BlackThreatt.Github.io](https://blackthreatt.github.io) contains full week-by-week breakdown, code reference, hardware BOM...
- **Blog:** This is where you will find technical posts I publish from each phase: documenting encountered concepts, bugs, or tips and tricks...

---
 
*Mohamed Ali Bessaidi · [linkedin.com/in/MohamedABessaidi](https://linkedin.com/in/MohamedABessaidi) · BessaidiMohamedAli99@gmail.com*

