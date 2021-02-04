#include <FaBoLCDmini_AQM0802A.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <MHZ19.h>

#define SRX 0
#define STX 1
#define INTERVAL 6

MHZ19 myMHZ19;

SoftwareSerial concInput(SRX, STX);
SoftwareSerial concOutput(2, 3);
FaBoLCDmini_AQM0802A lcd;

void setup() {
    concInput.begin(9600);
    concOutput.begin(9600);
    delay(100);
    myMHZ19.begin(concInput);

    Wire.begin();
    lcd.begin();
}


int count = 0;
int co2 = 0;
void loop() {
    if ((count % INTERVAL) == 0 ) {
        concInput.listen();
        co2 = myMHZ19.getCO2();
    }
    displayCo2(co2, (count % 2 == 0), (count % INTERVAL == 0));
    count++;
    delay(1000);
}

void displayCo2(int co2, bool isPeriod, bool isUpdate) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("CO2 ppm");
    lcd.setCursor(0, 1);
    lcd.print(co2);
    if (isPeriod && !isUpdate) {
        lcd.print(" .");
    } else if (isPeriod && isUpdate) {
        lcd.print(" :");
        concOutput.listen();
        concOutput.print(co2);
    }
}
