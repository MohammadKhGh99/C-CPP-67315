#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SpreaderDetectorParams.h"

#define USAGE_MSG "Usage: ./SpreaderDetectorBackend <Path to People.in> <Path to Meetings.in>\n"
#define INPUT_ERR_MSG "Error in input files.\n"
#define OUTPUT_ERR_MSG "Error in output file.\n"
#define MAX_LINE_LEN 1025
#define SPACE " "
#define NEW_LINE "\r\n"

/**
 * this struct represents the person.
 */
typedef struct Person
{
	char *name;
	long id;
	float age;
	struct Person *sons;
	struct Person *parent;
	float probability;
	int sonNum;
	int printed;
} Person;

Person firstInfected;
Person *people;
Person *peopleProbability;
int peopleNum = 0;
int peopleInMeetings = 0;

/**
 * this function used to free the tree of infected people.
 * @param root the root of the tree to free.
 */
void freeingPeopleArray(Person *root)
{
	// people not NULL
	if (root->sons == NULL)
	{
		if (root->name != NULL)
		{
			free(root->name);
			root->name = NULL;
		}
		free(root);
		root = NULL;
		return;
	}
	for (int i = 0; i < root->sonNum; ++i)
	{
		freeingPeopleArray(&root->sons[i]);
	}
}

void freeing(Person *root)
{
	if (root->sons == NULL)
	{
		return;
	}
	for (int i = 0; i < root->sonNum; ++i)
	{
		freeing(&root->sons[i]);
	}
	free(root->sons);
	root->sons = NULL;
}


/**
 * this function used to exit the program if there is a problem with something in running time or just to free al the
 * the allocated memory for the program after finishing with it.
 * @param peopleFile the people file.
 * @param meetingsFile the meetings file.
 * @param outputFile the output file.
 * @param flag 1 if there is a problem and 0 otherwise.
 */
void exiting(FILE *peopleFile, FILE *meetingsFile, FILE *outputFile, int flag)
{
	if (flag)
	{
		fprintf(stderr, STANDARD_LIB_ERR_MSG);
	}
	if (peopleFile != NULL)
	{
		fclose(peopleFile);
	}
	if (meetingsFile != NULL)
	{
		fclose(meetingsFile);
	}
	if (outputFile != NULL)
	{
		fclose(outputFile);
	}

	if (people != NULL)
	{
		for (int i = 0; i < peopleNum; ++i)
		{
			if (people[i].name != NULL)
			{
				free(people[i].name);
				people[i].name = NULL;
			}
		}
		free(people);
	}

	freeing(&firstInfected);

	if (peopleProbability != NULL)
	{
		free(peopleProbability);
	}
}

/**
 * this function to give the given person his adjectives.
 * @param line the line to read.
 * @param person the person to give adjectives.
 */
void readPerson(char *line, Person *person)
{
	char *name = strtok(line, SPACE);
	long id = strtol(strtok(NULL, SPACE), NULL, 10);
	float age = strtof(strtok(NULL, SPACE), NULL);
	person->name = name;
	person->age = age;
	person->id = id;
}

/**
 * this function read the people file and save all the people into an array.
 * @param peopleFile the people file.
 * @param meetingsFile the meetings file.
 * @param outputFile the output file.
 */
void loadPeople(FILE *peopleFile, FILE *meetingsFile, FILE *outputFile, int *flag)
{
	char line[1025];
	int lineNum = 0;
	while (fgets(line, MAX_LINE_LEN, peopleFile) != NULL)
	{
		peopleNum++;
		strtok(line, NEW_LINE);
		Person person;
		readPerson(line, &person);
		if (peopleNum == 1)
		{
			people = (Person *) malloc(peopleNum * sizeof(Person));
		}
		else
		{
			people = (Person *) realloc(people, peopleNum * sizeof(Person));
		}
		if (people == NULL)
		{
			exiting(peopleFile, meetingsFile, outputFile, 1);
			exit(EXIT_FAILURE);
		}
		people[peopleNum - 1].age = person.age;
		people[peopleNum - 1].id = person.id;
		people[peopleNum - 1].name = (char *) malloc(strlen(person.name) + 1);
		if (people[peopleNum - 1].name == NULL)
		{
			exiting(peopleFile, meetingsFile, outputFile, 1);
			exit(EXIT_FAILURE);
		}
		strncpy(people[peopleNum - 1].name, person.name, strlen(person.name) + 1);

		people[peopleNum - 1].sonNum = 0;
		people[peopleNum - 1].sons = NULL;
		people[peopleNum - 1].parent = NULL;
		people[peopleNum - 1].probability = 0;
		people[peopleNum - 1].printed = 0;
		lineNum++;
	}
	if (lineNum == 0)
	{
		(*flag) = 0;
	}
}

/**
 * this function compare between two people by id.
 * @param p1 the first person.
 * @param p2 the second person.
 * @return 1 if p1's id is bigger that p2'id, -1 if p1's id smaller than p2's id, 0 if they equal.
 */
int personIdCompare(const void *p1, const void *p2)
{
	if (((Person *) p1)->id > ((Person *) p2)->id)
	{
		return 1;
	}
	else if (((Person *) p1)->id < ((Person *) p2)->id)
	{
		return -1;
	}
	return 0;
}

/**
 * this function search for the given id number in the given sorted array by binary search.
 * @param array the sorted array to search in.
 * @param left the left index to start from.
 * @param right the right index to end in.
 * @param id the id number to search for.
 * @return if we found the person with the given id number we return the person object, else we return a NULL pointer.
 */
Person *binarySearch(Person *array, const int left, const int right, const long id)
{
	if (right >= left)
	{
		int mid = left + (right - left) / 2;
		if (array[mid].id == id)
		{
			array[mid].printed = 1;
			return &array[mid];
		}
		if (array[mid].id > id)
		{
			return binarySearch(array, left, mid - 1, id);
		}
		return binarySearch(array, mid + 1, right, id);
	}
	return NULL;
}

/**
 * this function calculates the probability to get infected to the person that has met the given person.
 * @param person the person to get his probability.
 * @param dist the distance from the other person.
 * @param time the time that they were with each other with the given distance.
 * @return the appropriate probability.
 */
float getProbability(const Person person, const float dist, const float time)
{
	if (person.parent != NULL)
	{
		return person.probability * ((time * MIN_DISTANCE) / (dist * MAX_TIME));
	}
	return ((time * MIN_DISTANCE) / (dist * MAX_TIME));
}

/**
 * this function finds the person with the given id number.
 * @param father the person to search in his sons.
 * @param id the id number to search for.
 * @return a Person object if we found him, NULL pointer otherwise.
 */
Person *find(Person *father, const long id)
{
	if (father == NULL)
	{
		return NULL;
	}
	if (father->id == id)
	{
		return father;
	}
	for (int i = 0; i < (*father).sonNum; ++i)
	{
		if (father->sons[i].id == id)
		{
			return &father->sons[i];
		}
	}
	for (int j = 0; j < (*father).sonNum; ++j)
	{
		Person *temp = find(&father->sons[j], id);
		if (temp != NULL)
		{
			return temp;
		}
	}
	return NULL;
}

/**
 * this function reads the meetings file and save all the people with the people that has met in a "tree".
 * @param peopleFile the people file.
 * @param meetingsFile the meetings file.
 * @param outputFile the output file.
 */
void loadMeetings(FILE *peopleFile, FILE *meetingsFile, FILE *outputFile, const int *flag)
{
	char line[1025];
	if (fgets(line, MAX_LINE_LEN, meetingsFile) != NULL)
	{
		if (!(*flag))
		{
			exiting(peopleFile, meetingsFile, outputFile, 0);
			fprintf(stderr, INPUT_ERR_MSG);
			exit(EXIT_FAILURE);
		}
		qsort(people, peopleNum, sizeof(Person), personIdCompare);
		long curId = strtol(strtok(line, NEW_LINE), NULL, 10);
		firstInfected = *binarySearch(people, 0, peopleNum - 1, curId);
	}
	else
	{
		return;
	}

	firstInfected.parent = NULL;
	firstInfected.probability = 1;
	Person *currentSpreader = &firstInfected;
	currentSpreader->sonNum = 0;
	int currentInfected = 0, num = 0;
	peopleInMeetings++;

	peopleProbability = (Person *) malloc(peopleNum * sizeof(Person));
	if (peopleProbability == NULL)
	{
		exiting(peopleFile, meetingsFile, outputFile, 1);
		exit(EXIT_FAILURE);
	}
	peopleProbability[0] = *currentSpreader;

	while (fgets(line, MAX_LINE_LEN, meetingsFile) != NULL)
	{
		if (currentInfected == 0)
		{
			currentSpreader->sonNum = 0;
		}

		strtok(line, NEW_LINE);
		long firstId = strtol(strtok(line, SPACE), NULL, 10);

		if (currentSpreader->id != firstId)
		{
			for (int i = 0; i < currentSpreader->sonNum; ++i)
			{
				currentSpreader->sons[i].parent = currentSpreader;
			}

			currentSpreader = find(&firstInfected, firstId);
			currentInfected = 0;
		}

		num++;
		currentInfected++;
		peopleInMeetings++;
		long secondId = strtol(strtok(NULL, SPACE), NULL, 10);
		float dist = (float) strtof(strtok(NULL, SPACE), NULL);
		float time = (float) strtof(strtok(NULL, SPACE), NULL);

		Person son = *binarySearch(people, 0, peopleNum - 1, secondId);
		currentSpreader->sonNum++;
		son.probability = getProbability(*currentSpreader, dist, time);
		if (currentInfected == 1)
		{
			currentSpreader->sons = (Person *) malloc(currentInfected * sizeof(Person));
		}
		else
		{
			currentSpreader->sons = (Person *) realloc(currentSpreader->sons, currentInfected * sizeof(Person));
		}
		if (currentSpreader->sons == NULL)
		{
			exiting(peopleFile, meetingsFile, outputFile, 1);
			exit(EXIT_FAILURE);
		}
		son.sonNum = 0;
		currentSpreader->sons[currentInfected - 1] = son;
		peopleProbability[num] = son;
	}
}

/**
 * this function to compare between two people by their probabilities.
 * @param p1 the first Person.
 * @param p2 the second Person.
 * @return 1 if the probability of the first person is bugger than the other, -1 if the probability of the first
 * perosn is smaller than the other person, 0 if equal.
 */
int compareProbabilities(const void *p1, const void *p2)
{
	if (((Person *) p1)->probability < ((Person *) p2)->probability)
	{
		return 1;
	}
	else if (((Person *) p1)->probability > ((Person *) p2)->probability)
	{
		return -1;
	}
	return 0;
}

/**
 * this function check if the given file exists or not.
 * @param peopleFile the people file.
 */
void checkPeopleFile(FILE *peopleFile)
{
	if (peopleFile == NULL)
	{
		fprintf(stderr, INPUT_ERR_MSG);
		exit(EXIT_FAILURE);
	}
}

/**
 * this function check if the first given file exists or not.
 * @param meetingsFile the meetings file.
 * @param peopleFile the people file.
 */
void checkMeetingsFile(FILE *meetingsFile, FILE *peopleFile)
{
	if (meetingsFile == NULL)
	{
		fprintf(stderr, INPUT_ERR_MSG);
		fclose(peopleFile);
		exit(EXIT_FAILURE);
	}
}

/**
 * this function prints the people by order of their probabilities.
 * @param outputFile the output file to write to.
 */
void printByOrder(FILE *outputFile)
{
	for (int i = 0; i < peopleInMeetings; ++i)
	{
		if (peopleProbability[i].probability >= MEDICAL_SUPERVISION_THRESHOLD)
		{
			fprintf(outputFile, MEDICAL_SUPERVISION_THRESHOLD_MSG, peopleProbability[i].name, peopleProbability[i].id);
		}
		else if (peopleProbability[i].probability >= REGULAR_QUARANTINE_THRESHOLD)
		{
			fprintf(outputFile, REGULAR_QUARANTINE_MSG, peopleProbability[i].name, peopleProbability[i].id);
		}
		else
		{
			fprintf(outputFile, CLEAN_MSG, peopleProbability[i].name, peopleProbability[i].id);
		}
		peopleProbability[i].printed = 1;
	}
	if (peopleNum != peopleInMeetings)
	{
		for (int i = 0; i < peopleNum; ++i)
		{
			if (!people[i].printed)
			{
				fprintf(outputFile, CLEAN_MSG, people[i].name, people[i].id);
				people[i].printed = 1;
			}
		}
	}
}

/**
 * this function is the main function.
 * @param argc the number of arguments in the command line.
 * @param argv the array of the arguments in the command line.
 * @return 0.
 */
int main(int argc, char **argv)
{
	if (argc != 3)
	{
		fprintf(stderr, USAGE_MSG);
		exit(EXIT_FAILURE);
	}

	FILE *peopleFile = fopen(argv[1], "r");
	checkPeopleFile(peopleFile);

	FILE *meetingsFile = fopen(argv[2], "r");
	checkMeetingsFile(meetingsFile, peopleFile);

	FILE *outputFile = fopen(OUTPUT_FILE, "w");
	if (outputFile == NULL)
	{
		fprintf(stderr, OUTPUT_ERR_MSG);
		fclose(peopleFile);
		fclose(meetingsFile);
		exit(EXIT_FAILURE);
	}

	int flag = 1;
	loadPeople(peopleFile, meetingsFile, outputFile, &flag);
	loadMeetings(peopleFile, meetingsFile, outputFile, &flag);
	if (peopleProbability != NULL)
	{
		qsort(peopleProbability, peopleNum, sizeof(Person), compareProbabilities);
	}
	printByOrder(outputFile);
	exiting(peopleFile, meetingsFile, outputFile, 0);

	return 0; // or exit(EXIT_SUCCESS);
}
