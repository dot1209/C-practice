#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void usage()	{

		puts("Please input command(i/d/u/f/l/q) and data :");
		puts("Insert the record : i studentID\\tname\\tphone\\temail");
		puts("Delete the record : d studentID");
		puts("Update the record : u studentID\\tname\\tphone\\temail");
		puts("Find the record : f [string]");
		puts("List the record : l");
		puts("Quit : q");

}

struct datatype	{

		int id;
		char *name;
		char *phone;
		char *email;
};

int search(char *str, struct datatype *data, int i)	{

		char *ptr = strstr(str, "studentID:");
		char *id;
		ptr += 10;
		id = malloc(10 * sizeof(char));
		strncpy(id, ptr, 9);

		if(data[i].id == atoi(id))
				return 1;
		else
				return 0;
}

char *getid(char *str)	{

		char *ptr = strstr(str, "studentID:");
		char *id = malloc(10 *sizeof(char));
		ptr += 10;

		strncpy(id, ptr, 9);

		return id;
}

char *getname(char *str)	{

		char *ptr = strstr(str, "name:");
		char *name = malloc(100 * sizeof(char));
		ptr += 5;

		int name_len = 0;

		while(isalpha(ptr[name_len]))
				name_len++;

		strncpy(name, ptr, name_len);

		return name;
}

char *getphone(char *str)	{

		char *ptr = strstr(str, "phone:");
		char *phone = malloc(10 * sizeof(char));
		ptr += 6;

		strncpy(phone, ptr, 10);

		return phone;
}

char *getemail(char *str)	{

		char *ptr = strstr(str, "email:");
		char *email = malloc(100 * sizeof(char));
		ptr += 6;

		int email_len = 0;

		while(ptr[email_len] != '	' &&  ptr[email_len] != '\n')
				email_len++;

		strncpy(email, ptr, email_len);

		return email;
}

int main()	{

		struct datatype data[200], tmp;
		char str[200];
		char input[1];
		int i, n = 0;
		int same = 0;
		int ok = 0;
		int update = 0;

		usage();

		while(scanf("%s", input) != EOF)	{

				switch(input[0])	{

						case 'i':

								if(fgets(str, sizeof(str), stdin) != NULL)	{

										data[n].id = atoi(getid(str));
										data[n].name = getname(str);						
										data[n].phone = getphone(str);
										data[n].email = getemail(str);

										if(n == 0)	{
												puts("Insert successful!");
												n++;
										}

										else	{

												for(i = 0; i < n; i++)	{

														if(data[n].id == data[i].id)
																same = 1;
												}

												if(same == 0)	{
														puts("Insert successful!");
														n++;
												}

												else
														puts("Insert error! studentID is exists!");
										}
								}

								break;

						case 'd':

								if(scanf("%s", str) != EOF)	{

										for(i = 0; i < n; i++)	{

												if(search(str, data, i) == 1)	{

														tmp = data[n-1];
														data[n-1] = data[i];
														data[i] = tmp;
														n--;
														puts("delete successful!");
												}

												else
														puts("Delete error! studentID not exists!");
										}
								}

								break;

						case 'l':

								for(i = 0; i < n; i++)	{
										printf("studentID:%d\tname:%s\t", data[i].id, data[i].name);
										printf("phone:%s\temail:%s\n", data[i].phone, data[i].email);
								}

								break;

						case 'q':

								puts("Thanks for your using!");
								return 0;

						case 'u':

								if(fgets(str, sizeof(str), stdin) != NULL)	{

										for(i = 0; i < n; i++)	{

												if(search(str, data, i) == 1)	{

														data[i].name = getname(str);
														data[i].phone = getphone(str);
														data[i].email = getemail(str);

														update = 1;
												}
										}

										if(update == 1)
												puts("Update successful!");
										else
												puts("Update error! studentID not exists!");

										update = 0;

								}

								break;

						case 'f':

								if(scanf("%s", str) != EOF)	{

										for(i = 0; i < n; i++)	{

												if(strstr(data[i].name, str) != NULL)	
														ok = 1;

												else if(strstr(data[i].phone, str) != NULL)	
														ok = 1;	

												else if(strstr(data[i].email, str) != NULL)	
														ok = 1;

												if(ok == 0)
														puts("Find error! Not exists!");
												else	{
														printf("studentID:%d\tname:%s\t", data[i].id, data[i].name);
														printf("phone:%s\temail:%s\n", data[i].phone, data[i].email);
												}
										}
								}
								
								break;
				}
		}
		return 0;
}
