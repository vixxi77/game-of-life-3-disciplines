#include <SDL2/SDL.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

const int cell_size = 25;
const int rows = SCREEN_HEIGHT/cell_size;
const int columns = SCREEN_WIDTH/cell_size;

int main(void){
	SDL_Window *window;
	SDL_Event event;
	SDL_Renderer *renderer;

	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("Convoys Game Of Life SDL", SDL_WINDOWPOS_CENTERED ,SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,SCREEN_HEIGHT,0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	SDL_Rect rectangle;
	
	int curr_pos_x = 0;
	int curr_pos_y = 0;

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	int running = 1;
	while(running){
		while(SDL_PollEvent(&event)){  
			switch(event.type){
				case SDL_QUIT:
					running = 0;
					break;
			}
		}		

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		for(int y = 0; y < rows; y++){
			for(int x = 0; x < columns; x++){
				rectangle.x = curr_pos_x;
				rectangle.y = curr_pos_y;
				rectangle.w = cell_size - 1;
				rectangle.h = cell_size - 1;
				SDL_RenderFillRect(renderer, &rectangle);
				curr_pos_x += cell_size;
			}
			curr_pos_y += cell_size;
			curr_pos_x = 0;
		}	

		SDL_RenderPresent(renderer);
		SDL_Delay(16);
	}
	SDL_Quit();
	return 0;
}



