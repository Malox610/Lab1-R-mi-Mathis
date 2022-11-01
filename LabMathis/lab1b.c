/*
 * lab1b.c
 *
 *  Created on:
 *      Author: 
 */

/* include helper functions for game */
#include "lifegame.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


/* add whatever other includes here */

/* number of generations to evolve the world */
#define NUM_GENERATIONS 50

/* functions to implement -- can copy from Part A */

/* this function should set the state of all
   the cells in the next generation and call
   finalize_evolution() to update the current
   state of the world to the next generation */
void next_generation(void);

/* this function should return the state of the cell
   at (x,y) in the next generation, according to the
   rules of Conway's Game of Life (see handout) */
int get_next_state(int x, int y);

/* this function should calculate the number of alive
   neighbors of the cell at (x,y) */
int num_neighbors(int x, int y);

int main(int argc, char ** argv)
{
	int n;

	/* TODO: initialize the world, from file argv[1]
	   if command line argument provided (argc > 1), or
	   using hard-coded pattern (use Part A) otherwise */

initialize_world_from_file("glider.txt");


	for (n = 0; n < NUM_GENERATIONS; n++)
	{
		next_generation();
		
		/* TODO (optional): Visualise world in each generation */
     	
		system("clear");
		output_world();
		sleep(1);
	}	

	/* TODO: output final world state to console and save
	   world to file "world.txt" in current directory */

	output_world();
	return 0;
}

void next_generation(void) {
/* TODO: for every cell, set the state in the next
	   generation according to the Game of Life rules

	   Hint: use get_next_state(x,y) and set_next_state(x,y) */
	   int nextstate ;
		for(int i =0 ; i <= WORLDWIDTH-1 ; i++)
		{ 
		   for(int j=0 ; j <= WORLDHEIGHT-1; j++)
		    {  
					nextstate = get_next_state(i,j);
				
					set_cell_state(i,j,nextstate);
		    }
		}

	finalize_evolution(); /* called at end to finalize */
}

int get_next_state(int x, int y) {
	int nextstate=1;
	
	/* TODO: for the specified cell, compute the state in
	   the next generation using the rules

	   Use num_neighbors(x,y) to compute the number of live
	   neighbors */
       int neighbors =0 ;
	   
	    neighbors = num_neighbors(x,y);
		
	   int state =get_cell_state(x,y);

     
	   if(neighbors<2 && state == ALIVE )
	   {
		nextstate=DEAD ;
		
	   }
	     else if(neighbors>3 && state == ALIVE )
	   {
		nextstate=DEAD ;
		
	   }

  		else if((neighbors==3 || neighbors==2 ) && state == ALIVE )
	   {
		nextstate=ALIVE;
		
	   }
    	else if(neighbors==3 && state == DEAD )
	   {
		nextstate=ALIVE ;
		
	   }
	else
		{
			nextstate=DEAD ;
			
		}

	   return nextstate;
}

int num_neighbors(int x, int y) {
/* TODO: for the specified cell, return the number of
	   neighbors that are ALIVE

	   Use get_cell_state(x,y) */
	   int neighbors =0; 

	   for (int i = x-1 ; i<=x+1 ; i++)
	   {
     	   for (int j = y-1 ; j<=y+1 ; j++)
	  		{
			
				if(i==x && j==y)
				{
					
				}else{
					int neighbor_cell_state = get_cell_state(i,j);
					if( neighbor_cell_state == ALIVE)
					{
						neighbors++; 
						
					}
				}
	  		}
	   }
	 
	   return neighbors;

}
