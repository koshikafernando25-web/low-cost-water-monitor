/*
 * Low-Cost 3-in-1 Water Quality Monitoring Subsystem
 * Core Signal Processing Engine (pH Subsystem Focus)
 */

// Hardware Pin Definitions
const int PH_ANALOG_PIN = 34;      // Connect to TL072 Pin 1 (Output)
const int ADC_RESOLUTION = 4095;   // 12-bit resolution for ESP32 (use 1023 for Arduino Uno)
const float VREF = 3.3;            // Operating ADC reference voltage (use 5.0 for Arduino Uno)

// Calibration Parameters
const float V_VIRTUAL_GROUND = 2.50; // The theoretical baseline set by our 10k resistor divider
const float NERNST_SLOPE = 0.05916;  // Voltage shift per single pH unit change at 25°C

void setup() {
    Serial.begin(115200);
    pinMode(PH_ANALOG_PIN, INPUT);
    Serial.println("--- Subsystem Booted: Tracking 3-in-1 Metrics ---");
}

void loop() {
    // Read and smooth analog input to eliminate fluid ripples
    long raw_accumulator = 0;
    for (int i = 0; i < 64; i++) {
        raw_accumulator += analogRead(PH_ANALOG_PIN);
        delayMicroseconds(50);
    }
    float avg_raw = raw_accumulator / 64.0;
    
    // Convert raw ADC ticks back to physical voltage matching the TL072 output
    float observed_voltage = (avg_raw / ADC_RESOLUTION) * VREF;
    
    // Reverse-engineer the Virtual Ground Offset Elevator
    // Shifts the voltage scale back to standard relative 0V reference
    float relative_probe_mv = (observed_voltage - V_VIRTUAL_GROUND);
    
    // Map the relative voltage to the true chemical Nernst scale
    // At pH 7, relative_probe_mv is 0V. Voltage increases as acidity rises.
    float calculated_ph = 7.0 - (relative_probe_mv / NERNST_SLOPE);
    
    // Restrict calculation limits safely within physical parameters (pH 0 - 14)
    if (calculated_ph < 0.0) calculated_ph = 0.0;
    if (calculated_ph > 14.0) calculated_ph = 14.0;

    // Output Data Stream
    Serial.print("TL072 Pin 1 Output: ");
    Serial.print(observed_voltage, 3);
    Serial.print("V | Calculated Chemical Value: pH ");
    Serial.println(calculated_ph, 2);

    delay(2000); // 2-second telemetry sampling window
}
