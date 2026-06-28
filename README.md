# Low-Cost Integrated 3-in-1 Water Quality Monitoring Subsystem

A production-optimized hardware and software architecture designed to evaluate **pH, Turbidity, and Total Dissolved Solids (TDS)** simultaneously inside a single inline pipeline block. 

By bypassing expensive retail breakout modules and designing analog conditioning layers directly around raw silicon, the absolute production bill of materials (BOM) sits **under $4.50 (~Rs. 1,350 LKR)**.

---

## 🚀 Key Engineering Innovations
* **Dual-Channel High-Impedance Buffering:** Uses a single, low-cost **TL072 JFET-input Op-Amp IC** to isolate and read fragile millivolt variations directly from a raw glass pH electrode without signal degradation.
* **The 2.5V Virtual Ground Shift:** Solves the challenge of microcontrollers being blind to negative voltages. By lifting the probe baseline to a 2.5V floor, the electrochemical output ($\pm414\text{ mV}$) is safely scaled into an entirely positive, readable window ($1.5\text{V} - 3.5\text{V}$).
* **Unified Optical/Electrochemical Block:** Houses a 90°/180° dual-angle optical turbidity path, an industrial PG13.5-gland-sealed glass pH electrode, and biochemically inert 316L stainless steel conductivity pins inside a compact 10cm footprint.

---

## 📋 System Bill of Materials (BOM)

| Component | Engineering Role | Wholesale Cost (USD) | Local Retail Baseline (LKR) |
| :--- | :--- | :--- | :--- |
| **E-201-C Glass Probe** | Raw Electrochemical Input | $1.80 | ~Rs. 2,500 (Retail Single) |
| **TL072 IC** | Dual FET-Input Signal Buffer | $0.15 | ~Rs. 70 |
| **PG13.5 Gland** | Monolithic Pipe Leak-Proof Seal | $0.20 | ~Rs. 150 |
| **Optics & TDS** | 940nm IR + Phototransistors + 316L Pins| $0.45 | ~Rs. 250 |
| **Passives & PCB Space** | Resistors, Caps, Prototyping Space | $0.50 | ~Rs. 150 |
| **TOTAL BOM COST** | **Target Production Architecture** | **~$3.10** | **Optimized Prototype Stage** |

---

## 🔌 Hardware Schematics: The pH Buffer Stage
