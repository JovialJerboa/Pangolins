/***************************************************************************\
	pangolins.h

	Header file for 
		Liam Flanagan's implementation of the Pangolins guessing game

 	Author: Liam Flanagan. liamflan@gmail.com
 	Version 3.0, 30-Mar-2010
\***************************************************************************/


// Struct definitions
struct node
{
	int nodeID;            // Should always be initialised
	int isQuestion;        // Should always be initialised (0=false, 1=true)
	struct node *YES_ptr;  // May be NULL
	struct node *NO_ptr;   // May be NULL
	struct node *PAR_ptr;  // May be NULL
	char *contents;        // May be blank
};


// Function prototypes
/*
 *	Function: anotherGame
 *	Comments: Function the ask the user if they would like to play another
 *				game. This function will take in user input to represent
 *				this and return it as a.
 */
bool anotherGame();
/*
 *	Function: askQuestion
 *	Comments: Function to ask the question stored within a given node.
 *				The node is represented by a pointer given as a parameter.
 *				During the life cycle of this function the user is
 *				required to give input to represent the answer to the
 *				question.
 */
struct node *askQuestion(struct node *reqNode);
/*
 *	Function: beginGame
 *	Comments: Function to do all the inital setup that is required
 *				before the game loop can be run and then run the
 *				question. Dependant on the answer this function will
 *				return one of left or right hand child of the gametree.
 */
void beginGame();
/*
 *	Function: buildInitialTree
 *	Comments: Function to build the initial gametree. This will only be
 *				run if a gamesave file cannot be opened.
 */
struct node *buildInitialTree();
/*
 *	Function: countSavedNodes
 *	Comments: Function to count the number of nodes present in the
 *				gamesave file. Each node is represented by a single
 *				line in the textfile.
 */
int countSavedNodes();
/*
 *	Function: guess
 *	Comments: This function takes a pointer to a node structure as
 *				a paremeter and displays this as a computed guess to
 *				the user via a basic UI. During the life cycle of this
 *				function the user is required to give input as to whether
 *				the guess is correct or not. This function returns an
 *				bool to represent the given answer.
 */
bool guess(struct node *reqNode);
/*
 *	Function: openGame
 *	Comments: Function to read the current gametree from the gamesave
 *				file and recreate parse it into memory so it can be
 *				used in runtime. This function returns a pointer to
 *				the root node.
 */
struct node *openGame();
/*
 *	Function: pangolin_addNode
 *	Comments: Function to add a node to the game tree structure.
 *				This will require various bits of information from
 *				the user.
 */
struct node *pangolin_addNode(struct node *currentNode, int nodeID);
/*
 *	Function: pangolin_freeNode
 *	Comments: Base case function for use with the pangolin_freeTree
 *				function. This deallocates the memory reserved for
 *				a single node.
 */
void pangolin_freeNode(struct node *reqNode);
/*
 *	Function: pangolin_freeTree
 *	Comments: Recursive function to free all the memory allocated
 *				for the game tree by traversing the tree to each
 *				node and then deallocating each individual node.
 */
void pangolin_freeTree(struct node *currentNode);
/*
 *	Function: pangolin_nodePrint
 *	Comments: Base case function for use with the pangolin_treePrint
 *				function. This prints a single node. This is purely
 * 				a diagnostic tool and shouldn't be used in the final
 *				build although it can be left in the source for prosperity.
 */
void pangolin_nodePrint(struct node *reqNode);
/*
 *	Function: pangolin_saveNode
 *	Comments: Base case function for use with the pangolin_saveTree
 *				funtion. This saves a single node to the gamesave file.
 */
void pangolin_saveNode(struct node *reqNode, FILE *myFile);
/*
 *	Function: pangolin_saveTree
 *	Comments: Recursive function to save the current state of the
 *				game tree structure.
 */
void pangolin_saveTree(struct node *currentNode, FILE *myFile);
/*
 *	Function: pangolin_treePrint
 *	Comments: Recursive function to print the current tree that has
 *				been built. This is purely a diagnostic tool and shouldn't
 * 				be used in the final build although it can be left in the 
 *				source for prosperity.
 */
void pangolin_treePrint(struct node *currentNode);
/*
 *	Function: printSplash
 *	Comments: Function to print the title of the game and simple instructions on the screen.
 *					This will be run everytime the game is played.
 */
void printSplash();
/*
 *	Function: rebuildPARNode
 *	Comments: Base case function to be used in conjunction with
 *				rebuildPARNode. This function sets the parent node
 *				of a node, given pointers to the relevant addresses
 *				in memory as parameters.
 */
void rebuildPARNode(struct node *currentNode, struct node *parentNode);
/*
 *	Function: rebuildPARTree
 *	Comments: Recursive function to set the parent nodes of a tree given
 *				the pointers to the current node being looked at and it's
 *				parent node.
 */
void rebuildPARTree(struct node *currentNode, struct node *parentNode);
/*
 *	Function: runGame
 *	Comments: Actual game code, contains the game loop etc.
 */
void runGame(struct node *reqRootNode, int reqNodeCount);
/*
 *	Function: saveGame
 *	Comments: Takes in a node structure as a parameter and recursively
 *				saves the information about this tree to the save file.
 */
void saveGame(struct node *reqNode);