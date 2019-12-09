#include <EtherCard.h>

static byte mymac[] = { 0x74,0x69,0x2D,0x30,0x31 };

byte Ethernet::buffer[700];

void setup() {
    Serial.begin(9600);
    Serial.println(F("\n[testDHCP"));

    Serial.print("MAC : ");
    for (byte i = 0; i<6 ; ++i) {
        Serial.print(mymac[i], HEX);
        if (i<5) {
            Serial.print(" : ");
        }
    }
    Serial.println();

    if(ether.begin(sizeof Ethernet::buffer, mymac) == 0) {
        Serial.println(F("Failed to access Ethernet controller!"));
    }
    Serial.println(F("Setting up DHCP"));
    if(!ether.dhcpSetup()) {
        Serial.println(F("DHCP failed"));
    }

    ether.printIp("My IP : ", ether.myip);
    ether.printIp("Netmask : ", ehter.netmask);
    ether.printIp("GW IP : ", ether.gwip);
    ether.printIp("DNS IP : ", ether.dnsip);
}

void loop() {
    
}