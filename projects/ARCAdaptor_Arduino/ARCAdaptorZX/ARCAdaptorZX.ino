#include "UsbKeyboard.h"
#include "ARCAdaptor.h"
#include "Bounce2.h" /*http://playground.arduino.cc/code/bounce*/

#define DATA0 X1_1
#define DATA1 X1_3
#define DATA2 X1_5
#define DATA3 X1_7
#define DATA4 X1_9

#define ADDRESS0 X2_1
#define ADDRESS1 X2_3
#define ADDRESS2 X2_5
#define ADDRESS3 X2_7
#define ADDRESS4 X2_9
#define ADDRESS5 X2_11
#define ADDRESS6 X2_13
#define ADDRESS7 X2_15

byte addressBus[]={
  ADDRESS0,
  ADDRESS1,
  ADDRESS2,
  ADDRESS3,
  ADDRESS4,
  ADDRESS5,
  ADDRESS6,
  ADDRESS7
     };
byte dataBus[]={
  DATA0,
  DATA1,
  DATA2,
  DATA3,
  DATA4
};

//defining keyboard
#define SYMBOL_SHIFT 1
#define CAPS_SHIFT 35
#define KEY_ALT 0xE2
#define KEY_SHIFT 0xE1

//for UNREAL Speccy Portable
//sym shift -> to ALT
//caps shift -> to SHIFT

byte keybmatrix[]={
  KEY_SPACE,KEY_ALT,KEY_M,KEY_N,KEY_B,
  KEY_ENTER,KEY_L,KEY_K,KEY_J,KEY_H,
  KEY_P,KEY_O,KEY_I,KEY_U,KEY_Y,
  KEY_0,KEY_9,KEY_8,KEY_7,KEY_6,
  KEY_1,KEY_2,KEY_3,KEY_4,KEY_5,
  KEY_Q,KEY_W,KEY_E,KEY_R,KEY_T,
  KEY_A,KEY_S,KEY_D,KEY_F,KEY_G,
  KEY_SHIFT,KEY_Z,KEY_X,KEY_C,KEY_V
};
#define KBUFSIZE 40
#define USBBUFFERSIZE BUFFER_SIZE /* UsbKeyboard.h */
#define DEBOUNCER 5

byte usbBuffer[USBBUFFERSIZE];

byte keyBuffer[KBUFSIZE];


bool bIdle=true;


// Instantiate a Bounce object
Bounce debouncer = Bounce(); 

void setup() {
//setting analog pins to digital
  // and setting up data bus
  
  pinMode(DATA0,INPUT);
  digitalWrite(DATA0,HIGH); 
  pinMode(DATA1,INPUT);
  digitalWrite(DATA1,HIGH);
  pinMode(DATA2,INPUT);
  digitalWrite(DATA2,HIGH);
  pinMode(DATA3,INPUT);
  digitalWrite(DATA3,HIGH);
  pinMode(DATA4,INPUT);
  digitalWrite(DATA4,HIGH);
  //address bus 
  pinMode(ADDRESS0, INPUT);
  digitalWrite(ADDRESS0,HIGH);
  pinMode(ADDRESS1, INPUT);
  digitalWrite(ADDRESS1,HIGH); 
  pinMode(ADDRESS2, INPUT);
  digitalWrite(ADDRESS2,HIGH);
  pinMode(ADDRESS3, INPUT);
  digitalWrite(ADDRESS3,HIGH);
  pinMode(ADDRESS4, INPUT);
  digitalWrite(ADDRESS4,HIGH);
  pinMode(ADDRESS5, INPUT);
  digitalWrite(ADDRESS5,HIGH);
  pinMode(ADDRESS6, INPUT);
  digitalWrite(ADDRESS6,HIGH);
  pinMode(ADDRESS7, INPUT);
  digitalWrite(ADDRESS7,HIGH);
}


void loop() {
  
  UsbKeyboard.update();

    char addressPointer=0;
  //reading keyboard
  char bufferPtr=0;
  memset(keyBuffer,0,sizeof(keyBuffer));
  memset(usbBuffer,0,sizeof(usbBuffer));
  for(char i=0;i<8;i++)
  {
    pinMode(addressBus[i], OUTPUT);
    digitalWrite(addressBus[i],LOW); //preparing data
    for (char j=0;j<5;j++)
    {
       debouncer.attach(dataBus[j]);
       debouncer.interval(DEBOUNCER);
       debouncer.update();
      char key = debouncer.read();
      
      if (!key)
      {
        keyBuffer[bufferPtr]=keybmatrix[i*5+j];        
      }
      bufferPtr++;
    } //end data bus
   pinMode(addressBus[i], INPUT);
   digitalWrite(addressBus[i],HIGH); //get back
   
  } //end address bus
  bool bPressed=false;
  //calculating modifiers
  bool bCapsShift=false;
  bool bSymbolShift = false;
  byte kModifier = 0;
  if (keyBuffer[SYMBOL_SHIFT])
  {
    bSymbolShift = true;
    kModifier = kModifier | (MOD_ALT_LEFT);
    keyBuffer[SYMBOL_SHIFT]=0;   
  }
  if (keyBuffer[CAPS_SHIFT])
  {
    bCapsShift = true;
    kModifier = kModifier | (MOD_SHIFT_LEFT);
    keyBuffer[CAPS_SHIFT]=0;  
  }
  
  #define DATA_PTR 1 //starting from second byte
  
  byte bytePtr = DATA_PTR;
  
  for(char k=0;k<KBUFSIZE;k++)
  {
    
    if(keyBuffer[k])
    {
      bPressed = true;
      if(bytePtr < USBBUFFERSIZE)
      {
        usbBuffer[bytePtr] = keyBuffer[k];
        bytePtr++;
      }  
    }
  }
  
  
  
  if (bytePtr == DATA_PTR ) //only modifiers left
  {
     memset(usbBuffer,0,sizeof(usbBuffer));
     if(bCapsShift)
     {
       usbBuffer[1] = KEY_SHIFT;
       bPressed=true;
     }
     if(bSymbolShift)
     {
       usbBuffer[2] = KEY_ALT;
       bPressed=true;
     }
     
     
  }
  
  
  usbBuffer[0]=kModifier;
  
   
 if (bPressed)
  {
    bIdle = false;
  }
     
  if(!bPressed)
  {
    memset(usbBuffer,0,sizeof(usbBuffer));
    
  }
  
  if (!bIdle)
  {
    UsbKeyboard.sendBuffer(usbBuffer);
    if (!bPressed)
    {
      bIdle = true; 
    }
  }

 
}
