/*
	ArdSim V3.1 - the library for input/output interface with X-Plane. 
	The latest version of this library, manuals and code samples at:
	http://arduino.svglobe.com
	Vlad Sychev 2015
*/
#ifndef ArdSim_h
#define ArdSim_h
#include "Arduino.h"
#include "Ethernet.h"
//#include "EthernetV2_0.h"
#define BOARD_TYPE 1, 1
#define XPLANE_IP 0,0,0,0
#define MAC_ADR 0xDE,0xAD,0xBE,0xEF,0xFE,0xED
#define ARDUINO_IP 0,0,0,0
#define ARDSIM_PORT 5080
#define XP_PORT 49000
#define MEGA 1
#define UNO 2
#define NANO 3
#define MINI 3
#define HOLD 1
#define STATIC 2
#define ON 255
#define OFF 0
#define MX 222
#define IN (1)
#define OUT (2)
#define NOINPUT 100
#define ArdSimScan sim.SimScan()
#define SGau() servoGauge(byte srv, byte num, byte pin, float min, float max, int smin, int smax)
#define ArdSimStart sim.SimStart(ARDSIM_PORT, MAC_ADR, XPLANE_IP, BOARD_TYPE, ARDUINO_IP)
#define SlaveOUT Wire.beginTransmission(s); for (int n=0; n<6; n++) Wire.write(sim.dt[n]); Wire.endTransmission();
void InputMatrix(byte X1, byte X2, byte Y1, byte Y2);
void EncoderPort(byte port);
void EncoderPin(byte pin,  byte btn=0);
void EncModeBtn(byte pin, byte enc, byte id, byte mx=0);
byte EncMode(byte enc);
void EncModeLED(byte pin, byte enc, byte mod);
void RepeatBtn(byte num, byte type=0, byte mx=0); 
void AnalogIn(byte pin, word pre, word min=0, word max=1023); 
void AnalogSwitch(byte pin, word pos, word cont=0);
boolean ReadInput (byte pin, byte act=STATIC, byte mx=0);
void SimInput(byte id);
float GetData(byte idx);
boolean NewData(byte idx);
void LEDout(byte pin, byte dref, float val=1, float val1=-999, boolean inv=0);
void Gauge ( byte num, byte pin, float min, float max, int smin=0, int smax=100);
void servoGauge (byte num, byte pin, float min, float max, int smin, int smax);
void OutputPin(byte pin, byte last=0);
void InputPin(byte pin=100, byte last=0);
void SendToSlave(byte s, byte d0, byte d1=0, byte d2=0, byte d3=0, byte d4=0);
void SendOUT(byte s);
void SetData(byte idx, float val);
//----test -------------
void StepPos (byte st, int pos);
void StepGauge ( byte A, byte B, byte mid, byte dref, float min, float max );
void StepperGauges();
//---------------- 	//XPD
void XPDref (char* DRef, float Val);
void XPCmnd (char* Com);
void XPMenu (int MenuNum); 
void ButtonCmnd(int pin, char* com, byte mx=0);
void APosition(byte pin, byte pos, char* com, float val=-999 );

class ARDsim
{
public:
ARDsim();
void SimScan();
boolean ToSlave(byte data);
void SimStart (unsigned int XPR, byte mc1, byte mc2, byte mc3, byte mc4, byte mc5, byte mc6, byte IP1, byte IP2,  byte IP3, byte IP4, byte Brd, byte Bn, byte IPa1, byte IPa2,  byte IPa3, byte IPa4); 
void ArdInit();     //LAN ver
void XPudp();
void Scan();
void EncIn();
void MxIn();
void DirIn();
void AnIn();
void PinSet(byte pin, byte in=0); // 0 - in, 1 - out
void AIn(byte num,  int val, byte type);
void Send(byte type, int num, byte dir=0, byte mode=0);
void Cmnd(char Data_com[]);								 	//XPD 
void Dref(char* dref, float Data);							//XPD 
void Menu(int mnum);									 	//XPD 
byte ARD;				 // Arduino num(for multi-ard)
byte d_pins;
byte a_pins;
byte w_pin;        // wire
boolean in_pin;    
int A_pos[16];    		 // prev pos (0-1000)
word a_set[16];			 // 0-9, 10-15 (< 64)
word aflags[16];	     // 0-9, 10 sw, 11-15- cont numb
unsigned long d_time;    // timer 2
unsigned long a_time;    // timer 2
unsigned long atime;     // timer ( 25 ms )
float Dget[50];
byte dt[6];
byte mxa; 
byte Act; 
byte anAct; 	//XPD 
int anPos;      //XPD
boolean active;
boolean tabu;
byte iscan;
word mxflag[16];
word mxcont[16];
word mxhold[16];
byte flags[60];  		//
byte Emem[25];			//  e/b state
byte Etyp[25];			//  e/b type
byte Emode[25];			//  mode 0, 1.... 8, A, B, C
byte Epins[28];     // (0-24 -direct enc pins) +flags: 25-enab/type; 26-port, 27- enc number
byte Bx1;
byte Bx2;
byte By1;
byte By2;
//------------------------
void ServoSet();
byte snum; //srv count
byte srp; // prev srv pin
int sGau[20];
byte srvpin[20];
unsigned long stime;    // servo timer
//-----------
unsigned long inscan; 
void stp_dn(byte st, int val);
void stp_up(byte st, int val);
void StepGau (byte st, int phase, int dir);
void StepRes();
byte A_coil[10];
byte mid[10];
byte B_coil[10]; 
byte sdref[10];
float stmin[10];
float stmax[10];
int mstep[10]; 
int abspos[10];
byte stn;
//---------------
 private:
EthernetUDP Udp;
unsigned int UP;        // UDP port
IPAddress ipx;  		// IP addr for PC (auto)
byte mac_ad[6];	
IPAddress ip;			// IP addr for Arduino
int xpip;
};

extern ARDsim sim; 
#endif
