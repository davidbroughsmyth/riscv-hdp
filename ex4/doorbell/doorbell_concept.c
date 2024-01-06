//#include <stdio.h>

void sleep(int seconds)
{
        int i;
        for (i = 0; i < seconds * 1000000; i++)
        {
                asm("nop");
        }
}

int main()
{
int DOORBELL_GPIO = 1;
int BELL_GPIO = 0;

while(1)
{
        if (DOORBELL_GPIO == 1)
        {
                BELL_GPIO = 1;
//		printf("Beep");
                sleep(1);
                BELL_GPIO = 0;
//		printf("Boop");
                sleep(1);
                
                DOORBELL_GPIO = 0;
        }
        else
        {
                BELL_GPIO = 0;                
                DOORBELL_GPIO = 1;
        }
}
return 0;
}
