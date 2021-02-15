/* CS Bomb test*/
/*Creator: deskpro256*/

#include<stdio.h>
#include<unistd.h>

#define RED 	"\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE 	"\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN 	"\x1b[36m"
#define RESET   "\x1b[0m"

int main()
{
	int code;

	printf(CYAN "\n Bomb Code: 7355608 \n Type the bomb code to arm it:\n" RESET);
	scanf("%d", &code);

	if (code == 7355608)
{
	printf(GREEN"Code correct!\n\n" RESET);
sleep(1);
	printf(BLUE"Bomb set!\n\n" RESET);
sleep(1);
	printf(MAGENTA"Time until explosion: 45 seconds!\n\n"RESET);
sleep(1);
	printf(YELLOW"Enter code to defuse!:\n\n"RESET);
sleep(5);
	scanf("%d", &code);
		if(code == 7355608)

		printf(GREEN"Bomb has been defused!\n\n"RESET);

			else {
			printf(GREEN".\n"RESET);

sleep(1);		printf(GREEN"..\n"RESET);

sleep(1);		printf(GREEN"...\n"RESET);

			printf(RED"*!WRONG CODE!*\n"RESET);
sleep(1);
			printf(RED"*!BOOM!*\n*!BOOM!*\n"RESET);
			printf(RED"*!BOOM!*\n*!BOOM!*\n"RESET);
			      }
}


	else {
	printf(GREEN".\n"RESET);
	sleep(1);
		printf(GREEN"..\n"RESET);
		sleep(1);
			printf(GREEN"...\n"RESET);

	printf(RED"Code incorrect! \n"RESET);
	sleep(1);
		printf(RED"*!BOOM!*\n*!BOOM!*\n"RESET);
		printf(RED"*!BOOM!*\n*!BOOM!*\n"RESET);
}




 return 0;
}

