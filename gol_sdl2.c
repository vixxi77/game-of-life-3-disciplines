#include <SDL2/SDL.h>
#include <stdio.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

typedef struct{
	SDL_Rect rectangle;
	SDL_Color color;
}Cell;

const int cell_size = 25;
const int rows = SCREEN_HEIGHT/cell_size;
const int columns = SCREEN_WIDTH/cell_size;

int main(void){
	SDL_Window *window;
	SDL_Event event;
	SDL_Renderer *renderer;
	int mouse_x;
	int mouse_y;
	Cell cell[rows][columns];

	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("Convoys Game Of Life SDL", SDL_WINDOWPOS_CENTERED ,SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,SCREEN_HEIGHT,0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	SDL_Rect rectangle;
	
	int curr_pos_x = 0;
	int curr_pos_y = 0;

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	/*
	for(int y = 0; y < rows; y++){
		for(int x = 0; x < columns; x++){
			rectangle.x = curr_pos_x;
			rectangle.y = curr_pos_y;
			rectangle.w = cell_size - 1;
			rectangle.h = cell_size - 1;
			SDL_RenderFillRect(renderer, &rectangle);
			curr_pos_x += cell_size;
			if(y < 1){
				printf("Rectangle %d, at position x: %d y: %d \n", x, rectangle.x, rectangle.y);
			}
		}
		curr_pos_y += cell_size;
		curr_pos_x = 0;
	}	
	*/
	for(int y = 0; y < rows; y++){
		for(int x = 0; x < columns; x++){
			cell[x][y].rectangle = (SDL_Rect) {x * cell_size, y * cell_size, cell_size - 1, cell_size - 1};
			SDL_RenderFillRect(renderer, &cell[x][y].rectangle);
			cell[x][y].color = (SDL_Color) {0, 0, 0, 255};
		}
	}	

	int running = 1;
	while(running){
		while(SDL_PollEvent(&event)){  
			switch(event.type){
				case SDL_QUIT:
					running = 0;
					break;
			}
		}		
		SDL_GetMouseState(&mouse_x, &mouse_y);
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderFillRect(renderer, &cell[mouse_x/cell_size][mouse_y/cell_size].rectangle);

		
		printf("\rCell at position COLUMN: %d ROW: %d ", mouse_x/cell_size, mouse_y/cell_size);
		fflush(stdout);
		SDL_RenderPresent(renderer);
		SDL_Delay(16);
	}
	SDL_Quit();
	return 0;
}



