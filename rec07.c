//Author: Bemnet Merkebu
//CSCE-3600
//Date: 3 April, 2023

#include <stdio.h>
#include <string.h>
#include <pthread.h>

#define SIZE 50

char sentence[2000];
int  ind = 0;
//initialize mutex lock
pthread_mutex_t printer_mutex = PTHREAD_MUTEX_INITIALIZER;

char convertUppercase(char lower)
{
	//Converts lowercase to uppercase
	if ((lower > 96) && (lower < 123))
	{
		return (lower - 32);
	}
	else
	{
		return lower;
	}
}

void printChar()
{
	//prints the converted sentence
	printf("The new sentence is [%d]: \t%c\n", ind, sentence[ind]);
	ind++;
}

void *convertMessage(void *ptr)
{
	//lock the mutex lock
	pthread_mutex_lock(&printer_mutex);
	// Function that each threads initiates its execution
	if (ind % 2)
	{
		sentence[ind] = convertUppercase(sentence[ind]);
	}
	
	printChar();
	//unlock the mutex lock
	pthread_mutex_unlock(&printer_mutex);

	return 0;
}

int main()
{
	int i;
	char buffer[SIZE];
	char *p;
	pthread_t ts[SIZE]; // define up to 50 threads

	printf("Please enter a phrase (less than 50 characters): ");

	if (fgets(buffer, sizeof(buffer), stdin) != NULL)
	{
		if ((p = strchr(buffer, '\n')) != NULL)
		{
			*p = '\0';
		}
	}

	strcpy(sentence, buffer); // copy string to char array
	
	printf("The original sentence is: \t %s\n", sentence);

	// create one thread for each character on the input word
	for (i = 0; i < strlen(buffer) + 1; ++i)
	{
		pthread_create(&ts[i], NULL, convertMessage, NULL);
	}
	
	// we wait until all threads finish execution
	for (i = 0; i < strlen(buffer); i++)
	{
		pthread_join(ts[i], NULL);
	}
	//destroy mutex lock
	pthread_mutex_destroy(&printer_mutex);
	
	printf("\n");
	
	return 0;
}
