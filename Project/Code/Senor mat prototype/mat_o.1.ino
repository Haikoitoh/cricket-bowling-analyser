

//Mux control pins for analog signal (SIG_pin) default for arduino mini pro
const byte s0 = 10;
const byte s1 = 11;
const byte s2 = 12;
const byte s3 = 13;

//Mux control pins for Output signal (OUT_pin) default for arduino mini pro
const byte w0 = 2; 
const byte w1 = 3;
const byte w2 = 4;
const byte w3= 5 ;

//Mux in "SIG" pin default for arduino mini pro 
const byte SIG_pin = 14; 

//Mux out "SIG" pin default for arduino mini pro
const byte OUT_pin = 7;

//Row and Column pins default for arduino mini pro
//const byte STATUS_pin = 13;
//const byte COL_pin = 12;

const boolean muxChannel[16][4]={
    {0,0,0,0}, //channel 0
    {1,0,0,0}, //channel 1
    {0,1,0,0}, //channel 2
    {1,1,0,0}, //channel 3
    {0,0,1,0}, //channel 4
    {1,0,1,0}, //channel 5
    {0,1,1,0}, //channel 6
    {1,1,1,0}, //channel 7
    {0,0,0,1}, //channel 8
    {1,0,0,1}, //channel 9
    {0,1,0,1}, //channel 10
    {1,1,0,1}, //channel 11
    {0,0,1,1}, //channel 12
    {1,0,1,1}, //channel 13
    {0,1,1,1}, //channel 14
    {1,1,1,1}  //channel 15
  };


//incoming serial byte
int inByte = 0;

int valor = 0;               //variable for sending bytes to processing
int calibra[8][8]; 
int maxsensor[8][8];//Calibration array for the min values of each od the 225 sensors.
int minsensor=1000;
int temp=0;      
//Variable for staring the min array
int multiplier = 254;
int pastmatrix[8][8];

void setup(){
    
  pinMode(s0, OUTPUT); 
  pinMode(s1, OUTPUT); 
  pinMode(s2, OUTPUT); 
  pinMode(s3, OUTPUT); 
  
  pinMode(w0, OUTPUT); 
  pinMode(w1, OUTPUT); 
  pinMode(w2, OUTPUT); 
  pinMode(w3, OUTPUT); 
  
  pinMode(OUT_pin, OUTPUT); 
  
 // pinMode(STATUS_pin, OUTPUT);
  //pinMode(COL_pin, OUTPUT);

  
  digitalWrite(s0, LOW);
  digitalWrite(s1, LOW);
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  
  digitalWrite(w0, LOW);
  digitalWrite(w1, LOW);
  digitalWrite(w2, LOW);
  digitalWrite(w3, LOW);
  
  digitalWrite(OUT_pin, HIGH);
 // digitalWrite(STATUS_pin, HIGH);
  //digitalWrite(COL_pin, HIGH);
  
 
  
  Serial.begin(115200);
  
  Serial.println("\n\Calibrating...\n");
  
  // Full of 0's of initial matrix
  for(byte j = 0; j < 8; j ++)
  { 
    writeMux(j);
    for(byte i = 0; i < 8; i ++)
      {calibra[j][i] = 0;
      maxsensor[j][i]=0;
  }
  }
  Serial.println("Done Calibiration Calculating averages");
  delay(5000);
  for(byte k = 0; k < 50; k++){  
    for(byte j = 0; j < 8; j ++){ 
      writeMux(j);
      for(byte i = 0; i < 8; i ++)
       { temp=readMux(i);
        calibra[j][i] = calibra[j][i]+temp;
        if( temp>maxsensor[j][i])
        {maxsensor[j][i]=temp;
        } if(temp < minsensor)
        {minsensor = temp;
        }
    }
    }
  }
  
  Serial.println("bb");
  //Print averages
  for(byte j = 0; j < 8; j ++){ 
    writeMux(j);
    for(byte i = 0; i < 8; i ++){
      calibra[j][i] = calibra[j][i]/50;
     
      Serial.print(calibra[j][i]);
      Serial.print("\t");
    }
  Serial.println(); 
  }
  
  Serial.println();
  Serial.print("Minimum Value: ");
  Serial.println(minsensor);
  Serial.println("Max Value is:");
  Serial.println();
  delay(5000);
 
}


void loop(){
  //Loop through and read all 16 values
  //Reports back Value at channel 6 is: 346
    Serial.println("round starts now");   
      for(int j = 0; j <8; j++){ 
        writeMux(j);
        
        for(int i = 0; i < 8; i++){
            
          valor = readMux(i);
         Serial.println(valor);
             
        } 
      }
    }
      


int readMux(byte channel){
  byte controlPin[] = {s0, s1, s2, s3};

  //loop through the 4 sig
  for(int i = 0; i < 4; i ++){
    digitalWrite(controlPin[i], muxChannel[channel][i]);
  }

  //read the value at the SIG pin
  int val = analogRead(SIG_pin);

  //return the value
  return val;
}

void writeMux(byte channel){
  byte controlPin[] = {w0, w1, w2, w3};

  //loop through the 4 sig
  for(byte i = 0; i < 4; i ++){
    digitalWrite(controlPin[i], muxChannel[channel][i]);
  }
}


