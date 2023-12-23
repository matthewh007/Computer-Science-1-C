//Name: Matthew Hernandez
//Dr. Andrew Steinberg
//COP3502 Computer Science 1
//Programming Assignment 5 Solution

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 2000

typedef struct{
	char * name; //dynamic string
	int rank;
}player_t;

//function prototype(s)
player_t* scanRoster(player_t *roster);
player_t* merge(player_t *roster,int firstElmt, int mid, int totalSize);
player_t* sortTeam(player_t *roster,int firstElmt, int totalSize);
void cleanUp(player_t* roster);
double averageFinder(player_t*team);

int main(void)
{
	int seed;
	printf("Enter seed: ");
	scanf("%d", &seed);
	srand(seed);

	player_t *roster = (player_t*) malloc(sizeof(player_t) * MAX);
	player_t *team1 = (player_t*) malloc(sizeof(player_t) * MAX / 2);
	player_t *team2 = (player_t*) malloc(sizeof(player_t) * MAX / 2);

	roster = scanRoster(roster);

	double average1 = 0;
	double average2 = 0;

    roster=sortTeam(roster,0,(MAX-1)); //roster gets sorted here

    //for loop that separates the roster into both of the teams
    for(int i=0;i<MAX;i++)
    {
        //if loop that inputs the roster elements into the second team when it reaches 1000
        if(i>=MAX/2)
        {
            team2[i-MAX/2]=roster[i];
            strcpy(team2[i-MAX/2].name,roster[i].name);
            team2[i-MAX/2].rank=roster[i].rank;
            continue;
        }

        team1[i]=roster[i];
        strcpy(team1[i].name,roster[i].name);
        team1[i].rank=roster[i].rank;

    }
    //getting both averages for both team by using averageFinder
    average1=averageFinder(team1);
    average2=averageFinder(team2);

	printf("Team 1 Rank Average is: %f\n", average1);
	printf("Team 2 Rank Average is: %f\n", average2);

	//freeing all arrays used
    free(roster);
    free(team1);
    free(team2);

	return 0;
}
//function that finds the average of a team
double averageFinder(player_t*team)
{
    double average=0;
    for(int i=0;i<MAX/2;i++)
    {
        average=team[i].rank+average;
    }
    average=average/(MAX/2);
    return average;
}
player_t* scanRoster(player_t *roster)
{
	FILE *fptr = fopen("players.txt", "r");
    char name[20];
    int index = 0;
    while(fscanf(fptr, "%s", name) == 1)
    {
        roster[index].name = (char *) malloc(sizeof(char) * 20);
        strcpy(roster[index].name, name);
        roster[index].rank = rand() % 5 + 1;
        ++index;
    }
    fclose(fptr);
    return roster;
}

//the merge function for the mergesort
player_t* merge(player_t *roster,int firstElmt, int mid, int totalSize)
{
    int n1=mid-firstElmt+1;
    int n2=totalSize-mid;
    //allocated memory for both different arrays
    player_t* leftarr= (player_t*) malloc(sizeof(player_t) *n1);
    player_t* rightarr=(player_t*) malloc(sizeof(player_t) *n2);

     //made 2 for loops to allocate memory for the string name
    for(int i=0;i<n1;i++)
    {
        leftarr[i].name= (char *) malloc(sizeof(char) * 20);
    }
    for(int i=0;i<n2;i++)
    {
        rightarr[i].name= (char *) malloc(sizeof(char) * 20);
    }
    //made a for loop to put the roster into both sub arrays
    for(int x = 0; x < n1; ++x)
    {
        leftarr[x] = roster[firstElmt + x];
        strcpy(leftarr[x].name,roster[firstElmt + x].name);
        leftarr[x].rank=roster[firstElmt + x].rank;
    }

    for(int x = 0; x < n2; ++x)
    {
        rightarr[x] = roster[mid+ x + 1];
        strcpy(rightarr[x].name,roster[mid+x+1].name);
        rightarr[x].rank=roster[mid+x+1].rank;
    }

    int x = 0;
    int y = 0;
    int z = firstElmt;
    //while loop that does the main sorting and puts the left and right array back into the roster depending on which has a greater value in the rank
    while(x<n1&&y<n2)
    {
        if(leftarr[x].rank<=rightarr[y].rank)
        {
            roster[z] = leftarr[x];
            strcpy(roster[z].name,leftarr[x].name);
            roster[z].rank=leftarr[x].rank;
            x++;
        }
        else
        {
            roster[z] = rightarr[y];
            strcpy(roster[z].name,rightarr[y].name);
            roster[z].rank=rightarr[y].rank;
            y++;
        }
        z++;
    }
    //while loop to copy the left array back into the main roster
    while (x < n1)
    {
        roster[z] = leftarr[x];
        strcpy(roster[z].name,leftarr[x].name);
        roster[z].rank=leftarr[x].rank;
        x++;
        z++;
    }
    //while loop to copy the right array back into the main roster
    while (y < n2)
    {
        roster[z] = rightarr[y];
        strcpy(roster[z].name,rightarr[y].name);
        roster[z].rank=rightarr[y].rank;
        y++;
        z++;
    }
    free(rightarr);
    free(leftarr);
    return roster;
}
//the mergesort function that uses the player, the left most and right most element in the array for the parameters
player_t* sortTeam(player_t*roster,int firstElmt, int totalSize)
{
    if(firstElmt < totalSize)
    {
        int middle=(firstElmt+totalSize)/2;
        sortTeam(roster,firstElmt,middle);
        sortTeam(roster,middle+1,totalSize);
        merge(roster,firstElmt,middle,totalSize);
    }
    return roster;
}
