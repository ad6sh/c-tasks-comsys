#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int
main(int argc, const char **argv)
{
	// argc = Number of arguments provided + 1
	// argv = Array of the arguments provided as string.
	// BUT: argv[0] = Name of the program, argv[1] = The first argument,
	//      argv[2] = The second argument, ...
	//printf("The name of this program is %s\n", argv[0]);
	//printf("This program was called with %i argument(s)\n", argc-1);
	char defaultString[] = "We are The Knights Who Say \"Ni!\". We demand a shrubbery. One that looks nice. And not to expensive.";
	
	if(argc == 1)
	{
		puts(defaultString);
	}
	else if (argc >= 2)
	{
		bool isShrubbery = false;
		int itCount = 0;
		for(int i = 1; i < argc ; i++)
		{			
			if(strcmp("shrubbery", argv[i]) == 0)
			{
				isShrubbery = true;
			}
			if(strcmp("it", argv[i]) == 0)
			{
				itCount++;
			}
		}
		if(itCount >= 5)
		{
			puts("Arrhhg!");
		}
		else if(isShrubbery)
		{
			puts("We are no longer The Knights Who Say \"Ni!\". We are now The Knights Who Say Ekki-Ekki-Ekki-Ekki-PTANG. Zoom-Boing. Z'nourrwringmm. Bring us another shrubbery. Slightly higher than the first one. Then you now must cut down the mightiest tree in the forest - with a herring!");
		}
		else
		{
			puts(defaultString);
		}
		
	}
	
	return EXIT_SUCCESS;
}

