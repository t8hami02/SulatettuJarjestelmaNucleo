#include "mbed.h"

AnalogIn ain(A0);
AnalogIn ain2(A1);

Timer timer;
Serial pc(USBTX,USBRX);

long aika = 0;

float lux;
float pirArvo;


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
	
	pir = ain2.read();
	
	if(pir > 0.5)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int main() 
{

timer.start();
timer.reset();
	while(true)
	{
		
		if (liikkeenTunnistus() == true)
		{
			
			lux = luxGet();
			if(lux < 50)
			{
				
				//pc.printf("Ota kuva pimealla");
				//pc.printf("\r\n");
			}
			else
			{
				//pc.printf("Ota kuva valoisalla");
				//pc.printf("\r\n");
			}
			
			pc.printf("1");
			pc.printf("\r\n");
			
			ThisThread::sleep_for(5000);
			//wait_ms(3000);
		}
		
		//lux = luxGet();
		//pirArvo = ain2.read();
		//pc.printf("%f", pirArvo);
		//pc.printf("\r\n");
		
	}
}	


