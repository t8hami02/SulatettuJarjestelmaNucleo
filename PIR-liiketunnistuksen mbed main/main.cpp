#include "mbed.h"

AnalogIn ain(A0);
AnalogIn ain2(A1);
AnalogOut aout(A2);

Timer timer;
Serial pc(USBTX,USBRX);
//DigitalIn button (PC_13);


float lux;
float pirArvo;
float ainArvo;

float luxGet()
{
	float mittaus;
	float ress;
	float janniteR;
	float tulos;
	
		mittaus = ain.read();
		
		//lasketaan anturin resistanssi
		janniteR = mittaus * 3.3;
		ress = 3.3/janniteR *11910 - 11910;
		
		//muutetaan anturin resistanssi lux-arvoksi kalibrointi kaavalla
		tulos = 3 * pow(10.0, 7.0) * pow(ress, -1.641);
		
		return tulos;
}

bool liikkeenTunnistus()
{
	float pir;
	bool vipu = true;
	float aika2;
	float raja = 1500.0;
	Timer timer2;
	
	pir = ain2.read();
	
	if(pir > 0.5)
	{
		timer2.start();
		aika2 = timer2.read_ms();
		while (aika2 < raja && vipu == true)
			{
				aika2 = timer2.read_ms();
				pir = ain2.read();				
				
				if( pir < 0.5)
				{
					vipu = false;
					timer2.reset();
					timer2.stop();
					return false;
				}
			}
			if ( aika2 > raja)
			{
				timer2.reset();
				timer2.stop();
				return true;
			}		
	}
	else
	{
		return false;
	}
}


int main() 
{
pc.baud(9600);
	while(true)
	{
		lux = luxGet();
		
		if( lux < 50)
		{
			aout.write(0.66);
		}
		else
		{
			aout.write(0.0);
		}
		
		if(liikkeenTunnistus() == true)
		{
			pc.printf("1");			
			ThisThread::sleep_for(3000);
		}

		
	}
}	


