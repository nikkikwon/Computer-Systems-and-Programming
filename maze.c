#include <stdio.h>
#include "maze.h"
/* Introduction:
 * This program contains various subroutines/ functions that help organize and solve the maze given. 
 * It contains function that finds the starting point specified the input file, a function to print 
 * the maze, function that solves maze, then a function that checks whether the maze solution is a 
 * valid one. 
*/

/*
 * Introduction: This function looks at every location then locate x,y coordinates of 
 * where 'S'=start is located then store those values in the mem reserved. 
 *
 * findStart -- finds the x and y location of the start of the  maze
 * INPUTS:      maze -- 2D char array that holds the contents of the maze
 *              width -- width of the maze
 *              height -- height of the maze
 *              x -- pointer to where x location should be stored
 *              y -- pointer to where y location should be stored
 * OUTPUTS: x and y will hold the values of the start
 * RETURN: none
 * SIDE EFFECTS: none
 */ 
void findStart(char ** maze, int width, int height, int * x, int * y)
{
    int row, col;
    // first assume no start is present 
    *x=-1;
    *y=-1; 

    //loop every row and column to see where the start'S' is located.
    for (row=0; row < height; row++)
    {
        for(col=0; col < width; col++)
        {
	    if (maze[row][col]=='S')
   	    {
	        *x=col;
	 	*y=row;
	    }
	}
    }	
    return;
}

/*
 * Introduction: This function prints maze in the same format given by the test samples.
 * It prints every rows and columns and every row is followed by a newline. 
 * 
 * printMaze -- prints out the maze in a human readable format (should look like examples)
 * INPUTS:      maze -- 2D char array that holds the contents of the maze 
 *              width -- width of the maze
 *              height -- height of the maze
 * OUTPUTS:     none
 * RETURN:      none
 * SIDE EFFECTS: prints the maze to the console
 */
void printMaze(char ** maze, int width, int height)
{
    int row, col;

    //print the maze for every rows and columns, with newline after each row
    for (row=0; row < height; row++)
    {
	for (col=0; col < width; col++)
	{
	    printf("%c", maze[row][col]);	
	}
    printf("\n");
    }
}

/*
 * Introduction:
 * This function solves Maze given with DFS algorithm. 
 * By using recursion, it checks the base case(detecting 'E') first then examine for all possibilities with 
 * some adjustments to the x, y values.
 * 
 * solveMazeDFS -- recursively solves the maze using depth first search
 * INPUTS:         maze -- 2D char array that holds the contents of the maze
 *                 width -- the width of the maze
 *                 height -- the height of the maze
 *                 xPos -- the current x position within the maze
 *                 yPos -- the current y position within the maze
 * OUTPUTS:        updates maze with the solution path ('.') and visited nodes ('~')
 * RETURNS:        0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:   none
 */ 
int solveMazeDFS(char ** maze, int width, int height, int xPos, int yPos)
{
    
    // if (x,y) outside of boundary, return 0
    if ( xPos < 0 || xPos > (width-1) || yPos < 0 || yPos > (height-1) )
        return 0;
  
    // if (x,y) is at the end of maze return true
    if (maze[yPos][xPos] == 'E')
        return 1;

    // if (x,y) is not an empty cell, return 0.
    if (maze[yPos][xPos]=='~' || maze[yPos][xPos]== '.' || maze[yPos][xPos]== '%')
        return 0;
   
    //set (x,y) as part of solution path in the maze
    if (maze[yPos][xPos] != 'S')
    {
	maze[yPos][xPos]='.';	
    }

        //left
    	if (solveMazeDFS(maze, width, height, xPos-1, yPos)==1 ){
       	    return 1;
	}

    	//right
        if (solveMazeDFS(maze, width, height, xPos+1, yPos)==1 ){
            return 1;
	}

    	//up
    	if (solveMazeDFS(maze, width, height, xPos, yPos-1)==1 ){
            return 1;
	}

    	//down
    	if (solveMazeDFS(maze, width, height, xPos, yPos+1)==1 ){
            return 1;
	}

    //unmark (x,y) then mark as visited return false
    if (maze[yPos][xPos] != 'S')
    maze[yPos][xPos]='~';	
         
    
      return 0;
}

/*
 * Introduction: 
 * This function checks whether the given solution is valid or not starting from the given 
 * starting position. Valid solution shouldn't reach to deadend or take a detour which 
 * leads this function to return 0. Otherwise function will return 1 indicating 
 * valid solution from the solve function. 
 * 
 * checkMaze -- checks if a maze has a valid solution or not
 * INPUTS:      maze -- 2D char array that holds the contents of the maze
 *              width -- width of the maze
 *              height -- height of the maze
 *              x -- the starting x position in the maze
 *              y -- the starting y position in the maze
 * OUTPUTS:     none
 * RETURN:      1 if the maze has a valid solution, otherwise 0
 * SIDE EFFECTS: none
 */ 
int checkMaze(char ** maze, int width, int height, int x, int y)
{
    //Start chcking from the starting coordinates
    int path;
    for (; y<height; y++)
    {
    	for(; x<width; x++)
 	{
	    path=0;
	    //Check all the surrounding locations
	    if ( maze[y][x] == '.' )
	    {
		if ( maze[y][x-1]=='.' )
	            path++;
		if ( maze[y][x+1] == '.' )
		    path++;
		if ( maze[y-1][x] == '.' )
		    path++;
		if ( maze[y+1][x] == '.' )
		    path++;
                //not a valid solution if there's more than 2 path
		if (path >2)
		    return 0;
	    }
	}	
    }           
    return 1;

}

/*
 * solveMazeBFS -- solves the maze using a breadth first search algorithm
 * INPUTS:         maze -- A 2D array that contains the contents of the maze
 *                 width -- the width of the maze
 *                 height -- the height of the maze
 *                 xPos -- the starting x position within the maze
 *                 yPos -- the starting y position within the maze
 * OUTPUTS:        none
 * RETURNS:        0 if the maze is unsolvable, else 1
 * SIDE EFFECTS:   marks the cells within the maze as visited or part of the solution path
 */
int solveMazeBFS(char ** maze, int width, int height, int xPos, int yPos)
{
  

    return 0;
}

/*
 * enqueue -- enqueues an integer onto the given queue
 * INPUTS:    queue -- a pointer to the array that will hold the contents of the queue
 *            value -- the value to  enqueue
 *            head -- a pointer to a variable that contains the head index in the queue
 *            tail -- a pointer to a variable that contains the tail index in the queue
 *            maxSize -- the maximum size of the queue (size of the array)
 * OUTPUTS:   none
 * RETURNS:   none
 * SIDE EFFECTS: adds an item to the queue
 */ 
void enqueue(int * queue, int value, int * head, int * tail, int maxSize)
{
    if ((*tail - maxSize) == *head)
    {
        printf("Queue is full\n");
        return;
    }
    *tail = *tail + 1;
    queue[*tail % maxSize] = value;
}

/* dequeue -- dequeues an item from the given queue
 * INPUTS:    queue -- a pointer to the array that holds the contents of the queue
 *            head -- a pointer to a variable that contains the head index in the queue
 *            tail -- a pointer to a variable that contains the tail index in the queue
 *            maxSize -- the maximum size of the queue (size of the array)
 * OUTPUTS:   none
 * RETURNS:   the value dequeued from the queue
 * SIDE EFFECTS: removes an item from the queue
 */
int dequeue(int * queue, int * head, int * tail, int maxSize)
{
    if (*head == *tail)
    {
        printf("Queue is empty\n");
        return -1;
    }
    *head = *head + 1;
    return queue[*head % maxSize];
}

