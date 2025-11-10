#include <SDL2/SDL.h>
#include <stdio.h>
#include <time.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

typedef struct{
	SDL_Rect rectangle;
	int isAlive;
}Cell;

const int cell_size = 16;
const int rows = SCREEN_HEIGHT/cell_size;
const int columns = SCREEN_WIDTH/cell_size;
SDL_Window *window;
SDL_Event event;
SDL_Renderer *renderer;


/*
int generate_view(void (*gen)(struct Cell _cell[columns][rows])){
	(*gen)();
	return 0;
}
*/

int main(int argc, char *argv[]){
	int mouse_x;
	int mouse_y;
	double time_per_frame = 0;
	int fps = 0;
	int STATE_PAUSED = 1;
	int mouse_down = 0;
	int running = 1;
	int alive_counter = 0;
	int pause_toggle = 1;
	int grid_lines = 0;
	Cell cell[rows][columns];
	Cell next_cell[rows][columns];

	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("Convoys Game Of Life SDL", SDL_WINDOWPOS_CENTERED ,SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,SCREEN_HEIGHT,0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	SDL_Rect rectangle;
	
	int curr_pos_x = 0;
	int curr_pos_y = 0;

	
	if(argc > 1 && strcmp(argv[1], "-grid") == 0)
		grid_lines = 1;

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	for(int y = 0; y < rows; y++){
		for(int x = 0; x < columns; x++){
			cell[x][y].rectangle = (SDL_Rect) {x * cell_size, y * cell_size,
				 grid_lines?cell_size - 1:cell_size ,grid_lines?cell_size - 1:cell_size};
			SDL_RenderFillRect(renderer, &cell[x][y].rectangle);
			cell[x][y].isAlive = 0;
		}
	}	

	
	while(running){
		clock_t start = clock();

		SDL_GetMouseState(&mouse_x, &mouse_y);
		while(SDL_PollEvent(&event)){  
			switch(event.type){
				case SDL_QUIT:
					running = 0;
					break;
				case SDL_MOUSEBUTTONDOWN:
					mouse_down = 1;
					printf("down, %d", mouse_down);
					break;
				case SDL_MOUSEBUTTONUP:
					mouse_down = 0;
					printf("release, %d", mouse_down);
					break;
				case SDL_KEYDOWN:
					switch(event.key.keysym.scancode){
						case SDL_SCANCODE_SPACE:
							if(pause_toggle){
								STATE_PAUSED = 0;	
								pause_toggle = 0;
							}else{
								STATE_PAUSED = 1;
								pause_toggle = 1;
							}
							
					}
			}
		}		



		if(STATE_PAUSED && mouse_down){
			cell[mouse_x/cell_size][mouse_y/cell_size].isAlive = 1;
		}


		if(!STATE_PAUSED){
			for(int y = 0; y < rows; y++){
				for(int x = 0; x < columns; x++){
					//thats ugly 
					//TODO: clean that shi up
					if(x > 0 && cell[x-1][y].isAlive){
						alive_counter++;
					} 
					if(x < columns - 1 && cell[x+1][y].isAlive){
						alive_counter++;
					}
					if(y > 0 && cell[x][y-1].isAlive){
						alive_counter++;
					}
					if(y < rows - 1 && cell[x][y+1].isAlive){
						alive_counter++;
					}
					if(y < rows -1 && x < columns -1 && cell[x+1][y+1].isAlive){
						alive_counter++;
					}
					if(x > 0 && y > 0 && cell[x-1][y-1].isAlive){
						alive_counter++;
					}
					if(y > 0 && x < columns - 1 && cell[x+1][y-1].isAlive){
						alive_counter++;
					}
					if(y < rows - 1 && x > 0 && cell[x-1][y+1].isAlive){
						alive_counter++;
					}

					if(cell[x][y].isAlive && alive_counter < 2){
						next_cell[x][y].isAlive = 0;
					}else if(cell[x][y].isAlive && alive_counter == 2 || alive_counter == 3){
						next_cell[x][y].isAlive = 1;
					}else if(cell[x][y].isAlive && alive_counter > 3){
						next_cell[x][y].isAlive = 0;
					}else if(!cell[x][y].isAlive && alive_counter == 3){
						next_cell[x][y].isAlive = 1;
					}
					alive_counter = 0;
				}
			}	

			for(int y = 0; y < rows; y++){
				for(int x = 0; x < columns; x++){
					cell[x][y].isAlive = next_cell[x][y].isAlive;
				}
			}

				
		}

		for(int y = 0; y < rows; y++){
			for(int x = 0; x < columns; x++){
				if(cell[x][y].isAlive){
					SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
					SDL_RenderFillRect(renderer, &cell[x][y].rectangle);
				}else if(!cell[x][y].isAlive){
					SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
					SDL_RenderFillRect(renderer, &cell[x][y].rectangle);
				} 
			}
		}	


//		printf("\rCell at position COLUMN: %d ROW: %d ", mouse_x/cell_size, mouse_y/cell_size);
		SDL_RenderPresent(renderer);

		time_t end = clock();
		time_per_frame = (double)(end - start) / CLOCKS_PER_SEC;
		fps = (int)(60 / time_per_frame);
		printf("\rMS: %f FPS: %d ", time_per_frame, fps);
		fflush(stdout);

		if(STATE_PAUSED){
			SDL_Delay(16);
		}else
			SDL_Delay(200);
	}
	SDL_Quit();
	return 0;
}

