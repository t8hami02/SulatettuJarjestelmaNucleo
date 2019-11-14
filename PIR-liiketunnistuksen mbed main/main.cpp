#include "mbed.h"
#include "L3G4200D.h"

Timer timer;
Timer timer2;
Serial pc(USBTX,USBRX);
L3G4200D gyro(D14, D15);
int g[3]={0, 0, 0};
int g2[3] ={0, 0, 0};
int ka1 = 0, ka2 = 0, ka3 = 0;
float kulma[3] = {0.0, 0.0, 0.0};
long aika2 = 0;
long aika = 0;

int main() 
{

timer.start();
timer.reset();
timer2.start();
timer2.reset();
	while(true)
	{
		
		/*
		while ( aika < 40 )
		{
			aika = timer.read_ms();
			
		}*/
		//aika2 = timer2.read_ms();
		//timer.reset();
		
		gyro.read(g);
		//Vakiotason korjaukset, testaa ja muuta nollat tarpeen mukaan...
		
		g[0] = g[0];
		g[1] = g[1] + 15;
		g[2] = g[2];
		
		kulma[0] = kulma[0]+g2[0]*70*0.001*(aika)*0.001;
		kulma[1] = kulma[1]+g2[1]*70*0.001*(aika)*0.001;
		kulma[2] = kulma[2]+g2[2]*70*0.001*(aika)*0.001;
		
		g2[0] = g[0];
		g2[1] = g[1];
		g2[2] = g[2];
		
		//Aikaleiman tulostus (ms)
        pc.printf("%i ", aika);
		
		//Gyrodatan tulostus (raakadataa; datasheetistä kalibrointi)
		/*for(int i=0; i<3; i++)
		{
                        pc.printf("%f ",kulma[i]);
						//pc.printf("%i ",g[i]);
		}*/
		
		pc.printf("\r\n");
		//wait(0.02);  //Ei tarvi odottaa jos pikavauhtia etsitään
		
		
	}
}	
