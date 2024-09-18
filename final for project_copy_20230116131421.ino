  const int xstepPin = 2; //X.STEP
  const int xdirPin = 5; // X.DIR high far from mot
  
  const int ystepPin = 3; //y.STEP
  const int ydirPin = 6; // y.DIR high far from mot
  
  const int zstepPin = 4; //z.STEP
  const int zdirPin = 7; // z.DIR High to go up 
  const int magnetPin =12;// magnetpin
  const float steplen = 0.001258; 
  float currentx,currenty;//keeps track of current position of the head;
  int zsteps=11200;
   
  int i;
  int k=1;//keeps track of loading
  
  template <typename T> int sgn(T val) {                                    
    return (T(0) < val) - (val < T(0));
  }

void setup() {
  pinMode(2,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(12,OUTPUT);
  Serial.begin(9600);
  digitalWrite(magnetPin,HIGH);
  
  
}




    float coordinates[14][2]={

    {10.7500,11.1854},
    {9.1250,13.9},
    {12.3750,13.9},
    {14.0,11.1854},
    {12.3750,8.3708},
    {9.1250,8.3708},
    {7.50,11.1854},
    {3.2500,2.8146},
    {1.6250,5.6292},
    {4.8750,5.6292},
    {6.500,2.8146},      
    {4.8750,0.0},
    {1.6250,0.0},
    {0.0,2.8146}
    };

void loop() {

  int z=1;
  while(Serial.available() && z == 1){
    Serial.print("\t ");
    Serial.print(k);
    Serial.print("\t ");


    int dat = Serial.parseInt();
    

    float destx = coordinates[dat-1][0];
    float desty = coordinates[dat-1][1];
    Serial.print(destx);
    Serial.print("\t");
    Serial.print(desty);

    
    if(currentx>destx)
    {
      digitalWrite(xdirPin,HIGH);
    }

    else
    {
      digitalWrite(xdirPin,LOW) ;
    }

      if(currenty>desty)
    {
      digitalWrite(ydirPin,LOW);
    }
    
    else
    {
      digitalWrite(ydirPin,HIGH) ;
    }
    
    float slope = (desty-currenty)/(destx-currentx);
    
    int stepsy = int(abs((desty-currenty)/steplen));
    Serial.print(stepsy);

      for(i=1; i <= int(abs((desty-currenty)/steplen)); i++)
    {
        digitalWrite(ystepPin,HIGH);
        delayMicroseconds(300);
        digitalWrite(ystepPin,LOW);
        delayMicroseconds(300);
      
    }
    
    delay(2000);

    Serial.print("in y  axis got from ");
    Serial.print(currenty);
    Serial.print("  to  ");
    Serial.print(desty); 
    currenty = currenty + sgn(desty-currenty)*i*steplen;
    
    int stepsx = int(abs(destx-currentx)/steplen);
    
    for(i=1; i <= int(abs(destx-currentx)/steplen);i++)
    {
        digitalWrite(xstepPin,HIGH);
        delayMicroseconds(300);
        digitalWrite(xstepPin,LOW);
        delayMicroseconds(300);
      
    }
    delay(2000);
    Serial.print("\t in x axis got from ");
    Serial.print(currentx);
    Serial.print("  to  ");
    Serial.print(destx);
    currentx = currentx + sgn(destx-currentx)*i*steplen;
    
    digitalWrite(zdirPin,LOW);//goes down
      for(i=1;i<=zsteps;i++){
        digitalWrite(zstepPin,HIGH);
        delayMicroseconds(300);
        digitalWrite(zstepPin,LOW);
        delayMicroseconds(300);
      }
      delay(500);
    if(k==1){
      digitalWrite(magnetPin,LOW);
      
    }
    if(k==0){
      digitalWrite(magnetPin,HIGH);
    } 

    delay(2000);

    digitalWrite(zdirPin,HIGH);//goes up
      for(i=1;i<=zsteps;i++){
        digitalWrite(zstepPin,HIGH);
        delayMicroseconds(300);
        digitalWrite(zstepPin,LOW);
        delayMicroseconds(300);
      }
    
    
    k=((k==1)?0:1);

  }
  
  
}