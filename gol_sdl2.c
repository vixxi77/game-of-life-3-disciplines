#include <SDL2/SDL.h>

int main(void){
	SDL_Window *window;
	SDL_Event event;
	SDL_Renderer *renderer;

	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("Convoys Game Of Life SDL",500,500, 800,800,0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	int running = 1;
	while(running){
		while(SDL_PollEvent(&event)){  
			switch(event.type){
				case SDL_QUIT:
					running = 0;
					break;
			}
		}		
		SDL_RenderClear(renderer);
		SDL_Delay(16);
	}
	return 0;
}



