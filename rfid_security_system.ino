#include<Servo.h>
#include <SPI.h>
#include <RFID.h>

RFID rfid(10, 9); //sda and reset pinleri
const byte rled = 7;
const byte gled = 6;
const byte buzzer = 3;
boolean permission = true; // boolean  değişkeni 
byte card[5] = {107, 135, 241, 197, 216}; //sistemin tanıyacağı kart numarası
Servo servo;   //created servo object
void setup()
{
  Serial.begin(9600);
  SPI.begin();
  rfid.init();  //RFID başlattık
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(3, OUTPUT);
  servo.attach(5); //   servo pini
}

void loop()

{
  servo.write(0);  
  permission = true;

  if (rfid.isCard()) {  //kart okursa...

    Serial.println(" -ARDUINO HOCAM- RFID SECURTY SYSTEM------CARD READ-----");

    if (rfid.readCardSerial()) { // kart numaralarını yazdırıyoruz

      Serial.println(" ");
      Serial.println("CARD NUMBERS");
      Serial.println("");
      Serial.print(rfid.serNum[0]);
      Serial.print(" , ");
      Serial.print(rfid.serNum[1]);
      Serial.print(" , ");
      Serial.print(rfid.serNum[2]);
      Serial.print(" , ");
      Serial.print(rfid.serNum[3]);
      Serial.print(" , ");
      Serial.print(rfid.serNum[4]);
      Serial.println(" ");

    }


    for (int i = 0; i < 5; i++) // kart numaralarını karşılaştırıyoruz
    {
      if (rfid.serNum[i] != card[i])  // boolean dedğişkenini burada false yapıyoruz
      {
        permission = false;
      }
    }
    if (permission == true)  //
    {




      Serial.println("IZIN VERILDI");
      digitalWrite(rled, LOW);
      digitalWrite(buzzer, HIGH);
      delay(50);
      digitalWrite(buzzer, LOW);
      delay(50);
      digitalWrite(buzzer, HIGH);
      delay(50);
      digitalWrite(buzzer, LOW);
      digitalWrite(gled, HIGH);
      servo.write(90);
      delay(2000);

    }



    else    // FALSE ise aşağıdaki işlemler.
    {





      Serial.println("IZINSIZ GIRIS!!!!!!!");
      digitalWrite(buzzer, HIGH);
      delay(300);
      digitalWrite(buzzer, LOW);
      digitalWrite(buzzer, HIGH);
      delay(50);
      digitalWrite(buzzer, LOW);
      digitalWrite(buzzer, HIGH);
      delay(50);
      digitalWrite(buzzer, LOW);
      digitalWrite(rled, HIGH);
      delay(500);
      digitalWrite(gled, LOW);
      servo.write(0);
      delay(2000);

    }



    rfid.halt();  //RFID sonlandırılıyor.
  }
  else                              //diğer türlü yeşil ve kırmızı LED ler sönsün.
    digitalWrite(gled, LOW);
  digitalWrite(rled, LOW);
}
