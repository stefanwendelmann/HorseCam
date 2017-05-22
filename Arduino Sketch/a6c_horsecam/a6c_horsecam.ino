#include <SoftwareSerial.h>
#include <String.h>

#define OK 1
#define NOTOK 2
#define TIMEOUT 3
#define RST 2

SoftwareSerial A6board (3, 2); // RX, TX
#define A6baud 9600

#define SERIALTIMEOUT 3000

void setup() {
  A6board.begin(A6baud);
  Serial.begin(9600);
  Serial.println("Serial setup done");
  delay(5000);
  do {
    Serial.println("Setting up the Modem...");
  } while (a6begin() != OK);
  Serial.println("Modem setup done");
  a6command("AT+CNMI=0,2,0,1,0", "OK", "yy", 5000, 2); // Set display it directly
  a6command("AT+CNMI?", "OK", "yy", 1500, 2); // Check SMS Recive mode
}

void loop() {
  //Read the input of the A6 Board
  if (A6board.available())  {
    s = A6board.readString();
  }
  //Check if its a message notification
  if (s.length() > 0 && s.startsWith("\r\n+CMT: \"")) {
    Serial.println(s);
  }
  delay(100);
}


void readAllSMS() {
  a6command("AT+CNMI?", "OK", "yy", 1500, 2); // Check SMS Recive mode

  a6command("AT+CMGF=1", "OK", "yy", 1500, 2);
  a6command("AT+CMGL=\"ALL\"", "OK", "yy", 10000, 1);

}

void printSignalQuality() {
  a6command("AT+CSQ", "OK", "yy", 5000, 2);
}

byte a6waitFor(String response1, String response2, int timeOut) {
  unsigned long entry = millis();
  int count = 0;
  String reply = a6read();
  byte retVal = 99;
  do {
    reply = a6read();
    if (reply != "") {
      Serial.print((millis() - entry));
      Serial.print(" ms ");
      Serial.println(reply);
    }
  } while ((reply.indexOf(response1) + reply.indexOf(response2) == -2) && millis() - entry < timeOut );
  if ((millis() - entry) >= timeOut) {
    retVal = TIMEOUT;
  } else {
    if (reply.indexOf(response1) + reply.indexOf(response2) > -2) retVal = OK;
    else retVal = NOTOK;
  }
  //  Serial.print("retVal = ");
  //  Serial.println(retVal);
  return retVal;
}

byte a6command(String command, String response1, String response2, int timeOut, int repetitions) {
  byte returnValue = NOTOK;
  byte count = 0;
  while (count < repetitions && returnValue != OK) {
    A6board.println(command);
    Serial.print("Command: ");
    Serial.println(command);
    if (a6waitFor(response1, response2, timeOut) == OK) {
      //     Serial.println("OK");
      returnValue = OK;
    } else returnValue = NOTOK;
    count++;
  }
  return returnValue;
}

bool a6begin() {
  A6board.println("AT+CREG?");
  byte hi = a6waitFor("1,", "5,", 1500);  // 1: registered, home network ; 5: registered, roaming
  while ( hi != OK) {
    A6board.println("AT+CREG?");
    hi = a6waitFor("1,", "5,", 1500);
  }

  if (a6command("AT&F0", "OK", "yy", 5000, 2) == OK) {   // Reset to factory settings
    if (a6command("ATE0", "OK", "yy", 5000, 2) == OK) {  // disable Echo
      if (a6command("AT+CMEE=2", "OK", "yy", 5000, 2) == OK) return OK;  // enable better error messages
      else return NOTOK;
    }
  }
}

void showSerialData()
{
  unsigned long entry = millis();
  while ( A6board.available() != 0 && millis() - entry < SERIALTIMEOUT)
    Serial.println(A6board.readStringUntil('\n'));
}

String a6read() {
  String reply = "";
  if (A6board.available())  {
    reply = A6board.readString();
  }
  //Serial.print("Reply: ");
  //Serial.println(reply);
  return reply;
}
