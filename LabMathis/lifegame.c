/*
 * lifegame.c
 *
 *  Created on: 25 october 2022
 *      Author: MAthis Esmiller and Rémi Teyssier
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>



#include "lifegame.h"

/* hard-coded world size */
#define WORLDWIDTH 39
#define WORLDHEIGHT 20

/* character representations of cell states */
#define CHAR_ALIVE '*'
#define CHAR_DEAD ' '

/* current cell states of the world */
static int world[WORLDWIDTH][WORLDHEIGHT];

/* next generation cell states */
static int nextstates[WORLDWIDTH][WORLDHEIGHT];



void initialize_world_from_file(const char * filename) {
	
	FILE* ptr ;
	
	int i =0 ; //for the n char of a line
	int j =0 ;//for the n line of a file
	
	char cell =0;


	ptr= fopen(filename, "r"); 
	//We initialize the world with only dead cell
	for (int a = 0; a < WORLDWIDTH; a++)
	{
		for (int b = 0; b < WORLDHEIGHT; b++)
		{
			world[a][b] = nextstates[a][b] = DEAD;
		}
	}


 	for(j=0;j< WORLDHEIGHT;j++)
	{// we parcours each line of the file 
			while(fread(&cell,1,1, ptr))
			{ //we parcours each character of a line
				if (i == 39  || cell =='\n' ) 
				{
					break;
				}
				else
				{
					
					if(cell==CHAR_ALIVE)
					{
						world[i][j]=ALIVE ;
					}
					else
					{
						world[i][j]=DEAD ;
					}
						i++;
				}
					
				
			}
			//when we reach the end of the line we go on the next line  and reset the i counter 
			i=0;
	}

	fclose(ptr);


}

void save_world_to_file(const char * filename) {
	/* TODO: write the state of the world into a file with
	   name "filename". Assume the file can be created, or if
	   the file exists, overwrite the file. The ith character
	   of the jth line (zero-indexed) describes world[i][j]
	   using the characters CHAR_ALIVE and CHAR_DEAD

	   This file should be readable using the function
	   initialize_world_from_file(filename) above; we can use
	   it to resume a game later
	 */

	FILE* fh ;
	int x , y ;
	int cell_state ;


	fh = fopen(filename,"w+");
	if(fh ==NULL) //if the file is not open we end the programm
	{
		printf("error opening the file");
		abort();
		
	}
	
		for (x = 0; x < WORLDHEIGHT; x++) // we parcour the 2d array to know the state of each cell and put it in the file at the same position
		{
			for (y = 0; y < WORLDWIDTH; y++) 
			{
				cell_state = world[y][x] ;
				if(cell_state ==ALIVE )
				{ 
					fputc(CHAR_ALIVE,fh);
				}
				else if(cell_state==DEAD)
				{
					fputc(CHAR_DEAD,fh);
				}
			
			}
		fputc('\n',fh);
		}
 		  fclose(fh);
	
}

/* you shouldn't need to edit anything below this line */

/* initializes the world to a hard-coded pattern, and resets
   all the cells in the next generation to DEAD */
void initialize_world(void) {
	int i, j;
	
	for (i = 0; i < WORLDWIDTH; i++)
	{
		for (j = 0; j < WORLDHEIGHT; j++)
		{
			world[i][j] = nextstates[i][j] = DEAD;
		}
	}
				/* pattern "glider" */
				world[1][2] = ALIVE;
				world[3][1] = ALIVE;
				world[3][2] = ALIVE;
				world[3][3] = ALIVE;
				world[2][3] = ALIVE;
	
	output_world();

}

int is_World_Empty(void) {
	for (int i = 0; i < WORLDWIDTH; i++)
		for (int j = 0; j < WORLDHEIGHT; j++)
			if (world[i][j] == ALIVE) return 0;
	return 1;
}

int get_world_width(void) {
	return WORLDWIDTH;
}

int get_world_height(void) {
	return WORLDHEIGHT;
}

int get_cell_state(int x, int y) {
	if (x < 0 || x >= WORLDWIDTH || y < 0 || y >= WORLDHEIGHT)
		return DEAD;
	return world[x][y];
}

void set_cell_state(int x, int y, int state) {
	if (x < 0 || x >= WORLDWIDTH || y < 0 || y >= WORLDHEIGHT) {
		fprintf(stderr,"Error: coordinates (%d,%d) are invalid.\n", x, y);
		abort();
	}
	nextstates[x][y] = state;
}

void finalize_evolution(void) {
	int x, y;
	for (x = 0; x < WORLDWIDTH; x++) {
		for (y = 0; y < WORLDHEIGHT; y++) {
			world[x][y] = nextstates[x][y];
			nextstates[x][y] = DEAD;
		}
	}
}

void output_world(void) {
	
	char worldstr[2*WORLDWIDTH+2];
	int i, j;

	worldstr[2*WORLDWIDTH+1] = '\0';
	worldstr[0] = '+';
	for (i = 1; i < 2*WORLDWIDTH; i++)
		worldstr[i] = '-';
	worldstr[2*WORLDWIDTH] = '+';
	puts(worldstr);
	for (i = 0; i <= 2*WORLDWIDTH; i+=2)
		worldstr[i] = '|';
	for (i = 0; i < WORLDHEIGHT; i++) {
		for (j = 0; j < WORLDWIDTH; j++)
			worldstr[2*j+1] = world[j][i] == ALIVE ? CHAR_ALIVE : CHAR_DEAD;
		puts(worldstr);
	}
	worldstr[0] = '+';
	for (i = 1; i < 2*WORLDWIDTH; i++)
		worldstr[i] = '-';
	worldstr[2*WORLDWIDTH] = '+';
	puts(worldstr);

		
}


