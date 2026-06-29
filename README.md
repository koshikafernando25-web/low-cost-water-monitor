# Low-Cost Integrated 2-in-1 Water Quality Monitoring Subsystem

A production-optimized hardware and software architecture designed to evaluate **pH and Turbidity** simultaneously inside a single inline pipeline block. 

By bypassing expensive retail breakout modules, removing cross-talk interference, and designing analog conditioning layers directly around raw silicon, the absolute production bill of materials (BOM) is optimized to sit **under $3.50 (~Rs. 1,050 LKR)**.

---

## 🚀 Key Engineering Innovations
* **Dual-Channel High-Impedance Buffering:** Uses a single, low-cost **TL072 JFET-input Op-Amp IC** to isolate and read fragile millivolt variations directly from a raw glass pH electrode without signal degradation, while handling the optical transit calculations on its secondary channel.
* **The 2.5V Virtual Ground Shift:** Solves the challenge of microcontrollers being blind to negative voltages. By lifting the probe baseline to a 2.5V floor, the electrochemical output ($\pm414\text{ mV}$) is safely scaled into an entirely positive, readable window ($1.5\text{V} - 3.5\text{V}$).
* **Isolated Optical/Electrochemical Block:** Houses a 90°/180° dual-angle optical turbidity path and an industrial PG13.5-gland-sealed glass pH electrode inside a compact 10cm footprint. Stray currents are eliminated by intentionally omitting direct immersion electrical conductivity (TDS) networks.

---

## 📋 System Bill of Materials (BOM)

| Component | Engineering Role | Wholesale Cost (USD) | Local Retail Baseline (LKR) |
| :--- | :--- | :--- | :--- |
| **E-201-C Glass Probe** | Raw Electrochemical Input | $1.80 | ~Rs. 2,500 (Retail Single) |
| **TL072 IC** | Dual FET-Input Signal Buffer | $0.15 | ~Rs. 70 |
| **PG13.5 Gland** | Monolithic Pipe Leak-Proof Seal | $0.20 | ~Rs. 150 |
| **Optics Array** | 940nm IR Emitting Diode + Phototransistors | $0.25 | ~Rs. 120 |
| **Passives & Board** | Resistors, Caps, Prototyping Space | $0.40 | ~Rs. 120 |
| **TOTAL BOM COST** | **Target Production Architecture** | **~$2.80** | **Optimized Prototype Stage** |

---

## 🔌 Hardware Schematics: The 2-in-1 Processing Array

```text
                       +5V Power Rail ────────────────────────┬──────────────────────┐
                                                              │                      │
                                                        [10k Resistor]         (Pin 8 - VCC)
                                                              │                      │
                                                              ├──────────────┐  ┌────┴────┐
     [ RAW STRIPPED CABLE ]                                   │              │  │  TL072  │
    ┌──────────────────────┐                                  ├─(+)          └──┤3 (In+)  │
    │ Outer Shield Mesh ───┼──────────────────────────────────┤  [10uF Cap]     │         │
    ├──────────────────────┤                                  ├─(-)          ┌──┤2 (In-)  │
    │ Inner Core Wire ─────┼────────┐                         │              │  │         │
    └──────────────────────┘        │                     [10k Resistor]     └──┤1 (Out)──┼──► To MCU
                                    │                         │                 └─────────┘    Analog Pin 34
                                    │                         │                      │
       System Ground (0V) ──────────┴─────────────────────────┴──────────────────────(Pin 4 - GND)
