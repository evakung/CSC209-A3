//
// CSC209 team.c
//
// Program for maintaining a personal team.
//
// Uses a linked list to hold the team players.
//
// Author: Michelle Liao
// Student Info: 999139640  cdf: g3michhy
// Author 2: Fan Yi Kung (Eva)
// Student 2 Info (if team): 998137573   cdf:c2kungfa
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

//**********************************************************************
// Linked List Definitions 
//  Define your linked list node and pointer types
//  here for use throughout the file.
//
//
//   ADD STATEMENT(S) HERE

struct player {
	char *familyName;
	char *firstName;
	char *position;
	int value;
	struct player *next;
};

struct team {
	struct player *players;
};

typedef struct player Player;
typedef struct team Team;

//**********************************************************************
// Linked List Function Declarations
//
// Functions that modify the linked list.
//   Declare your linked list functions here.
//
//   ADD STATEMENT(S) HERE

Player *makePlayer(char familyName[], char firstName[], char position[], int value);
Player *previousPlayer(Team *team, char familyName[]);

void addPlayer(Team *team, Player *player);
void printTeam(Team *team);
void printPlayer(Team *team, char familyName[]);
void deleteTeam(Team *team);
void valueCheck(Team *team, int valueToCompare);

int deletePlayer(Team *team, char familyName[]);
int checkFamilyName(Team *team, char familyName[]);
int sizeTeam(Team *team);

//**********************************************************************
// Support Function Declarations
//

void safegets (char s[], int arraySize);        // gets without buffer overflow
void familyNameDuplicate (char familyName[]);   // marker/tester friendly 
void familyNameFound (char familyName[]);       //   functions to print
void familyNameNotFound (char familyName[]);    //     messages to user
void familyNameDeleted (char familyName[]);
void printTeamEmpty (void);
void printTeamTitle(void);
void printNoPlayersWithLowerValue(int value);

//**********************************************************************
// Program-wide Constants
//

const int MAX_LENGTH = 1023;
const char NULL_CHAR = '\0';
const char NEWLINE = '\n';
const char GOALKEEPER = 'G';
const char DEFENDER = 'D';
const char MIDFIELDER = 'M';
const char STRIKER = 'S';


//**********************************************************************
// Main Program
//

int main (void)
{ 
    const char bannerString[]
        = "Personal Team Maintenance Program.\n\n";
    const char commandList[]
        = "Commands are I (insert), D (delete), S (search by name),\n"
          "  V (search by value), P (print), Q (quit).\n";

    // Declare linked list head.
    //   ADD STATEMENT(S) HERE TO DECLARE LINKED LIST HEAD.

 
    // announce start of program
    printf("%s",bannerString);
    printf("%s",commandList);
    
    char response;
    char input[MAX_LENGTH+1];


	//Making team linked List
	Team *team = malloc(sizeof(team));
	


    do
    {
        printf("\nCommand?: ");
        safegets(input,MAX_LENGTH+1);
        // Response is first char entered by user.
        // Convert to uppercase to simplify later comparisons.
        response = toupper(input[0]);



        if (response == 'I')
        {
            // Insert a player entry into the linked list.
            // Maintain the list in correct order (G, D, M, S).
            //   ADD STATEMENT(S) HERE


		char familyName[MAX_LENGTH];
		char firstName[MAX_LENGTH];
		char position[1];
		char inputValue[MAX_LENGTH];
		int value;

            // USE THE FOLLOWING PRINTF STATEMENTS WHEN PROMPTING FOR DATA:

        	printf("  family name: " );
		safegets(familyName,MAX_LENGTH+1);

        	printf("  first name: ");
		safegets(firstName,MAX_LENGTH+1);

        	printf("  position: ");
		safegets(position,MAX_LENGTH+1);

        	printf("  value: ");
		safegets(inputValue,MAX_LENGTH+1);
		value = atoi(inputValue);


		/*Checking for valid input*/
		if (value > 0 && (*position == GOALKEEPER || *position == DEFENDER || *position == MIDFIELDER || *position == STRIKER)){
			if (checkFamilyName(team,familyName) == 1){
				familyNameDuplicate(familyName); //checks for duplicated familyName in team
			}else{
				Player *newPlayer;			
				newPlayer = makePlayer(familyName, firstName, position, value); //if newPlayer succeds, will return Player, error will be caught within the function

				//Add player to team list 	
				addPlayer(team, newPlayer);
		
			}
		}else{
			printf("\nPlayer %s was not added onto team, please make sure you have proper values\n", familyName);
		}
        }
        else if (response == 'D')
        {
            // Delete a player from the list.

            printf("\nEnter family name for entry to delete: ");

            //   ADD STATEMENT(S) HERE

		char familyName[MAX_LENGTH];
		safegets(familyName,MAX_LENGTH+1);
		
		if( team->players == NULL || checkFamilyName(team,familyName) == 0){
			familyNameNotFound(familyName);
		}else{
			if (deletePlayer(team, familyName) == 0){ //Deletion of player succeeds
				familyNameDeleted(familyName);
			}
		}

        }
        else if (response == 'S')
        {
            // Search for a player by family name.

            printf("\nEnter family name to search for: ");

            //   ADD STATEMENT(S) HERE

		char familyName[MAX_LENGTH];
		safegets(familyName,MAX_LENGTH+1);
		
		if(team->players == NULL || checkFamilyName(team,familyName) == 0){
			familyNameNotFound(familyName);
		}else{
			familyNameFound(familyName);
			printPlayer(team, familyName);
		}
	

        }
        else if (response == 'V')
        {
            // Search for players that are worth less than or equal a value.

            printf("\nEnter value: ");

            //   ADD STATEMENT(S) HERE
		char inputValue[MAX_LENGTH];		
		int valueToCompare;

		safegets(inputValue,MAX_LENGTH+1);
		valueToCompare = atoi(inputValue);

		valueCheck(team, valueToCompare);
		
        }
        else if (response == 'P')
        {
            // Print the team.

            //   ADD STATEMENT(S) HERE
		
		if(sizeTeam(team)==0){
			printTeamEmpty();
		}else{
			printTeamTitle();
			printTeam(team);
		}

        }
        else if (response == 'Q')
        {
            ; // do nothing, we'll catch this case below
        }
        else 
        {
            // do this if no command matched ...
            printf("\nInvalid command.\n%s\n",commandList);
        }
    } while (response != 'Q');
  
    // Delete the whole linked list that hold the team.
    //   ADD STATEMENT(S) HERE
	deleteTeam(team);

    // Print the linked list to confirm deletion.
    //   ADD STATEMENT(S) HERE
	if(sizeTeam(team)==0){
		printTeamEmpty();
	}


    return 0;
}

//**********************************************************************
// Support Function Definitions

// Function to get a line of input without overflowing target char array.
void safegets (char s[], int arraySize)
{
    int i = 0, maxIndex = arraySize-1;
    char c;
    while (i < maxIndex && (c = getchar()) != NEWLINE)
    {
        s[i] = c;
        i = i + 1;
    }
    s[i] = NULL_CHAR;
}

// Function to call when user is trying to insert a family name 
// that is already in the book.
void familyNameDuplicate (char familyName[])
{
    printf("\nAn entry for <%s> is already in the team!\n"
           "New entry not entered.\n",familyName);
}

// Function to call when a player with this family name was found in the team.
void familyNameFound (char familyName[])
{
    printf("\nThe player with family name <%s> was found in the team.\n",
             familyName);
}

// Function to call when a player with this family name was not found in the team.
void familyNameNotFound (char familyName[])
{
    printf("\nThe player with family name <%s> is not in the team.\n",
             familyName);
	
}

// Function to call when a family name that is to be deleted
// was found in the team.
void familyNameDeleted (char familyName[])
{
    printf("\nDeleting player with family name <%s> from the team.\n",
             familyName);
}

// Function to call when printing an empty team.
void printTeamEmpty (void)
{
    printf("\nThe team is empty.\n");
}

// Function to call to print title when whole team being printed.
void printTeamTitle (void)
{
    printf("\nMy Team: \n");
}

// Function to call when no player in the team has lower or equal value to the given value
void printNoPlayersWithLowerValue(int value)
{
	printf("\nNo player(s) in the team is worth less than or equal to <%d>.\n", value);
}

//**********************************************************************
// Add your functions below this line.

/*
returns a new player pointer with proper allocation of familyName, firstName, and position.
*/
Player *makePlayer(char familyName[], char firstName[], char position[] ,int value){
	
	/*Allocating new space for newPlayer*/
	Player *newPlayer = malloc(sizeof(Player));
	char *newFirstName = malloc(sizeof(firstName));
	char *newFamilyName = malloc(sizeof(familyName));
	char *newPosition = malloc(sizeof(position));

	newPlayer->familyName = strncpy(newFamilyName, familyName, (strlen(familyName)+1));
	newPlayer->firstName = strncpy(newFirstName, firstName, (strlen(firstName)+1));
	newPlayer->position = strncpy(newPosition, position, (strlen(position)+1));
	newPlayer->value = value;
	
	if(newPlayer == NULL && newFamilyName == NULL && newFirstName == NULL){
		fprintf(stderr, "Failed to allocate space\n");	
		exit(1);	
	}
	
	return newPlayer;
}


/*Adds new Player to team*/
void addPlayer(Team *team, Player *player){
	
	if(team->players == NULL){ //base
		team->players = player;
	}else{
		Player *current, *temp, *previous;
		int g=0, d=0, m=0, s=0, index=0, total;

		for(current = team->players; current != NULL; current = current->next){
			if (*current->position == GOALKEEPER){
				g++;
			}else if (*current->position == DEFENDER){
				d++;
			}else if (*current->position == MIDFIELDER){
				m++;
			}else if (*current->position == STRIKER){
				s++;
			}
		}

		total = g+d+m+s; //used for conditions of sorting

		for(current = team->players; current != NULL; current = current->next){
			if (*player->position == GOALKEEPER){
				if(g == 0){
					player->next = current;
					team->players = player;
					return;
				}else{
					if(current->next == NULL || *current->next->position != GOALKEEPER){ //only added at beginning of list, therefore dont need to check for other conditions
						player->next = current->next;
						current->next = player;
						return;
					}
				}
			}else if (*player->position == DEFENDER){
				if(d+g == 0){
					player->next = current;
					team->players = player;
					return;
				}else{
					if(*current->position == MIDFIELDER || *current->position == STRIKER){
						previous = previousPlayer(team, current->familyName);
						previous->next = player;
						player->next = current;
						return;

					}else if(current->next == NULL){ //only defenders and goalies in list then
						current->next = player;
						return;
					}				
				}
			}else if (*player->position == MIDFIELDER){
				if((total-s) == 0){
					player->next = current;
					team->players = player;
					return;
				}else{
					if(*current->position == STRIKER){
						previous = previousPlayer(team, current->familyName);
						previous->next = player;
						player->next = current;
						return;
					}else if(current->next == NULL){ //skipping through goalie, def, mid
						current->next = player;
						return;
					}
				}
			}else if(*player->position == STRIKER){
				if(current->next == NULL){ //will always add onto the end of the list 
					current->next = player;
					return;
				}
			}
		}
	}	
}



void printTeam(Team *team){
	Player *temp;
	for(temp = team->players; temp != NULL; temp = temp->next){
		printPlayer(team,temp->familyName);
	}
}

void printPlayer(Team *team, char familyName[]){
	Player *temp;
	for(temp = team->players; temp != NULL; temp = temp->next){
		if(strcmp(temp->familyName, familyName) == 0){ //a match!
			printf("\n%s\n%s\n%s\n%d\n", temp->familyName, temp->firstName, temp->position, temp->value);
		}
	}
}


/*return 0 if familyName is NOT in team*/
int checkFamilyName(Team *team, char familyName[]){

	Player *temp;
	
	for(temp = team->players; temp != NULL; temp = temp->next){
		if(strcmp(temp->familyName, familyName) == 0){ //a match!
			return 1;
		}
	}
	return 0;
}


//Deletes the whole team 
void deleteTeam(Team *team){

	Player *current;	

	while (team->players != NULL){
		int size = sizeTeam(team); 
		current = team->players;
		if(size > 1){
			team->players = current->next;
			free(current);
		}else{
			team->players = NULL;
			free(team->players);
		}
		current = current->next;
	}
}


/*
Deletes the specified player, and frees the player memory
Returns 0 if deleted, 1 otherwise
*/
int deletePlayer(Team *team, char familyName[]){

	Player *current, *previous;	
	current = team->players;
	int index = 0;
	while (current != NULL){
		int size = sizeTeam(team); 
		if(strcmp(current->familyName, familyName) == 0){
			previous = previousPlayer(team, current->familyName);
			if(size > 1){
				if(index == 0){ //if wants to delete first player of the team
					team->players = current->next;
				}else{
					previous->next = current->next;
				}
				free(current);
				return 0;
			}else{
				team->players = NULL;
				free(team->players);
				return 0;
			}
		}
		index++;
		current = current->next;
	}
	return 1;
}

/*Prints players whos value are equal or less than the value given*/
void valueCheck(Team *team, int valueToCompare){

	Player *current;
	for (current=team->players; current != NULL; current = current->next){
		if(current->value <= valueToCompare){
			printPlayer(team, current->familyName);
			return;
		}
	}
	printNoPlayersWithLowerValue(valueToCompare);
}


/*Returns previous player of the given player in the team*/
Player *previousPlayer(Team *team, char familyName[]) {
	
	Player *prev, *current;
	int count = 0;

	current=team->players;
	while(current != NULL){
		if(count == 0){
			prev = current;
			count++;
			if(strcmp(familyName, current->familyName)==0){ //base case
				return prev;
			}
			current = current->next;
		}else{
			prev=current;
			current = current->next;
		}
		if(current !=NULL){
			if(strcmp(familyName, current->familyName)==0){
				return prev;
			}
		}
	}
} 

//Returns the size of the team
int sizeTeam(Team *team){

	Player *current;
	int returnValue = 0;

	for(current = team->players; current != NULL; current = current->next){
		returnValue++;
	}
	return returnValue;
}


