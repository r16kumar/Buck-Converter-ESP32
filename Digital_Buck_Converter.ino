/**
 * @file      Digital_Buck_Converter.ino
 * @author    Rohit Kumar
 * @brief     Open-loop 12V to 5V Buck Converter Firmware
 * @details   Generates a 50kHz PWM signal via ESP32 to drive an IR2110 
 * and IRFZ44N high-side switch. Includes a software soft-start.
 * @note      Requires ESP32 Core 
 */

// --- Hardware Configuration ---
#define PWM_PIN      18       // GPIO connected to IR2110 HIN (Pin 10)
#define PWM_FREQ     50000    // Switching frequency: 50 kHz
#define PWM_RES      10       // Resolution: 10-bit (0-1023)

// --- System Parameters ---
// Target calculation: Vout / Vin = 5V / 12V = 41.6% Duty Cycle
// 41.6% of 1023 (10-bit resolution) ≈ 427
#define TARGET_DUTY  427      
#define SOFT_START_DELAY 5    // Milliseconds between duty cycle increments

void setup() {
  Serial.begin(115200);
  delay(1000); 

  Serial.println("\n[SYSTEM] Initializing Digital Buck Converter...");

  // Initialize PWM output on the specified pin (ESP32 Core 3.x.x API)
  ledcAttach(PWM_PIN, PWM_FREQ, PWM_RES);

  // Ensure output is strictly zero before applying power
  ledcWrite(PWM_PIN, 0); 
  delay(500);

  executeSoftStart();
}

void loop() {
  // Main system loop. Open-loop topology requires no active feedback adjustment.
  // Output status telemetry every 5 seconds.
  Serial.println("[STATUS] Converter ACTIVE | Output: ~5.0V | Freq: 50kHz");
  delay(5000);
}

/**
 * @brief Gradually ramps the PWM duty cycle to prevent LC filter inrush current
 */
void executeSoftStart() {
  Serial.println("[SYSTEM] Executing Soft-Start Sequence...");
  
  for (int duty = 0; duty <= TARGET_DUTY; duty += 2) {
    ledcWrite(PWM_PIN, duty);
    delay(SOFT_START_DELAY);  
  }
  
  // Lock at final target
  ledcWrite(PWM_PIN, TARGET_DUTY);
  
  Serial.print("[SYSTEM] Soft-Start Complete. Target Duty Cycle: ");
  Serial.print((TARGET_DUTY * 100.0) / 1023.0, 1);
  Serial.println("%");
}