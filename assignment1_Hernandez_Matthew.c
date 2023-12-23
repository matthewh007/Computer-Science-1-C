//Name: Matthew Hernandez
//COP3502C Spring 2022
//Programming Assignment 1

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define LIMIT 20

char ** doubleIt(char **arr, int *maxsize);
char ** populate(char ** words, FILE *fptr, int *currentsize, int *maxsize);
char* generateSentence(char ** noun, char ** verb, char ** adjective, char ** preposition, char ** article, int nounsize, int verbsize, int adjsize, int prepositionsize, int articlesize); //write sentence to console window
void generateStory(char ** noun, char ** verb, char ** adjective, char ** preposition, char ** article, int nounsize, int verbsize, int adjsize, int prepositionsize, int articlesize, FILE *fptr); //write story to txt file
void displaySentence(char * sentence);
void cleanUp(char ** nouns, char ** verbs, char ** adjectives, char ** prepositions, char ** articles, int nounsize, int verbsize, int adjsize, int prepositionsize, int articlesize);

int main()
{
	//setup randomness
	int x;
	printf("Enter seed: ");
	scanf("%d", &x);
	srand(x); //set seed

	//declare necessary variables
	int nounsize = 0;
	int verbsize = 0;
	int adjsize = 0;
	int prepositionsize = 0;

	int nounmaxsize = 5;
	int verbmaxsize = 5;
	int adjmaxsize = 5;
	int prepositionmaxsize = 5;
	const int articlemaxsize = 3; //there are only 3 articles in the english language a, an, and the. that is why const is applied

	printf("Welcome to the random sentence generator.\n");

	//double pointers
	char ** nouns = NULL;
	char ** verbs = NULL;
	char ** adjectives = NULL;
	char ** preposition = NULL;
	char ** articles = NULL;

	nouns = (char **) malloc(sizeof(char *) * nounmaxsize);
	verbs = (char **) malloc(sizeof(char *) * verbmaxsize);
	adjectives = (char **) malloc(sizeof(char *) * adjmaxsize);
	preposition = (char **) malloc(sizeof(char *) * prepositionmaxsize);
	articles = (char **) malloc(sizeof(char *) * articlemaxsize);

	//make sure malloc was able to allocate memory
	if(nouns == NULL || verbs == NULL || adjectives == NULL || preposition == NULL || articles == NULL)
	{
		printf("malloc was not successful\n");
		printf("Program will now terminate.\n");
		exit(1);
	}

	//populate articles using strcpy. numbers represent how many characters are needed. this includes \0 character
	articles[0] = (char *) malloc(sizeof(char) * 2);
	strcpy(articles[0], "A");
	articles[1] = (char *) malloc(sizeof(char) * 3);
	strcpy(articles[1], "An");
	articles[2] = (char *) malloc(sizeof(char) * 4);
	strcpy(articles[2], "The");

	//open the file of words
	FILE *fptr = fopen("nouns.txt", "r");
	FILE *fptr2 = fopen("verbs.txt", "r");
	FILE *fptr3 = fopen("adjectives.txt", "r");
	FILE *fptr4 = fopen("preposition.txt", "r");

	//make sure the files were opened properly
	if(fptr == NULL || fptr2 == NULL || fptr3 == NULL || fptr4 == NULL)
	{
		printf("file was not successful in opening.");
		printf("Program will now terminate.\n");
		exit(1);
	}

	//populate the dynamic array
	nouns = populate(nouns, fptr, &nounsize, &nounmaxsize); //populate nouns
	verbs = populate(verbs, fptr2, &verbsize, &verbmaxsize); //populate verbs
	adjectives = populate(adjectives, fptr3, &adjsize, &adjmaxsize); //populate adjectives
	preposition = populate(preposition, fptr4, &prepositionsize, &prepositionmaxsize); //populate prepositions

	//close the files
	fclose(fptr);
	fclose(fptr2);
	fclose(fptr3);
	fclose(fptr4);

	//now lets generate 5 sentences and write them to the console window

	printf("Let's generate some random sentences that don't make sense.\n");

	for(int x = 0; x < 5; ++x)
	{
		char * sentence = generateSentence(nouns, verbs, adjectives, preposition, articles, nounsize, verbsize, adjsize, prepositionsize, articlemaxsize);
		displaySentence(sentence);
		free(sentence);
	}

	printf("Now let's create three stories that just don't make sense.\n");
	fptr = fopen("story1.txt", "w");
	generateStory(nouns, verbs, adjectives, preposition, articles, nounsize, verbsize, adjsize, prepositionsize, articlemaxsize, fptr); //story 1
	fclose(fptr);

	fptr = fopen("story2.txt", "w");
	generateStory(nouns, verbs, adjectives, preposition, articles, nounsize, verbsize, adjsize, prepositionsize, articlemaxsize, fptr); //story 2
	fclose(fptr);

	fptr = fopen("story3.txt", "w");
	generateStory(nouns, verbs, adjectives, preposition, articles, nounsize, verbsize, adjsize, prepositionsize, articlemaxsize, fptr); //story 3
	fclose(fptr);

	cleanUp(nouns,verbs, adjectives, preposition, articles, nounmaxsize, verbmaxsize, adjmaxsize, prepositionmaxsize, 3);


	printf("The stories were generated successfully and stored in their respective text files.\n");
	printf("Check them out!\n");

	return 0;
}
//function that prints the sentence
void displaySentence(char* sentence)
{
    printf("%s", sentence);
}
//function that transfers the words from the files to the arrays in the program
char ** populate(char ** words, FILE *fptr, int *currentsize, int *maxsize)
{
    //while loop that scans the words from the file and has an if statement to increase maxsize
    while(1)
    {
        //the line under allocates every new component for the words array and then scanf adds it in
        words[*currentsize]=(char*) malloc(sizeof(char) *LIMIT );
        int end=fscanf(fptr, "%s", words[*currentsize]);

        if (end==EOF)
            break;

        (*currentsize)++;
        //if statement to increase maxsize if currentsize equals it
        if(*currentsize==*maxsize)
        {
            words = doubleIt(words,maxsize);

        }
    }
    return words;

}
//function that doubles the memory for the 2D array in the populate function
char ** doubleIt(char **arr, int *maxsize)
{
    //doubling maxsize and declaring a new array
    *maxsize = *maxsize*2;
    char **newArray = (char**)malloc(sizeof(char*) * (*maxsize));

    //for loop that allocates the components of the new array with more memory
    for(int i = 0;i < (*maxsize);i++)
        newArray[i] = (char*)malloc(sizeof(char) * (LIMIT));

    //for loop that puts the components of the old array into the new array with more memory
    for(int i = 0;i < (*maxsize)/2;i++)
       strcpy(newArray[i],arr[i]);
    //for loop that frees the components of the old array
    for(int i = 0;i < (*maxsize)/2;i++)
        free(arr[i]);

    free(arr);

    return newArray;
}
//function that creates sentences using the arrays for different types of words and their lengths
char* generateSentence(char ** noun, char ** verb, char ** adjective, char **preposition, char ** article, int nounsize, int verbsize, int adjsize, int prepositionsize, int articlesize)
{
    // made a 1D array called sentence and allocated memory for 100 characters
    char *sentence=(char*)malloc(sizeof(char) * (100));
    //for creating the sentence I used strcopy and then strcat to add to the article and rest of the sentence
    strcpy(sentence,article[rand()%articlesize]);
    strcat(sentence," ");
    strcat(sentence,adjective[rand()%adjsize]);
    strcat(sentence," ");
    strcat(sentence,noun[rand()%nounsize]);
    strcat(sentence," ");
    strcat(sentence,verb[rand()%verbsize]);
    strcat(sentence," ");
    strcat(sentence,preposition[rand()%prepositionsize]);
    strcat(sentence," ");
    strcat(sentence,article[rand()%articlesize]);
    strcat(sentence," ");
    strcat(sentence,adjective[rand()%adjsize]);
    strcat(sentence," ");
    strcat(sentence,noun[rand()%nounsize]);
    strcat(sentence,".\n");

    return sentence;
}

//function that creates a story
void generateStory(char ** noun, char ** verb, char ** adjective, char **preposition, char ** article, int nounsize, int verbsize, int adjsize, int prepositionsize, int articlesize, FILE *fptr)
{
    // made a 1D array called sentence and allocated memory for 100 characters
    char *sentence = (char*)malloc(sizeof(char)*100);
    //integer for the random range of 100-500 inclusive
    int random = (rand()%401)+100;
    //for loop that creates the story based on a random number of lines
    for(int i = 0;i < (random);i++)
    {
        sentence=generateSentence(noun, verb, adjective, preposition, article, nounsize, verbsize, adjsize, prepositionsize, articlesize);
        fprintf(fptr,"%s",sentence);
        free(sentence);

    }

}

//function that frees the arrays and the size of the array
void cleanUp(char ** nouns, char ** verbs, char ** adjectives, char **prepositions, char ** articles, int nounsize, int verbsize, int adjsize, int prepositionsize, int articlesize)
{

    //each for loop frees the components of each different type of word array
    //following that I freed the array itself
     for(int i = 0;i < nounsize+1;i++)
        free(nouns[i]);
    free(nouns);
    for(int i = 0;i < verbsize+1;i++)
        free(verbs[i]);
    free(verbs);
    for(int i = 0;i < adjsize+1;i++)
        free(adjectives[i]);
    free(adjectives);
    for(int i = 0;i < prepositionsize+1;i++)
        free(prepositions[i]);
    free(prepositions);

}

