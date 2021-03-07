#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int division();
int main (void)
{
	int i;
	int score=0;
	int divisor;
	int quotient;
	int z;
	srand ((int) time (NULL));
	for(i=0;i<10;i++)
	{
		divisor = rand () % 12 + 1;
		quotient = rand () % 13;
		z=division(divisor, quotient);
		if(z==1)
		{
			printf("Correct!\n");
			score++;
		}
		else
		{
			printf("Wrong :( The correct answer is %d\n",quotient);
		}
	}
	printf("You got %d/10 correct!\n",score);
}
int division(int x,int y){
	int dividend;
	int quotient1;
	dividend=x*y;
	printf("What is %d/%d?\n",dividend,x);
	scanf("%d",&quotient1);
	if(y==quotient1)
		return 1;
	else
		return 0;
}
