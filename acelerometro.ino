#include <SPI.h>
#include <SD.h>
/* ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)*/

File arquivo;

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

void setup(void) {
  Serial.begin(9600);
  SD.begin(4);
  
  while (!Serial)
    delay(10); // Espera até que a comunicação serial esteja disponível

  // Tenta iniciar o acelerômetro, caso contrário mostra mensagem de erro
  if (!mpu.begin()) {
    Serial.println("A comunicação com o acelerômetro MPU6050 falhou.");
    while (1) {
      delay(10);
    }
  }
  arquivo = SD.open("log.txt", FILE_WRITE);
  //cabeçalho do arquivo
  arquivo.println("aceleração x;aceleração y;aceleração z;velocidade angular x;velocidade angular y;velocidade angular z;tempo");
  arquivo.close();
    
  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_260_HZ);
  delay(100);
}
float tempo = 0, intervalo = 1;
void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  
  arquivo = SD.open("log.txt", FILE_WRITE);
  arquivo.print(a.acceleration.x);
  arquivo.print(";");
  arquivo.print(a.acceleration.y);
  arquivo.print(";");
  arquivo.print(a.acceleration.z);
  arquivo.print(";");
  arquivo.print(g.gyro.x);
  arquivo.print(";");
  arquivo.print(g.gyro.y);
  arquivo.print(";");
  arquivo.print(g.gyro.z);
  arquivo.print(";");
  tempo = millis();
  arquivo.print(tempo/1000);
  arquivo.println();
  arquivo.close();

  /*
  Serial.print(a.acceleration.x);
  Serial.print(";");
  Serial.print(a.acceleration.y);
  Serial.print(";");
  Serial.print(a.acceleration.z);
  Serial.print(";");
  Serial.print(g.gyro.x);
  Serial.print(";");
  Serial.print(g.gyro.y);
  Serial.print(";");
  Serial.print(g.gyro.z);
  Serial.println();
  */
}
