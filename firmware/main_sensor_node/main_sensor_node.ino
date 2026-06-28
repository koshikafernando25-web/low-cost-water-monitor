/*
 * Low-Cost Integrated 3-in-1 Water Quality Monitoring Subsystem
 * Simultaneous Processing Engine: pH, Turbidity, and TDS
 */

// Hardware Pin Definitions
const int PH_ANALOG_PIN = 34;         // TL072 Pin 1 (pH Buffer Output)
const int TURBIDITY_ANALOG_PIN = 35;  // TL072 Pin 7 (Turbidity Photo-Receiver Output)
const int TDS_ANALOG_PIN = 36;        // Connected directly to one of the 316L SS Pins

// System Variables
const int ADC_RESOLUTION = 4095;      // 12-bit ADC for ESP32
const float VREF = 3.3;               // ADC Operating Voltage

// Calibration Parameters
const float V_VIRTUAL_GROUND = 2.50;  // 2.5V reference floor for pH
const float NERNST_SLOPE = 0.05916;   // Nernst shift per pH unit at 25°C

void setup() {
    Serial.begin(115200);
    pinMode(PH_ANALOG_PIN, INPUT);
    pinMode(TURBIDITY_ANALOG_PIN, INPUT);
    pinMode(TDS_ANALOG_PIN, INPUT);
    Serial.println("--- 3-in-1 Monolithic Subsystem Active ---");
}

void loop() {
    // ==========================================
    // 1. pH SUBSYSTEM SAMPLING (Electrochemical)
    // ==========================================
    long ph_acc = 0;
    for (int i = 0; i < 32; i++) ph_acc += analogRead(PH_ANALOG_PIN);
    float v_ph = (ph_acc / 32.0 / ADC_RESOLUTION) * VREF;
    float relative_probe_mv = (v_ph - V_VIRTUAL_GROUND);
    float calculated_ph = 7.0 - (relative_probe_mv / NERNST_SLOPE);
    if (calculated_ph < 0.0) calculated_ph = 0.0;
    if (calculated_ph > 14.0) calculated_ph = 14.0;

    // ==========================================
    // 2. TURBIDITY SUBSYSTEM SAMPLING (Optical)
    // ==========================================
    long turb_acc = 0;
    for (int i = 0; i < 32; i++) turb_acc += analogRead(TURBIDITY_ANALOG_PIN);
    float v_turb = (turb_acc / 32.0 / ADC_RESOLUTION) * VREF;
    // Higher voltage = clearer water (more light received)
    // Lower voltage = muddy water (light scattering blocked)
    float turbidity_ntu = map(v_turb * 100, 0, VREF * 100, 3000, 0); 
    if (turbidity_ntu < 0) turbidity_ntu = 0;

    // ==========================================
    // 3. TDS SUBSYSTEM SAMPLING (Electrical)
    // ==========================================
    long tds_acc = 0;
    for (int i = 0; i < 32; i++) tds_acc += analogRead(TDS_ANALOG_PIN);
    float v_tds = (tds_acc / 32.0 / ADC_RESOLUTION) * VREF;
    // Basic linear estimation equation for conductivity
    float ppm_tds = (66.71 * v_tds * v_tds * v_tds) - (127.93 * v_tds * v_tds) + (428.7 * v_tds);

    // ==========================================
    // TELEMETRY DATA STREAM OUTPUT
    // ==========================================
    Serial.print("DATA_STREAM | ");
    Serial.print("pH: "); Serial.print(calculated_ph, 2);
    Serial.print(" | Turbidity: "); Serial.print(turbidity_ntu, 0); Serial.print(" NTU");
    Serial.print(" | TDS: "); Serial.print(ppm_tds, 0); Serial.println(" PPM");

    delay(2000); // 2-second telemetry window
}
