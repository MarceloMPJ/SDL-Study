#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_keyboard.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

void pintaFundo(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
	SDL_RenderClear(renderer);
}

void pintaRetanguloNaTela(int blocoEixoX, int blocoEixoY, SDL_Renderer* renderer) {
	SDL_Rect retangulo;
	
	retangulo.x = blocoEixoX;
	retangulo.y = blocoEixoY;
	
	retangulo.w = 8;
	retangulo.h = 8;

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(renderer, &retangulo);
}

void controleDoQuadrado(SDL_Renderer* renderer, SDL_Window* window) {
	int blocoEixoX = 0;
	int blocoEixoY = 0;

	SDL_Event evento;
	
	while(true) {
		SDL_GetKeyboardState(NULL);
		SDL_PollEvent(&evento);
	
		if(evento.type == SDL_KEYDOWN) {
			switch(evento.key.keysym.sym) {
				case SDLK_w:
				case SDLK_KP_8:
					blocoEixoY -= 3;
					break;
				
				case SDLK_x:
				case SDLK_KP_2:
					blocoEixoY += 3;
					break;

				case SDLK_a:
				case SDLK_KP_4:
					blocoEixoX -= 3;
					break;

				case SDLK_d:
				case SDLK_KP_6:
					blocoEixoX += 3;
					break;

				case SDLK_s:
				case SDLK_KP_5:
					pintaFundo(renderer);
					break;
				case SDLK_ESCAPE:
					SDL_DestroyWindow(window);
					SDL_Quit();
					return;
			}
		}

		pintaRetanguloNaTela(blocoEixoX, blocoEixoY, renderer);

		SDL_RenderPresent(renderer);

		SDL_GetKeyboardState(NULL);
	}
}

int main(int argc, char* args[]) {
	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;

	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL não pode iniciar! Error: %s\n", SDL_GetError());
	}

	window = SDL_CreateWindow
	(
		"SDL Tutorial",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN
	);
		
	if(window == NULL) {
		printf("A janela não pode ser criada! Error: %s\n", SDL_GetError());
		return -1;
	}

	SDL_Renderer* renderer = NULL;	
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);	

	pintaFundo(renderer);
	pintaRetanguloNaTela(0, 0, renderer);
	SDL_RenderPresent(renderer);

	controleDoQuadrado(renderer, window);

	return 0;
}