#include "mbed.h"
#include "L3G4200D.h"
#include "math.h"

Timer timer;
Serial pc(USBTX,USBRX);
L3G4200D gyro(D14, D15);
int g[3]={0, 0, 0};
AnalogIn Analog(A0);
float tulos;
float vali;
float e;
float lux;

int main() 
{

timer.start();
timer.reset();
	while(true)
	{
		unsigned long aika = timer.read_ms();
		//timer.reset();
		
		//Vakiotason korjaukset, testaa ja muuta nollat tarpeen mukaan...
		
		tulos=Analog.read();
	
		
        lux=0.00002*exp(18.388*tulos);
		//Aikaleiman tulostus (ms)
                pc.printf("%f %f L", tulos,lux);


		
		
		pc.printf("\r\n");

		
		
	}
}	
