int pan = A0 ;

void setup() {
Serial.begin(115200);
pinMode(INPUT , pan);

}

void teste1(){
  float panv1 = analogRead(pan);
 float panv2 = (panv1/40.01);
 // Serial.println(panv2);
  Serial.println(33);
 delay(2000);
  }

void loop() {

teste1();

}
