/*
	ArdSim  - the library for input/output interface with X-Plane. 
	The latest version of this library, manuals and code samples at:
	http://arduino.svglobe.com
	Vlad Sychev 2015
	Ver 3.1 (21 Oct 2015)
*/

#include "ArdSim.h"
ARDsim::ARDsim() { }
ARDsim sim = ARDsim();
//-----Setup / Start --------------
void  ARDsim::SimStart(unsigned int XPR,  byte mc1, byte mc2, byte mc3, byte mc4, byte mc5, byte mc6,  byte IP1, byte IP2,  byte IP3, byte IP4,  byte Brd, byte Bn,  byte IPa1, byte IPa2,  byte IPa3, byte IPa4) 
  { ARD=Bn;  UP = XPR;  iscan=4; in_pin=0; sim.snum=255;
switch (Brd) {
case 1: d_pins=50; a_pins=16; w_pin=20; break;  // excluded 50-53 for Ethernet shield
case 2: d_pins=10; a_pins=6; break;
case 3: d_pins=10; a_pins=8; break;
	}
bitSet(flags[4], 4); bitSet(flags[10], 4); //bitSet(flags[0], 4); bitSet(flags[1], 4);	//for Ethernet shield
	mac_ad[0] = mc1; mac_ad[1] = mc2; mac_ad[2] = mc3;
	mac_ad[3] = mc4; mac_ad[4] = mc5; mac_ad[5] = mc6;  
	ipx[0] = IP1; ipx[1]=IP2; ipx[2]=IP3; ipx[3]=IP4;
	ip[0]=IPa1; ip[1]=IPa2; ip[2]=IPa3; ip[3]=IPa4;
	if (IPa4==0) { Ethernet.begin(mac_ad);  ip = Ethernet.localIP();  }
	Ethernet.begin(mac_ad, ip); Udp.begin(UP);
	if (IP4!=0) ArdInit(); 	//while (flags[54]==0) XPudp(); 
} 
void ARDsim::SimScan() { 
	if (iscan!=0)  iscan--; 
	if (iscan==3) return;          //first loop, reserve outputs
	if (iscan==2) { if (in_pin==0) { for (int i=0; i<d_pins; i++) PinSet(i, 0); } // pins in 
				while (flags[54]==0) XPudp();  StepRes(); }  
	 if (millis()-a_time>50) { d_time=0; tabu=0; } // reset timer for rep
	 XPudp(); Act=-1; mxa=0; inscan=micros(); Scan(); 	ServoSet(); if (stn!=0) StepperGauges();   
}
//----------------------------------
void ARDsim::PinSet(byte pin, byte in) {
	if (in==1) { pinMode(pin, OUTPUT);  bitSet(flags[pin], 4); 
		bitClear(flags[pin], 1); }
	else {                              
		if ((flags[pin]&16)!=0) return;
		 if ( pin==13) pinMode(pin, INPUT);
		 else	pinMode(pin, INPUT_PULLUP);
		  bitSet(flags[pin], 1);  bitSet(flags[pin], 0);  
		} }
void OutputPin(byte pin, byte last) {
	if (last==0) sim.PinSet(pin, 1);
	else for (int i=pin; i<=last; i++)  sim.PinSet(i, 1);
	}
void InputPin(byte pin, byte last) { sim.in_pin=1;
	if (pin==100) return;
	if (last==0) sim.PinSet(pin, 0);
	else for (int i=pin; i<=last; i++)  sim.PinSet(i, 0);
	}
byte EncMode(byte enc) { return sim.Emode[enc-1]; }  //if ((sim.Etyp[enc-1]&128)==0) return 0; else return sim.Emode[enc-1];
void EncModeLED(byte pin, byte enc, byte mod) {  
		if ((sim.flags[pin]&16)==0)  sim.PinSet(pin, 1);
	if ((sim.Etyp[enc-1]&128)!=0) { if (sim.Emode[enc-1]==mod) digitalWrite(pin, 1); else digitalWrite(pin, 0);}
}

//------------------  Initial setup----------------------
void InputMatrix(byte X1, byte X2, byte Y1, byte Y2) {
    for (int x=X1; x<=X2; x++) { pinMode(x, INPUT_PULLUP);  bitSet(sim.flags[x], 4); }
    for (int y=Y1; y<=Y2; y++) { pinMode(y, OUTPUT); digitalWrite(y, HIGH);  bitSet(sim.flags[y], 4);}
		sim.Bx1 = X1; sim.Bx2 = X2; 
		sim.By1 = Y1; sim.By2 = Y2; 	 
  }
void EncoderPort(byte port) { 
	sim.Epins[25]=1;  sim.Epins[26] = port; 
	for (int x=port; x<=(port+2); x++) { pinMode(x, INPUT_PULLUP);  bitSet(sim.flags[x], 4); }
	} 

void EncoderPin(byte pin,  byte btn) { 
		byte n=sim.Epins[27]; sim.Epins[27]++; 
		sim.Epins[n]=pin; sim.Etyp[n] = btn; bitSet(sim.Etyp[n], 7); if (btn) sim.Emode[n]=1;
		bitSet(sim.flags[pin], 4);
	if (sim.Epins[25]!=1) { sim.Epins[25]=2;
		bitSet(sim.flags[pin+1], 4);  pinMode(pin, INPUT_PULLUP); pinMode(pin+1, INPUT_PULLUP); 
		if (btn>0) { bitSet(sim.flags[pin+2], 4); bitSet(sim.Emem[n], 4);  pinMode(pin+2, INPUT_PULLUP); }
			} 
	else pinMode(pin, OUTPUT); 	
	}
void RepeatBtn(byte num, byte type, byte mx) { 
		if (type==222) { type=0, mx=222; }
		if (num >= sim.d_pins) mx=222;
		if (mx==222) {
				num=num-1;
				int a=num/16; int c=num-(16*a);
			 bitSet(sim.mxcont[a], c);  bitClear(sim.mxhold[a], c);
			if (type==1)  bitSet(sim.mxhold[a], c);  } 
		else {
		 bitSet(sim.flags[num], 2);  bitClear(sim.flags[num], 3);
		if (type==1)  bitSet(sim.flags[num], 3); }
 }

void AnalogIn(byte pin, word pre, word min, word max) {
		sim.a_set[pin]=max | (min<<10);  sim.aflags[pin]=pre-1;
} 
void AnalogSwitch(byte pin, word pos, word cont) {
	sim.a_set[pin] = 1023;   sim.aflags[pin]=pos-1;
	 if (cont>0)  sim.aflags[pin]=(pos-1) | (cont<<11);
		bitSet(sim.aflags[pin], 10); 
}
//----------
void ARDsim::Scan() { 
	if (Epins[25]>0 && iscan==0) EncIn();
	if (By1!=By2 && Bx1!=Bx2) MxIn();
	DirIn(); AnIn();
}	
void ARDsim::EncIn() {  // -- enc------
	int last=Epins[27]; byte enc=0; int edir=0; int in=26; 	// matrix connection 
	for (int i = 0; i < last; i++)  { if (Epins[25]==2) in=i;	    // direct connections
		if (Epins[25]==1) digitalWrite(Epins[i], LOW); 	// matrix init row
		byte eb = Etyp[i]&15; 	// button type
		byte em = Emem[i]&3;								// enc state mem  (0-3)
//----------------------------intr btn ---------------------------------------
		if (eb > 0) { int btn = !digitalRead(Epins[in]+2);  
			 if (eb==1) Emode[i] = btn+1;								// bt hold or click? 
			 else if (btn != bitRead(Emem[i], 2)) {
		  	 	bitWrite(Emem[i], 2, btn);   bitClear(sim.Etyp[i], 7);
				if (btn==0) { if (Emode[i] > 9) Emode[i] = 0;	 		// if external mode 
				Emode[i]++; if (Emode[i]==eb+1) Emode[i]=1; bitSet(Etyp[i], 7);  }  		// change mode if clicked on-release
			      if (Epins[25]==1) digitalWrite(Epins[i], HIGH);  	// matrix close row
						delay(15);   return;  } } 								
//-----------------------------------------------------------------------------	
		enc=!digitalRead(Epins[in]+1); enc=enc<<1; enc=enc|!digitalRead(Epins[in]);
		if (enc != em) { int e=1; 
		 for (int m=0; m<80; m++) {  if(m!=0) { enc=!digitalRead(Epins[in]+1); enc=enc<<1; enc=enc|!digitalRead(Epins[in]);}
			switch (em) { 
    		  case 0: if (enc == 1 )  edir++;  else if (enc == 2 ) edir--; break;
   			  case 1: if (enc == 3 )  edir++;  else if (enc == 0 ) edir--; break; 
   			  case 2: if (enc == 0 )  edir++;  else if (enc == 3 ) edir--; break;
   			  case 3: if (enc == 2 )  edir++;  else if (enc == 1 ) edir--; break;	
						}   em = enc;	delayMicroseconds(800);		}		
			if (edir<0) e=2; edir=abs(edir); if (edir<5) edir=1; if (edir>8) edir=edir*2; 
			while (edir!=0) { Send (0, i+1, e, Emode[i]); edir--; }								
			 Emem[i] = enc+(Emem[i]&4);	 if (Epins[25]==1) 	digitalWrite(Epins[i], HIGH);  return; //  active enc
				} if (Epins[25]==1)	digitalWrite(Epins[i], HIGH);  		 // matrix  close row
			} 
		  }
void ARDsim::MxIn() {  //mx
		Act=-1; int a;  int c;
		for (int i = By1; i <= By2; i++)  {
			digitalWrite(i, LOW); 
			for (int j = Bx1; j <= Bx2; j++)  { Act++;
			 active = digitalRead(j); 
				a=Act/16;  c=Act-(16*a);
		   	if (active != bitRead(mxflag[a], c) || iscan==1) { Act++;
				bitWrite(mxflag[a], c, active);	 digitalWrite(i, HIGH); 
				if (!tabu) Send (3, Act, active+1); 
	if (bitRead(mxcont[a], c)) {	//--- repeat
	bitSet(mxflag[a], c); tabu=0;  
		if (bitRead(mxhold[a], c)) { a_time=millis(); 
		if (d_time==0) d_time=millis(); 
		 if (millis() - d_time < 1000)  tabu=1; } } 
 			delay(15);	 mxa=222; if (iscan==0) return; }
				} digitalWrite(i, HIGH); 
				} Act=-1; mxa=0;	}
void ARDsim::DirIn() { //--- Dir --
		for (byte i = 0; i < d_pins; i++)  { 
			 if ((flags[i]&2) ==2) { active = digitalRead(i);
				if (active != bitRead(flags[i], 0)  || iscan==1) 			// 2-d bit -mem
					{ bitWrite(flags[i], 0, active);  Act = i; 
					if (!tabu) Send (1, i, active+1);
	if (bitRead(flags[i], 2)) {						//--- repeat
	bitSet(flags[i], 0); tabu=0;  
		if (bitRead(flags[i], 3)) { a_time=millis(); 
		if (d_time==0) d_time=millis(); 
	    if (millis() - d_time < 1000)  tabu=1; }
	    }  delay(15);			
			if (iscan==0) return ;	}
				} sim.Act=-1;	} 
	}
void ARDsim::AnIn() { //---- an 
	if ((millis() - atime > 25) || iscan==1)
	 { int Ain; int min;	int max; int pre; byte t;
		for (int i=0; i<a_pins; i++) if (aflags[i]>0) { 
		min=(a_set[i]>>10)&63;  max=a_set[i]&1023; pre=(aflags[i]&1023);
		  t=((aflags[i]>>10)&1);  int sence = 1024/pre;  
		Ain=constrain(analogRead(i), min, max );  
		 if (t==0)  Ain = map(Ain, min, max, 0, 1023); 
		 int pos = round(float(Ain)/sence);
				if (A_pos[i] != pos || iscan==1) { A_pos[i] = pos; 
					if (t==0)  pos = constrain(map(pos, 0, pre, 0, 1000), 0, 1000);  
					else pos++;    
			AIn(i, pos, t);	 
anAct=i; anPos=pos;										// for direct UDP only				
		if (t==1 && (aflags[i]>>11)==pos) A_pos[i]=-1;   	
		if (iscan==0 && t==1 ) { atime = millis();  return; }  // for multiposition
			}  }
		atime = millis(); }  }															
//----------- in actions -------------------------------------
boolean ReadInput (byte pin, byte act, byte mx) {
		if (act==222) { act=2, mx=222; }
		if (pin >= sim.d_pins) mx=222;
		if (act==2) { 
			if (mx==222) { int a=(pin)/16; int c=pin-(a*16); 
						return !bitRead(sim.mxflag[a], c);	}
			else { if ((sim.flags[pin]&16)!=0) return 0;
					 return !bitRead(sim.flags[pin], 0); }  }
		if (sim.Act != pin || mx!=sim.mxa) return 0;	
		if (act==255) act=1;
		if (sim.active==!act) return 1; return 0; 
		}	

void EncModeBtn(byte pin, byte enc, byte id, byte mx) {
	if (mx==0 && (sim.flags[pin]&16)!=0) return; 
	if (sim.Emode[enc-1]==0) sim.Emode[enc-1]=id; // first mode set
		if (pin >= sim.d_pins) mx=222;
	if (sim.active ==0 || sim.Act != pin || mx!=sim.mxa) return; 
		sim.Emode[enc-1]=id; 
	}
// for UDP direct
void ButtonCmnd(int pin, char* com, byte mx) { 
		if (pin >= sim.d_pins) mx=222;
	if (sim.Act != abs(pin) || sim.tabu || mx!=sim.mxa) return; 
	boolean dir=0; if (pin<0) dir=1;
	if (dir==sim.active) {  sim.Cmnd(com);  delay(15);  }  }
void APosition(byte pin, byte pos, char* com, float val ) {
	if (sim.anAct != pin) return; 
	if (sim.anPos!=pos) return;  sim.anAct=20;
  if (val==-999) sim.Cmnd(com); else  sim.Dref(com, val);  delay(15); 
}

//--- Out ---
boolean NewData(byte idx) { 
	if ((sim.flags[idx]&128)!=0) {  return 1; }  // bitClear(sim.flags[idx], 7);
	else return	0;}
float GetData(byte idx) { bitClear(sim.flags[idx], 7); return sim.Dget[idx];}
void SetData(byte idx, float val) {  sim.Dget[idx]=val;  bitSet(sim.flags[idx], 7); }
//------------wire
boolean ARDsim::ToSlave(byte data) {   
	 if (w_pin!=0 && (flags[w_pin]&16)==0)  { bitSet(flags[w_pin], 4); bitSet(flags[w_pin+1], 4); } //reserve wire pins
		if ((flags[data]&128)!=0) {   union { byte byte_v[4]; float fl_v; }  ftob;
             ftob.fl_v =  Dget[data];   bitClear(flags[data], 7); dt[0]=data;
            for (int n=0; n<4; n++) dt[n+1]=ftob.byte_v[n]; return 1; } return 0; }
void SendToSlave(byte s, byte d0, byte d1, byte d2, byte d3, byte d4 ) {
  if (sim.ToSlave(d0)) SendOUT(s); 
  if (d1>0 && sim.ToSlave(d1)) SendOUT(s); if (d2>0 && sim.ToSlave(d2)) SendOUT(s); 
  if (d3>0 && sim.ToSlave(d3)) SendOUT(s); if (d4>0 && sim.ToSlave(d4)) SendOUT(s); 
  } 
//--------------------
void LEDout( byte pin, byte dr, float val, float val1, boolean inv) {  
	   if ((sim.flags[pin]&16)==0)  sim.PinSet(pin, 1);
	if (dr==0)  { digitalWrite(pin, 0);  return; }
	if (dr==255)  { digitalWrite(pin, 1); return; }
	if (val1==-999) {
		if (sim.Dget[dr] != val) { digitalWrite(pin, 0); return; }
		else if ((sim.flags[dr]&128)!=0) { digitalWrite(pin, 1);  bitClear(sim.flags[dr], 7); }	} 
	else {
		if (sim.Dget[dr] < val || sim.Dget[dr] > val1) { digitalWrite(pin, inv); return; }
		else if ((sim.flags[dr]&128)!=0) { digitalWrite(pin, !inv);   bitClear(sim.flags[dr], 7);  }
	} }
void Gauge (byte num, byte pin, float min, float max, int gmin, int gmax) {
	   if ((sim.flags[pin]&16)==0) sim.PinSet(pin, 1);
    if ((sim.flags[num]&128)==0 || sim.Dget[num]<min || sim.Dget[num]>max) return; // new and in range?
			 bitClear(sim.flags[num], 7); 	
			float c = sim.Dget[num]; int n=1; 
				if (abs(max)<1) n=1000; 
		else if (abs(max)<10) n=100; 
		else if (abs(max)<100) n=10;
		 max*=n; min*=n;  c*=n;  
		gmin=256*gmin/100; gmax=256*gmax/100;
		c=(c-min)*(gmax-gmin)/(max-min)+gmin;
			analogWrite (pin, c); 
			}
void servoGauge (byte num, byte pin, float min, float max, int smin, int smax) {
	 if ((sim.flags[pin]&16)==0) { sim.PinSet(pin, 1); bitSet(sim.flags[num], 7);
		sim.snum++;  sim.srvpin[sim.snum]=pin;    return; }
		int s=0;
    if ((sim.flags[num]&128)==0 || sim.Dget[num]<min || sim.Dget[num]>max) return; //new and in range?
    for (int m=0; m<11; m++) { s=m; if (sim.srvpin[m]==pin) break; }
		bitClear(sim.flags[num], 7);
		float c= sim.Dget[num]; int n=1; 
		int lo=smin; int hi=smax; if (smax<smin) { lo=smax;  hi=smin;}
	if (abs(max-min)<=1) n=1000; 
	else if (abs(max-min)<20) n=100; 
	else if (abs(max-min)<200) n=10;
		 max*=n; min*=n;
		c=(c*n-min)*(smax-smin)/(max-min)+smin;
	if (c>=lo && c<=hi)  sim.sGau[s] = c; //servo num
 }
void ARDsim::ServoSet() {  unsigned long t=millis()-stime; 
		if (t > 19 && snum!=255) {	stime=millis(); if (t<21) {	int sort[20]; int val; byte sn[20];
			for (int i=0; i<20; i++) { sort[i]=0; sn[i]=0; }
 		for (int i=0; i<20; i++) { val = sGau[i];   int n;
 			  for (n=i-1; (n >= 0) && (val < sort[n]); n--) { sort[n+1] = sort[n];	sn[n+1]=sn[n]; }
 			  sort[n+1] = val; sn[n+1]=i;  } 
				int srvn=19-snum; int h=srvn;
		while (h<20) { digitalWrite(srvpin[sn[h]], HIGH);  delayMicroseconds(2);  h++;  }
				h=sort[srvn]-((snum-1)*8);   //rise 8us*num  
			 delayMicroseconds(h); digitalWrite(srvpin[sn[srvn]], 0); h=srvn+1;
 		while (h<20) { if (sort[h]>sort[h-1]) delayMicroseconds(sort[h]-sort[h-1]);  
				digitalWrite(srvpin[sn[h]], 0);   h++; } //8us fall
			}  }	}
//--------------test -
void ARDsim::StepRes() {
		for (int s=0; s<10; s++) {
		if (mid[s]!=0) stp_dn(s, 1020);  abspos[s]=0; 
			} 	}
 void StepperGauges() {
		if (micros()-sim.inscan > 800) sim.inscan=0;
		else if (micros()-sim.inscan < 800) sim.inscan=sim.inscan+(800-sim.inscan);
	for (int s=0; s<sim.stn; s++) {
		if (sim.mid[s]!=0) { int d=sim.sdref[s]; long val;
	if ((sim.flags[d]&128)!=0) { 
 	float c = sim.Dget[d]; int n=1; 
		if (abs(sim.stmax[s])<2) n=1000; 
		else if (abs(sim.stmax[s])<10) n=100; 
		else if (abs(sim.stmax[s])<100) n=10;
		 long max=sim.stmax[s]*n; long min=sim.stmin[s]*n;  val= long(c*n);  
 		 val = map(val, min, max, 0, 1000);
	//	StepPos(s, val);
	 	 if (sim.mstep[s]==7) sim.mstep[s]=1; if (sim.mstep[s]==0) sim.mstep[s]=6; 
   		 if (val>sim.abspos[s]) { sim.StepGau(s, sim.mstep[s], 1); sim.mstep[s]++;}
   		 else {  sim.StepGau(s, sim.mstep[s], 0);  sim.mstep[s]--; }  // }
	if (val==sim.abspos[s]) bitClear(sim.flags[d], 7);
 			   }   }  }   delayMicroseconds(sim.inscan);
		 }
void StepGauge ( byte A, byte B, byte mid, byte dref, float min, float max ) {
	 sim.PinSet(A, 1); sim.PinSet(B, 1); sim.PinSet(mid, 1); 
		sim.stn++; int s=sim.stn-1;
	sim.A_coil[s] = A; sim.mid[s] = mid; sim.B_coil[s] = B;  
	sim.sdref[s]=dref; sim.stmin[s]=min; sim.stmax[s]=max;
}
void ARDsim::StepGau (byte st, int phase, int dir) {
  if (dir==1) abspos[st]++; else abspos[st]--;
  if (abspos[st] >=1000  ) return;
switch (phase) {
case 1: digitalWrite(A_coil[st],HIGH); digitalWrite(mid[st],LOW);  digitalWrite(B_coil[st],HIGH);  break;
case 2: digitalWrite(A_coil[st],HIGH); digitalWrite(mid[st],LOW);  digitalWrite(B_coil[st],LOW);  break;
case 3: digitalWrite(A_coil[st],HIGH); digitalWrite(mid[st],HIGH); digitalWrite(B_coil[st],LOW);  break;
case 4: digitalWrite(A_coil[st],LOW);  digitalWrite(mid[st],HIGH); digitalWrite(B_coil[st],LOW);  break;
case 5: digitalWrite(A_coil[st],LOW);  digitalWrite(mid[st],HIGH); digitalWrite(B_coil[st],HIGH);  break;
case 6: digitalWrite(A_coil[st],LOW);  digitalWrite(mid[st],LOW);  digitalWrite(B_coil[st],HIGH);  break;  
  }   }
void StepPos (byte st, int pos) {   //set position
  while (pos!=sim.abspos[st]) { delayMicroseconds(800);
   if (sim.mstep[st]==7) sim.mstep[st]=1; if (sim.mstep[st]==0) sim.mstep[st]=6; 
    if (pos>sim.abspos[st]) { sim.StepGau(st, sim.mstep[st], 1); sim.mstep[st]++;}
    else {  sim.StepGau(st, sim.mstep[st], 0);  sim.mstep[st]--; } 
    }  }
void ARDsim::stp_dn(byte st, int val) {
 while (val!=0) { delayMicroseconds(800);
 if (mstep[st]==0) mstep[st]=6; 
  StepGau(st, mstep[st], 0);  mstep[st]--; val--; 
 }  }
void ARDsim::stp_up(byte st, int val) {
  while (val!=0)  {  delayMicroseconds(800);
	if (mstep[st]==7) mstep[st]=1; 
  StepGau(st, mstep[st], 1); mstep[st]++; val--;
 }  }
//-------- Connect
void ARDsim::XPudp() { 
	int ps = Udp.parsePacket(); 
	if (ps) { char db[256]; Udp.read (db, ps); db[ps]='\0'; //for (int i=0; i<8; i++) Serial.print(db[i]); Serial.println(); 
	if (db[0]==88&&(db[1]==80 || db[1]==88)) { for (byte i=0; i<6; i++) flags[i+54]=db[2+i];	
			 if (ipx[3]==0 || db[1]==80) { ipx = Udp.remoteIP();  ArdInit();  iscan=1; } } 
	 else if (db[0] == 62) { int pos=1;  byte dref_ID;  char Data_read[8];      // read if output (0,2)
         while (pos < ps) {  dref_ID = db[pos];  pos+=2; int n=0;   
             while (db[pos] != 62) { Data_read[n] = db[pos];  pos++;  n++;  }    // -- data in string 
             Data_read[n]='\0';   
             Dget[dref_ID]=atof(Data_read); bitSet(sim.flags[dref_ID], 7);  pos++; }  }	 //--- pos = packetSize
 		 } 	}
//--------
void ARDsim::ArdInit() {  Udp.beginPacket(ipx, UP); Udp.write("|AR"); Udp.write(ARD+48);  Udp.endPacket(); }
void ARDsim::Send(byte type, int num, byte dir, byte mode) {  
	byte b; byte c; byte a = num /100; 
	if (a!=0) num=num-a*100; b=num /10;
	if (b!=0) num=num-b*10; c=num;
	Udp.beginPacket(ipx, UP);  Udp.write(flags[59]); 
	Udp.write(ARD); Udp.write(flags[54+type]); 
	if (a>0) Udp.write(a+48);  
	if (b>0 || a>0) Udp.write(b+48); 
	Udp.write(c+48); 
	if (mode>0) { Udp.write('/');
		if (mode<65) mode+=48; Udp.write(mode); }   // mode - 1-8,  or A,B,C...
	if (dir>0) Udp.write(41+dir*2); 					 // + or -  or no
	Udp.endPacket(); } 
void SimInput(byte num) { sim.Send(4,num); }	
void ARDsim::AIn(byte num,  int val, byte t) { 		
		byte b; byte a = num /10;  	
		char value[5]; itoa(val, value, 10); //value[4]='\0';
		if (a!=0) num=num-a*10; b=num;
		byte d; byte c = val /10; 
		if (c!=0) val=val-c*10; d=val;
	Udp.beginPacket(ipx, UP);  Udp.write(flags[59]);
		Udp.write(ARD); Udp.write(flags[56]) ; 
		if (a>0) Udp.write(a+48);
		Udp.write(b+48); 
	if (t==1) { Udp.write('/'); if (c>0) Udp.write(c+48);
		Udp.write(d+48); }
	else { Udp.write(' '); Udp.write(value); }
	 Udp.endPacket(); }

void ARDsim::Cmnd(char Data_com[]) { 
	boolean sim=0; int cm=0;
	if (Data_com[0]=='$') Data_com[0]='0';
  if (Data_com[0]=='s' && Data_com[1]=='i' && Data_com[2]=='m' && Data_com[3]=='/') sim=1;
	Udp.beginPacket(ipx, XP_PORT); 
if (Data_com[1]==0)  Udp.write("CHAR0"); 
	else { 
		if (Data_com[0]=='0') Udp.write("CMND"); 
		else Udp.write("CMND0");	if (sim==0) Udp.write("sim/"); 
		}
	Udp.write(Data_com) ;
	Udp.endPacket(); 
		} 
//----------- cust
void ARDsim::Dref(char* dref, float Data) {    
	boolean sim=0;  int cm=0;  int n = 0;	int m=0;
	union{ byte bv[4]; float fv;} bf; 
    char DataRef[501];
	  if (dref[0]=='$') cm=1;
	  if (dref[0]=='s' && dref[1]=='i' && dref[2]=='m' && dref[3]=='/') sim=1;
	if (sim==0 && cm==0) { DataRef[0]='s'; DataRef[1]='i'; DataRef[2]='m'; DataRef[3]='/'; m=4; } 
	while (dref[n+cm]) {DataRef[m] = dref[n+cm]; n++; m++; } 
	if (dref[n-1]!=']') { DataRef[m]='['; DataRef[m+1]='0'; DataRef[m+2]=']'; m+=3; }
	for (int i = m; i < 500; i++) DataRef[i] = char(32); DataRef[500] = char(0);

	Udp.beginPacket(ipx, XP_PORT);
	Udp.write("DREF0"); 
	    bf.fv = Data; 
        for (int i=0; i<4; i++)  Udp.write(bf.bv[i]); 
    Udp.write(DataRef); 
    Udp.endPacket(); 
 } 
void ARDsim::Menu(int mnum) {  
	char trans2[4];
	Udp.beginPacket(ipx, XP_PORT); 
	Udp.write("MENU0") ;  
	Udp.write(itoa(mnum, trans2, 10));
	Udp.endPacket(); 
		} 
void XPDref (char* DRef, float Val) { sim.Dref (DRef, Val); }
void XPCmnd (char* Com) { sim.Cmnd (Com); }
void XPMenu (int MenuNum)  { sim.Menu (MenuNum); }
