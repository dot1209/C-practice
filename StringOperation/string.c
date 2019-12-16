#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void removed(char str[])	{

		char new[1024] = {0};
		int i, j;

		for(i = 0; i < 1024; i++)	{

				if(str[i] == ' ' && str[i+1] == ' ')
						str[i] = '*';
		}		

		j=0;

		for(i = 0; i < 1024; i++)	{

				if(str[i] != '*')	{

						new[j] = str[i];
						j++;
				}
		}

		for(i = 0; i < 1024; i++)
				str[i] = 0;

		for(i = 0; i < j; i++)	
				str[i] = new[i];
}

void lower(char str[])	{

		int i;

		for(i = 0; i < 1024; i++)
				str[i] = tolower(str[i]);
}

char *strreplace(char *str, char *find, char *rep)	{

		int findlen = strlen(find);
		int replen = strlen(rep);
		int len = strlen(str) + 1;
		int gap = 0;

		char *result = (char*)malloc(sizeof(char) * len);
		strcpy(result, str);

		char *former = str;
		char *location = strstr(former, find);

		while(location != NULL)	{

				gap = gap + (location - former);
				result[gap] = '\0';

				len = len + (replen - findlen);

				result = (char*)realloc(result, sizeof(char) * len);

				strcat(result, rep);
				gap = gap + replen;

				former = location + findlen;
				strcat(result, former);

				location = strstr(former, find);
		}

		return result;
}

int main(int argc, char *argv[])	{

		char str[1024];

		while(fgets(str, sizeof(str), stdin) != NULL)	{

				if(argc == 2)	{

						if(argv[1][0] == '-' && argv[1][1] == 'l')	{

								lower(str);
								printf("%s", str);
						}

						if(argv[1][0] == '-' && argv[1][1] == 'r')	{

								removed(str);
								printf("%s", str);
						}
				}

				else if(argc == 4)	{

						if(argv[1][0] == '-' && argv[1][1] == 's')

								printf("%s", strreplace(str, argv[2], argv[3]));
				}

		}

		return 0;
}
