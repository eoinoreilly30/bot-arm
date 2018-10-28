#include <Servo.h>
#include <stdlib.h>

Servo lr, ud, fb;  // create servo object to control a servo

int lrpin = 10;
int udpin = 11;
int fbpin = 6;

String rx;

int fb_rx;
int ud_rx;
int lr_rx;

void home_axes();

void setup() {
  lr.attach(lrpin);
  ud.attach(udpin);
  fb.attach(fbpin);
  Serial.begin(9600);
  home_axes();
}

void move_lr(int val){
  int pos = lr.read();
  
  if(pos < val){
    for(int i=pos; i<=val; i++){
      lr.write(i);
      delay(20);
    }
  }

  else if(pos > val){
    for(int i=pos; i>=val; i--){
      lr.write(i);
      delay(20);
    }
  }

  else return;
}

void move_fb(int val){
  int pos = fb.read();
  
  if(val > 175 || val < 40) return;
  
  if(pos < val){
    for(int i=pos; i<=val; i++){
      fb.write(i);
      delay(20);
    }
  }

  else if(pos > val){
    for(int i=pos; i>=val; i--){
      fb.write(i);
      delay(20);
    }
  }

  else return;
}

void move_ud(int val){
  int pos = ud.read();
  
  if(val > 100 || val < 40) return;
  
  if(pos < val){
    for(int i=pos; i<=val; i++){
      ud.write(i);
      delay(20);
    }
  }

  else if(pos > val){
    for(int i=pos; i>=val; i--){
      ud.write(i);
      delay(20);
    }
  }

  else return;
}

void home_axes(){
  move_lr(90);
  move_fb(70);
  move_ud(80);
}

String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void loop() {
  if (Serial.available() > 0) {
    rx = Serial.readString();
    Serial.println("Received: " + rx);

    if(rx == "home") home_axes();

    else{
    fb_rx = getValue(rx, ';', 0).toInt();
    ud_rx = getValue(rx, ';', 1).toInt();
    lr_rx = getValue(rx, ';', 2).toInt();
    
    move_fb(fb_rx);
    move_ud(ud_rx);
    move_lr(lr_rx);
    }
  }
  
  else {
    Serial.print("fb:");
    Serial.print(fb.read());
    Serial.print(" ud:");
    Serial.print(ud.read());
    Serial.print(" lr:");
    Serial.println(lr.read());
    }
  delay(1000);
}
