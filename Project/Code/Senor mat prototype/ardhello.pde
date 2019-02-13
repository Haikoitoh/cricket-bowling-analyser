import processing.serial.*; //import the Serial library
 Serial myPort;  //the Serial port object
 String val;
 int[] input = new int [2];
 int serialCount=0;
 int tiempoant;

// since we're doing serial handshaking, 
// we need to check if we've heard from the microcontroller
boolean firstContact = false;
void setup() {
  size(960, 960); //make our canvas 200 x 200 pixels big
  //  initialize your serial port and set the baud rate to 9600
  myPort = new Serial(this, Serial.list()[0], 115200);
}
void draw()  {
    background(0);
    for (int j=0; j<8; j++) {
      for (int i=0; i<8; i++) {
          stroke(255);
          noFill();
          rect(i*120,j*120,120,120);
        }
  
      }
    int  a=input[0];
    int  b=input[1];
 fill(255,0,0);
  rect(a*120,b*120,120,120);
  }

void serialEvent(Serial myPort) {
  // read a byte from the serial port:
  int inByte = myPort.read();
  // if this is the first byte received, and it's an A,
  // clear the serial buffer and note that you've
  // h
  //  ad first contact from the microcontroller. 
  // Otherwise, add the incoming byte to the array:
  if (firstContact == false) {
    if (inByte == 'A') { 
      myPort.clear();          // clear the serial port buffer
      firstContact = true;     // you've had first contact from the microcontroller
      myPort.write(65);
      println(inByte);// ask for more
    }
  } else {
    // Add the latest byte from the serial port to array:
      input[serialCount] = inByte;
      println(inByte);

    serialCount++;

    // If we have 3 bytes:
    if (serialCount > 1 ) {
 
      
    
      // Send a capital A to request new sensor readings:
      myPort.write('A');
      // Reset serialCount:
      serialCount = 0;
    }
  }
}
