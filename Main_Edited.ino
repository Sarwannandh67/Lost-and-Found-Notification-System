#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <MFRC522.h>

// Pin Definitions
#define RST_PIN 9
#define SS_PIN 10
#define BUZZER_PIN 7
#define SWITCH_PIN 8

// RFID and Display Setup
MFRC522 mfrc522(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2); // Replace 0x27 with your display's address


// GSM Module Setup
SoftwareSerial gsm(2, 3); // RX (GSM TX), TX (GSM RX)

// Constants
#define BUZZER_DURATION 2000
#define GSM_RESPONSE_TIMEOUT 5000

// Known RFID Tags and Owner Information
struct TagInfo {
  String tagID;
  String ownerName;
  String phoneNumber;
};

TagInfo tags[] = {
   {"B9FBA594", "Sarwannandh", "+919704736991"},
   {"331EBCE4", "Karthikeya", "+917702343067"},
   {"748CAFA3", "Supradeep", "+917702343067"},
};
const int numTags = sizeof(tags) / sizeof(tags[0]);

// Function Prototypes
bool scanForTag();
String getTagID();
int findTag(String tagID);
void handleKnownTag(int tagIndex);
void handleUnknownTag();
bool sendSMS(String phoneNumber, String message);
void activateBuzzer();

void setup() {
  Serial.begin(9600); // Initialize Serial Monitor
  gsm.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  lcd.begin(16, 2);
  lcd.backlight();
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(SWITCH_PIN, INPUT_PULLUP);

  Serial.println("System Initializing...");
  lcd.setCursor(0, 0);
  lcd.print("System Initializing");
  delay(2000);

  lcd.clear();
  lcd.print("Ready to Scan");
  Serial.println("System Ready. Waiting for RFID tag...");
}

void loop() {
  // Check for RFID Tag
  if (scanForTag()) {
    String scannedID = getTagID();

    Serial.print("Tag Detected: ");
    Serial.println(scannedID);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Tag ID:");
    lcd.setCursor(0, 1);
    lcd.print(scannedID);
    delay(2000);

    int tagIndex = findTag(scannedID);
    if (tagIndex != -1) {
      handleKnownTag(tagIndex);
    } else {
      handleUnknownTag();
    }

    delay(5000);
    lcd.clear();
    lcd.print("Ready to Scan");
    Serial.println("System Ready. Waiting for RFID tag...");
  }
}

// Function to Scan for RFID Tag
bool scanForTag() {
  return mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial();
}

// Function to Retrieve RFID Tag ID
String getTagID() {
  String tagID = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    tagID += String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""); // Add leading zero
    tagID += String(mfrc522.uid.uidByte[i], HEX);
  }
  tagID.toUpperCase();
  return tagID;
}

// Function to Find Tag in Known List
int findTag(String tagID) {
  for (int i = 0; i < numTags; i++) {
    if (tags[i].tagID == tagID) {
      return i;
    }
  }
  return -1; // Tag not found
}

// Function to Handle Known Tag
void handleKnownTag(int tagIndex) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Owner:");
  lcd.setCursor(0, 1);
  lcd.print(tags[tagIndex].ownerName);

  Serial.print("Known Tag Found: ");
  Serial.println(tags[tagIndex].ownerName);
  Serial.print("Sending SMS to: ");
  Serial.println(tags[tagIndex].phoneNumber);

  bool smsSent = sendSMS(tags[tagIndex].phoneNumber, "Dear Sir/Mam \n Your items are found at the Center. Please Come here to collect \n ~ Regards Lost n' Found Managment system");
  if (smsSent) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("SMS Sent");
    lcd.setCursor(0, 1);
    lcd.print(tags[tagIndex].ownerName);
    Serial.println("SMS Sent Successfully.");
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("SMS Failed");
    Serial.println("SMS Sending Failed.");
  }

  activateBuzzer();
}

// Function to Handle Unknown Tag
void handleUnknownTag() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Unknown Tag");
  lcd.setCursor(0, 1);
  lcd.print("Not in System");

  Serial.println("Unknown Tag Detected. Not in System.");
  activateBuzzer();
}

// Function to Send SMS
bool sendSMS(String phoneNumber, String message) {
  gsm.println("AT");
  if (!waitForGSMResponse("OK", GSM_RESPONSE_TIMEOUT)) return false;

  gsm.println("AT+CMGF=1"); // Set SMS to Text Mode
  if (!waitForGSMResponse("OK", GSM_RESPONSE_TIMEOUT)) return false;

  gsm.print("AT+CMGS=\"");
  gsm.print(phoneNumber);
  gsm.println("\"");
  if (!waitForGSMResponse(">", GSM_RESPONSE_TIMEOUT)) return false;

  gsm.print(message);
  gsm.write(26); // CTRL+Z to send
  if (!waitForGSMResponse("OK", GSM_RESPONSE_TIMEOUT)) return false;

  return true;
}

// Function to Wait for GSM Module Response
bool waitForGSMResponse(String expected, unsigned long timeout) {
  unsigned long startTime = millis();
  while (millis() - startTime < timeout) {
    if (gsm.available()) {
      String response = gsm.readString();
      if (response.indexOf(expected) != -1) {
        return true;
      }
    }
  }
  return false;
}

// Function to Activate Buzzer
void activateBuzzer() {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(BUZZER_DURATION);
  digitalWrite(BUZZER_PIN, LOW);
}
