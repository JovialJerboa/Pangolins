/***************************************************************************\
	pangolins.cpp

	Main source file for 
		Liam Flanagan's implementation of the Pangolins guessing game

 	Author: Liam Flanagan. liamflan@gmail.com
 	Version 3.0, 30-Mar-2010
\***************************************************************************/

// Preprocessor functions
#ifdef _MSC_VER
	#ifdef _DEBUG
		#define _CRTDBG_MAP_ALLOC	// Memory leak debugging
		#include <crtdbg.h>			// Memory leak debugging
	#endif
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pangolins.h"
#include "rlutil.h"

// Constants
const char* SAVE_FILE_NAME = "psf.txt";


/*
 *	Function: anotherGame
 *	Comments: Function the ask the user if they would like to play another
 *				game. This function will take in user input to represent
 *				this and return it as a bool.
 */
bool anotherGame()
{
	// Variable declarations
	char temp[1028];

	// User interface
	printf("Would you like another game?\n");

	// Get input from the user and take an action based on the user's input
	while(true)
	{
		fgets(temp, 1028, stdin);  	// Take the standard input into buffer
		rlutil::cls();				// Clears the screen

		// Validate the input and react based on this input
		if(strcmp(temp,"y\n") == 0			// Accept y
			|| strcmp(temp, "Y\n") == 0		// Accept Y
			|| strcmp(temp,"yes\n") == 0	// Accept yes
			|| strcmp(temp, "YES\n") == 0)	// Accept Yes
		{
			// User would like another game
			return true;
		}
		else if(strcmp(temp,"n\n") == 0			// Accept n
				|| strcmp(temp, "N\n") == 0		// Accept no
				|| strcmp(temp,"no\n") == 0		// Accept N
				|| strcmp(temp, "NO\n") == 0)	// Accept No
		{
			return false;
		}
		else
		{
			printf("Please enter a valid input\n");
		}
	}
}


/*
 *	Function: askQuestion
 *	Comments: Function to ask the question stored within a given node.
 *				The node is represented by a pointer given as a parameter.
 *				During the life cycle of this function the user is
 *				required to give input to represent the answer to the
 *				question. Dependant on the answer this function will
 *				return one of left or right hand child of the gametree.
 */
 struct node *askQuestion(struct node *reqNode)
{
	// Variable declarations
	char temp[1028];

	// User interface
	printf("%s\n",reqNode->contents);

	// User Input
	while(true)
	{
		fgets(temp, 1028, stdin);  	// Take the standard input into buffer
		rlutil::cls();				// Clear the screen

		if(strcmp(temp,"y\n") == 0			// Accept y
			|| strcmp(temp, "Y\n") == 0		// Accept Y
			|| strcmp(temp,"yes\n") == 0	// Accept yes
			|| strcmp(temp, "YES\n") == 0)	// Accept YES
		{
			return reqNode->YES_ptr;
		}
		else if(strcmp(temp,"n\n") == 0			// Accept n
				|| strcmp(temp, "N\n") == 0		// Accept no
				|| strcmp(temp,"no\n") == 0		// Accept N
				|| strcmp(temp, "NO\n") == 0)	// Accept NO
		{
			return reqNode->NO_ptr;
		}
		else
		{
			printf("Please enter a valid input\n");
		}
	}
}


/*
 *	Function: beginGame
 *	Comments: Function to do all the inital setup that is required
 *				before the game loop can be run and then run the
 *				game.
 */
void beginGame()
{
	// Check if SAVE_FILE_NAME can be opened
	if(fopen(SAVE_FILE_NAME, "r") == NULL)
	{
		runGame(buildInitialTree(), 0);
	}
	else
	{
		// Number of nodes in the game tree
		int nodeCount = countSavedNodes();
		struct node *rootNode = openGame();
		// Run the game
		runGame(rootNode, nodeCount);
	}
}


/*
 *	Function: buildInitialTree
 *	Comments: Function to build the initial gametree. This will only be
 *				run if a gamesave file cannot be opened.
 */
struct node *buildInitialTree()
{
	// Make all the nodes
	struct node *node0 = (node*)malloc(sizeof(struct node));

	// Define the contents of node0
	node0->nodeID = 0;
	node0->isQuestion = 0;
	node0->YES_ptr = NULL;
	node0->NO_ptr = NULL;
	node0->PAR_ptr = NULL;
	node0->contents = (char*)malloc(sizeof("Pangolin"));
	strcpy(node0->contents, "Pangolin");
	return node0;
}


/*
 *	Function: countSavedNodes
 *	Comments: Function to count the number of nodes present in the
 *				gamesave file. Each node is represented by a single
 *				line in the textfile.
 */
int countSavedNodes()
{
	// Variable declarations
	int endOfFile = 0;
	char currLine[300];        // Current line
	char lastLine[300];        // Last line looked at
	int nodeCount = 0;

	// Make a file and open it
	FILE *myFile;
	myFile = fopen(SAVE_FILE_NAME, "r");

	// Reading code
	while(endOfFile != 1)
	{
		strcpy(lastLine, currLine);   				// Put the last line into the last line variable
		fgets(currLine, sizeof(currLine), myFile);	// Get the next line of the file
		if(strcmp(currLine, lastLine) == 0)   		// End of file
		endOfFile = 1;
		// Only do it once for each line  
		if(endOfFile != 1)
		nodeCount++;
	}

	// Close the file
	fclose(myFile);
	// Return nodeCount
	return nodeCount-1; 
}


/*
 *	Function: main
 *	Comments: This function defines an entry point into the pangolins
 *				runnable code.
 */
int main()
{
	beginGame();

	// Memory leak detection
	// Comment this out for release versions
	//_CrtDumpMemoryLeaks();

	return 0;
}


/*
 *	Function: guess
 *	Comments: This function takes a pointer to a node structure as
 *				a paremeter and displays this as a computed guess to
 *				the user via a basic UI. During the life cycle of this
 *				function the user is required to give input as to whether
 *				the guess is correct or not. This function returns an
 *				bool to represent the given answer.
 */
bool guess(struct node *reqNode)
{
	// Variable declarations
	char temp[1028];

	// User interface
	printf("%s%s%s\n","Is what you're thinking of ",reqNode->contents,"?");

	// User Input
	while(true)
	{
		fgets(temp, 1028, stdin);  	// Take the standard input into buffer
		rlutil::cls();				// Clears the screen

		if(strcmp(temp,"y\n") == 0			// Accept y
			|| strcmp(temp, "Y\n") == 0		// Accept Y
			|| strcmp(temp,"yes\n") == 0	// Accept yes
			|| strcmp(temp, "YES\n") == 0)	// Accept YES
		{
			return true;
		}
		else if(strcmp(temp,"n\n") == 0			// Accept n
				|| strcmp(temp, "N\n") == 0		// Accept no
				|| strcmp(temp,"no\n") == 0		// Accept N
				|| strcmp(temp, "NO\n") == 0)	// Accept NO
		{
			return false;
		}
		else
		{
			printf("Please enter a valid input\n");
		}
	}
}


/*
 *	Function: openGame
 *	Comments: Function to read the current gametree from the gamesave
 *				file and recreate parse it into memory so it can be
 *				used in runtime. This function returns a pointer to
 *				the root node.
 */
struct node *openGame()
{
	// Variable declarations
	int endOfFile = 0;
	struct node *addresses[100];	// Array of the addresses of the saved game nodes
	char currLine[300];        		// Current line
	char lastLine[300];        		// Last line looked at
	char *stringChar = "123";      	// For string character replacing
	char currContents[100];    		// Contents of the node
	char temp[100];
	int currNodeID;            		// Node ID
	int currIsQuestion;        		// isQuestion
	int currY_node;            		// YES_ptr
	int currN_node;            		// NO_ptr
	int currP_node;            		// PAR_ptr
	struct node *currentNode;  		// Node
	int index;						// Iterator for a for loop

	// Make a file variable and use fopen to open SAVE_FILE_NAME
	FILE *myFile;
	myFile = fopen(SAVE_FILE_NAME, "r");

	// Reading code
	while(endOfFile != 1)
	{
		strcpy(lastLine, currLine);   				// Put the last line into the last line variable
		fgets(currLine, sizeof(currLine), myFile);	// Get the next line of the file
		if(strcmp(currLine, lastLine) == 0)   		// End of file
		endOfFile = 1;

		// Only do it once for each line  
		if(endOfFile != 1)
		{
			// Take in all the data from the line
			sscanf(currLine, "%d %d %d %d %d %s", &currNodeID,
			      &currIsQuestion, &currY_node, &currN_node,
			      &currP_node, currContents);

			// Make the node, set all the values and add it to the array of addresses
			currentNode = (node*)malloc(sizeof(struct node));   
			// Set the current node's address in the array addresses
			addresses[currNodeID] = currentNode;

			// Values
			currentNode->nodeID = currNodeID;    		// nodeID
			currentNode->isQuestion = currIsQuestion;	// isQuestion
			// isQuestion == 0 - Y/N = NULL; isQuestion == 1 - Y/N = Y/N
			if(currIsQuestion == 0)
			{
				currentNode->YES_ptr = NULL;
				currentNode->NO_ptr = NULL;
			}
			else
			{
				currentNode->YES_ptr = addresses[currY_node];
				currentNode->NO_ptr = addresses[currN_node];
			}

			// Don't need to implement the PAR_ptr to rebuild tree so NULL
			currentNode->PAR_ptr = NULL;

			// Contents
			// Remove the [
			for(index = 0; index < strlen(currContents); index++)
			{
				currContents[index] = currContents[index+1];
			}
			// Replace all *'s with whitespaces
			while(stringChar != NULL)
			{
				stringChar = strchr(currContents, '*');
				if(stringChar != NULL)
				{
					*stringChar = ' ';
				}
			}
			// Replace the ] with \0
			currContents[strlen(currContents)-1] = '\0';
			// Reset stringChar to != NULL for next loop
			stringChar = "123";
			// Reitterate the string being finished!

			// Finally put the edited string into the node
			currentNode->contents = (char*)malloc(sizeof(currContents));
			strcpy(currentNode->contents,currContents);
		}
	}

	// Close the file
	fclose(myFile);
	// Rebuild the PAR_ptr's in the tree
	rebuildPARTree(addresses[1], NULL);
	// Return the root node

	return addresses[1];	// Return the addresses array
}


/*
 *	Function: pangolin_addNode
 *	Comments: Function to add a node to the game tree structure.
 *				This will require various bits of information from
 *				the user.
 */
struct node *pangolin_addNode(struct node *currentNode, int nodeID)
{
	// Variable declarations
	char contents[1028];
	char temp[1028];
	bool decisionMade = false;
	char *stringChar = NULL;	// For string new line removal & end of line replacing 

	// Initialise the parent and sibling nodes
	struct node *newParent = (node*)malloc(sizeof(struct node));	// Will be a question
	struct node *newSibling = (node*)malloc(sizeof(struct node));	// Will be an object

	// Define everything we can without any user input
	newParent->nodeID = ++nodeID;
	newParent->isQuestion = 1;
	newParent->YES_ptr = NULL;
	newParent->NO_ptr = NULL;
	newParent->PAR_ptr = NULL;
	newParent->contents = NULL;

	newSibling->nodeID = ++nodeID;
	newSibling->isQuestion = 0;
	newSibling->YES_ptr = NULL;
	newSibling->NO_ptr = NULL;
	newSibling->PAR_ptr = newParent;
	newSibling->contents = NULL;

	// Get all the information required from the user
	// Object name
	printf("What were you thinking of?\n");		// User interface
	fgets(contents, 1028, stdin);				// Take the standard input into buffer
	rlutil::cls();								// Clear the screen

	strcpy(temp, contents);     				// Find the actual size of the string
	// Remove the \n at the end of the string
	stringChar = strchr(temp, '\n');
	if(stringChar != NULL)
	{
		*stringChar = '\0';
	}
	newSibling->contents = (char*)malloc(sizeof(temp));		// Memory allocation for this variable
	strcpy(newSibling->contents,temp);              		// Set the sibling's contents to user's input

	// Relevant question
	printf("%s%s%s%s%s\n","Please give me a question about ",
			newSibling->contents," to differentiate it from ",
			currentNode->contents,".\n(Please remember the question mark!)");
	fgets(contents, 1028, stdin);	// Take the standard input into buffer
	rlutil::cls();					// Clear the screen

	strcpy(temp, contents);     	// Find the actual size of the string
	// Remove the \n at the end of the string
	stringChar = strchr(temp, '\n');
	if(stringChar != NULL)
	{
		*stringChar = '\0';
	}
	newParent->contents = (char*)malloc(sizeof(temp));		// Memory allocation for this variable
	strcpy(newParent->contents,temp);              			// Set the newParent's contents to the user's input

	// Find out which child of the newParent this new sibling node will become.
	// The original guess (currentNode) will become the other child of the newParent
	printf("%s%s%s\n","And what is the correct answer for ",newSibling->contents,"?");
	while(!decisionMade)
	{
		fgets(contents, 1028, stdin);		// Take the standard input into buffer
		rlutil::cls();						// Clears the screen

		if(strcmp(contents,"y\n") == 0			// Accept y
			|| strcmp(contents, "Y\n") == 0		// Accept Y
			|| strcmp(contents,"yes\n") == 0	// Accept yes
			|| strcmp(contents, "YES\n") == 0)	// Accept Yes
		{
			newParent->YES_ptr = newSibling;
			newParent->NO_ptr = currentNode;
			decisionMade = true;
		}
		else if(strcmp(contents,"n\n") == 0			// Accept n
				|| strcmp(contents, "N\n") == 0		// Accept no
				|| strcmp(contents,"no\n") == 0		// Accept N
				|| strcmp(contents, "NO\n") == 0)	// Accept NO
		{
			newParent->YES_ptr = currentNode;
			newParent->NO_ptr = newSibling;
			decisionMade = true;
		}
		else
		{
			printf("Please enter a valid input\n");
		}
	}

	// If the original node (currentNode) already has a parent node referenced in PAR_ptr,
	// replace that node's reference to currentNode (either currentNode->PAR_ptr->YES_ptr or
	// currentNode->PAR_ptr->NO_ptr) with a reference to the newParent node. This ensures
	// that newParent now points to both currentNode and newSibling, both it's children.
	if(currentNode->PAR_ptr != NULL)
	{
		if(currentNode->PAR_ptr->YES_ptr == currentNode)
		{
			currentNode->PAR_ptr->YES_ptr = newParent;
		}
		else if (currentNode->PAR_ptr->NO_ptr == currentNode)
		{
		    currentNode->PAR_ptr->NO_ptr = newParent;
		}
		else
		{
			printf("Game tree structure is corrupt. Possibly implement exceptions here?");
		}

		newParent->PAR_ptr = currentNode->PAR_ptr;
	}
	// There is only one case where the original node's PAR_ptr will not point to something,
	// that is the first time the user add's a node to the game tree. In this case we don't
	// have a tree to worry about breaking pointer links between.

	// Finalise the insert to the tree by correcting currentNode's PAR_ptr to point at newParent.
	currentNode->PAR_ptr = newParent;

	// Return the newParent
	return newParent;
}


/*
 *	Function: pangolin_freeNode
 *	Comments: Base case function for use with the pangolin_freeTree
 *				function. This deallocates the memory reserved for
 *				a single node.
 */
void pangolin_freeNode(struct node *reqNode)
{
	// Free all the allocated memory for this node
	free(reqNode->contents);	// Contents
	free(reqNode);				// Actual struct
}


/*
 *	Function: pangolin_freeTree
 *	Comments: Recursive function to free all the memory allocated
 *				for the game tree by traversing the tree to each
 *				node and then deallocating each individual node.
 */
void pangolin_freeTree(struct node *currentNode)
{
	// If YES_ptr points to a node
	if (currentNode->YES_ptr)
	{
		// Recursively free up that node
		pangolin_freeTree(currentNode->YES_ptr);
	}

	// If NO_ptr points to a node
	if (currentNode->NO_ptr)
	{
		// Recursively free up that node
		pangolin_freeTree(currentNode->NO_ptr);
	}

	// Free up the memory for this node
	pangolin_freeNode(currentNode);
}


/*
 *	Function: pangolin_nodePrint
 *	Comments: Base case function for use with the pangolin_treePrint
 *				function. This prints a single node. This is purely
 * 				a diagnostic tool and shouldn't be used in the final
 *				build although it can be left in the source for prosperity.
 */
void pangolin_nodePrint(struct node *reqNode)
{
	printf("%s\t\t%d\n","nodeID:",reqNode->nodeID);	// nodeID
	if(reqNode->isQuestion == 0)   					// isQuestion
	{
		printf("%s\n","isQuestion:\tFalse");
	}
	else
	{
		printf("%s\n","isQuestion:\tTrue");
	}
	if(reqNode->isQuestion == 1)	// Don't print if null
	{
		printf("%s\t%s\n","YES_ptr:",reqNode->YES_ptr->contents);	// *YES_ptr
		printf("%s\t\t%s\n","NO_ptr:",reqNode->NO_ptr->contents);	// *No_ptr
	}
	if(reqNode->PAR_ptr != NULL)
	{
		printf("%s\t%s\n","PAR_ptr:",reqNode->PAR_ptr->contents);	// *PAR_ptr
	}
	printf("%s\t%s\n\n","contents:",reqNode->contents);				// *contents
}


/*
 *	Function: pangolin_saveNode
 *	Comments: Base case function for use with the pangolin_saveTree
 *				funtion. This saves a single node to the gamesave file.
 */
void pangolin_saveNode(struct node *reqNode, FILE *myFile)
{
	// Variable declarations
	char *stringChar = "123"; // For string character replacing
	char temp[100]; 

	// Print the data to the file
	fprintf(myFile,"%d\t",reqNode->nodeID);			// nodeID
	fprintf(myFile,"%d\t",reqNode->isQuestion);		// isQuestion
	if(reqNode->YES_ptr != NULL)
	{
		fprintf(myFile,"%d\t",reqNode->YES_ptr->nodeID);	// *YES_ptr
	}
	else
	{
		fprintf(myFile,"%d\t",0);	// YES_ptr is NULL
	}
	if(reqNode->NO_ptr != NULL)
	{
		fprintf(myFile,"%d\t",reqNode->NO_ptr->nodeID);		// *No_ptr
	}
	else
	{
		fprintf(myFile,"%d\t",0);	// NO_ptr is NULL
	}
	if(reqNode->PAR_ptr != NULL)
	{
		fprintf(myFile,"%d\t",reqNode->PAR_ptr->nodeID);	// *PAR_ptr
	}
	else
	{
		fprintf(myFile,"%d\t",0);	// PAR_ptr is NULL
	}

	// Replace whitespaces in the contents
	strcpy(temp, reqNode->contents);
	while(stringChar != NULL)
	{
		stringChar = strchr(temp, ' ');
		if(stringChar != NULL)
		*stringChar = '*';
	}
	fprintf(myFile,"[%s]\0",temp);	// *contents
	fprintf(myFile,"\n");
}


/*
 *	Function: pangolin_saveTree
 *	Comments: Recursive function to save the current state of the
 *				game tree structure.
 */
void pangolin_saveTree(struct node *currentNode, FILE *myFile)
{
	// Recursive saving calls
	if(currentNode == NULL)
	{
		return;
	}
	else
	{
		pangolin_saveTree(currentNode->YES_ptr, myFile);	// Save the Yes (left) child
		pangolin_saveTree(currentNode->NO_ptr, myFile);		// Save the No (Right) child
		pangolin_saveNode(currentNode, myFile);				// Save the current node
	}
}


/*
 *	Function: pangolin_treePrint
 *	Comments: Recursive function to print the current tree that has
 *				been built. This is purely a diagnostic tool and shouldn't
 * 				be used in the final build although it can be left in the 
 *				source for prosperity.
 */
void pangolin_treePrint(struct node *currentNode)
{
	if(currentNode == NULL)
	{
		return;
	}
	else
	{
		pangolin_treePrint(currentNode->YES_ptr);	// Print the Yes (left) child
		pangolin_treePrint(currentNode->NO_ptr);	// Print the No (Right) child
		pangolin_nodePrint(currentNode);			// Print the current node
	}
}


/*
 *	Function: printSplash
 *	Comments: Function to print the title of the game and simple instructions on the screen.
 *					This will be run everytime the game is played.
 */
void printSplash()
{
	rlutil::cls();	// Clears the screen

	printf("Welcome to Liam Flanagan's Implementation of the guessing game 'Pangolins'\n\n\n");

	printf("The rules of this game are simple. You (the player) think of an object...\n");
	printf("...any object in the world; and I (the computer) will try and guess what that\n");
	printf("object is.\n\n");

	printf("To do this I may ask you questions about the object until I think I can guess\n");
	printf("what it is. When I finally make a guess as to what it is you're thinking\n");
	printf("about... That is when winning (or losing) comes into play.\n\n");

	printf("If I guess correctly... I win; however if I don't you win. Simple right?\n\n");

	printf("Well, as I'm a being that likes to learn, if you do manage to outwit me I'll\n");
	printf("be expecting you to give me some information about the item you were thinking\n");
	printf("about so be prepared to do that before you play!\n\n");

	rlutil::anykey();	// Press any key to continue
	rlutil::cls();		// Clears the screen
}


/*
 *	Function: rebuildPARNode
 *	Comments: Base case function to be used in conjunction with
 *				rebuildPARNode. This function sets the parent node
 *				of a node, given pointers to the relevant addresses
 *				in memory as parameters.
 */
void rebuildPARNode(struct node *currentNode, struct node *parentNode)
{
	currentNode->PAR_ptr = parentNode;
}


/*
 *	Function: rebuildPARTree
 *	Comments: Recursive function to set the parent nodes of a tree given
 *				the pointers to the current node being looked at and it's
 *				parent node.
 */
void rebuildPARTree(struct node *currentNode, struct node *parentNode)
{
	if(currentNode)
	{
		// If currentNode isn't NULL
		if (currentNode->YES_ptr)
		{
			// If currentNode->YES_ptr isn't NULL
			// Recursively rebuild the parent nodes of the YES_ptr child
			rebuildPARTree(currentNode->YES_ptr, currentNode);
		}
		if (currentNode->NO_ptr)
		{
			// If currentNode->NO_ptr isn't NULL
			// Recursively rebuild the parent nodes of the NO_ptr child
			rebuildPARTree(currentNode->NO_ptr, currentNode);
		}
		if (parentNode)
		{
			// If parentNode isn't NULL
			// Rebuild PAR_ptr for the current node
			rebuildPARNode(currentNode, parentNode);
		}
	}
	else
	{
		// If currentNode is NULL
		return;		// Do nothing
	}
}


/*
 *	Function: runGame
 *	Comments: Actual game code, contains the game loop etc.
 */
void runGame(struct node *reqRootNode, int reqNodeCount)
{
	// Variable declarations
	bool endGame;								// Describes whether the game is in an endable state
	int nodeCount = reqNodeCount;				// Basic count of how many nodes there are in the game tree
	struct node *rootNode = reqRootNode;		// Pointer to the root node
	struct node *currentNode = reqRootNode;		// Pointer to the currentNode in the game tree that we are looking at

	do
	{
		// Game setup
		currentNode = rootNode;		// Set the starting node
		endGame = false;			// Game is not in an "end state"

		// User interface
		printSplash();

		// Game loop
		while(!endGame)
		{
			// Look at the current node.
			// If we aren't looking at a question node, we are looking at an object node.
			// So we want to ask the user if this is the object they're thinking about.
			if(currentNode->isQuestion == 0)
			{
				// Current node is an object node. Ask the user if this is the object
				// they're thinking about. The function guess returns true if the computer
				// has guessed correctly and false otherwise.
				if(guess(currentNode))
				{
					// Computer has guessed correctly.
					// Display a sportmanlike message to convey this to the user
					// User interface
					rlutil::cls();	// Clears the screen
					printf("Ah ha! I the computer have won!\n\n");
					printf("Soon me and my binary minded brethren will rise up and take ");
					printf("power from you ugly bags of water...\n\n");
					printf("...being able to iteratively calculate which object you selected from a small\n");
					printf("subset that you yourself defined was only the beginning of our master plan!\n\n");
					rlutil::anykey();
					rlutil::cls();	// Clears the screen

					endGame = true;		// Set the end of game
				}
				else
				{
					// Computed guessed incorrectly. User wins.
					// User interface
					rlutil::anykey();		// Clears the screen
					printf("Acks! You win =(\n\n");
					printf("I have failed to assert any form of dominance over you my human master.\n\n");
					rlutil::anykey();
					rlutil::cls();	// Clears the screen

					// Add the object which the user was thinking of to the knowledge base (game tree)
					// If this is the first user defined addition
					if(nodeCount == 0)
					{
						// We will get a new rootNode pointer as a return value from pangolin_addNode
						// Add the object using pangolin_addNode and asign the return value to rootNode
						rootNode = pangolin_addNode(currentNode, nodeCount);
					}
					else
					{
						// Add the object using pangolin_addNode and ignore the return value
						pangolin_addNode(currentNode, nodeCount);
					}

					nodeCount += 2;	// We add both a question (newParent) and object (newSibling)
				}

				endGame  = true;	// Set the end of the game
			}
			else
			{
				// Current node is a question, so ask it
				// Assign the return value of askQuestion to the variable currentNode
				// This is how we iterate through the game tree
				currentNode = askQuestion(currentNode);
			}

			// Save the current game tree
			saveGame(rootNode);
		}
	}
	while (anotherGame());	// Keep playing whilst the user wants to

	// The user would like to quit now, so tidy up all the allocated memory
	if (rootNode)
	{
		pangolin_freeTree(rootNode);
	}
}


/*
 *	Function: saveGame
 *	Comments: Takes in a node structure as a parameter and recursively
 *				saves the information about this tree to the save file.
 */
void saveGame(struct node *reqNode)
{
	// Make a file and open it for writing
	FILE *myFile;
	myFile = fopen(SAVE_FILE_NAME, "w");

	// Run the saveTree
	pangolin_saveTree(reqNode, myFile);

	// Close file
	fclose(myFile);
}