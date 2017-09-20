#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_keyboard.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* window = NULL;

int min(int a, int b) { return (a <= b) ? a : b; }

int pow2(int x) { return x*x; }

Uint32* getPixel(SDL_Surface* surface, int x, int y) {
  return ((Uint32 *) surface->pixels + y * surface->w + x);
}

void linhaDDA(SDL_Surface* surface, int xi, int yi, int xf, int yf, int corR, int corG, int corB) {
  int dx = xf - xi, dy = yf - yi, etapas;
  float incX, incY, x = xi, y = yi;

  etapas = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);

  incX = dx/(float) etapas;
  incY = dy/(float) etapas;

  Uint32* pixel = getPixel(surface, x, y);
  *(pixel) = SDL_MapRGB(surface->format, corR, corG, corB);

  for(int i = 0; i < etapas; i++) {
    x += incX;
    y += incY;

    pixel = getPixel(surface, x, y);
    *(pixel) = SDL_MapRGB(surface->format, corR, corG, corB);
  }
}

void circBrasenham(SDL_Surface* surface, int xc, int yc, int r, int corR, int corG, int corB) {
  int x = 0;
  int y = -r;

  int RR = pow2(r);

  int cont = 0;

  while(x < r) {
    // Pinta o pixel
    Uint32* pixel1 = getPixel(surface, xc-x, yc+y);
    Uint32* pixel2 = getPixel(surface, xc+x, yc-y-1);
    Uint32* pixel3 = getPixel(surface, xc+x, yc+y);
    Uint32* pixel4 = getPixel(surface, xc-x, yc-y-1);

    *(pixel1) = SDL_MapRGB(surface->format, corR, corG, corB);
    *(pixel2) = SDL_MapRGB(surface->format, corR, corG, corB);
    *(pixel3) = SDL_MapRGB(surface->format, corR, corG, corB);
    *(pixel4) = SDL_MapRGB(surface->format, corR, corG, corB);

    int mh = pow2(x+1) + pow2(y) - RR; 
    int md = pow2(x+1) + pow2(y+1) - RR;
    int mv = pow2(x) + pow2(y+1) - RR;
     
    // B
    if(md == 0) {
      x = x+1;
      y = y+1;
    }

    if(md < 0) {
      int omega = mh - md;

      // A
      if(omega > 0) {
        x = x+1;
        continue;
      }

      // B
      x = x+1;
      y = y+1;
    }

    if(md > 0) {
      int omega = md - mv;

      // B
      if(omega <= 0) {
        x = x+1;
        y = y+1;
        continue;
      }

      // C      
      y = y+1;
    }
  }
}

void desenhaLinha(SDL_Surface* surface, int corR, int corG, int corB) {
  int xi, yi, xf,yf;

  xi = rand()%SCREEN_WIDTH;
  yi = rand()%SCREEN_HEIGHT;
  xf = rand()%SCREEN_WIDTH;
  yf = rand()%SCREEN_HEIGHT;

  linhaDDA(surface, xi, yi, xf, yf, corR, corG, corB);
}

void desenhaCirculo(SDL_Surface* surface, int corR, int corG, int corB) {
  int xc, yc, r;

  xc = rand()%SCREEN_WIDTH;
  yc = rand()%SCREEN_HEIGHT;
  r = rand()%200;

  circBrasenham(surface, xc, yc, r, corR, corG, corB);
}

void desenhaLinhaOuCirculo(SDL_Surface* surface) {
  int i = 0;
  for(; i < 50; i++) {
    int escolheLinha = rand()%2;
    
    int corR = rand()%(0xFF+1);
    int corG = rand()%(0xFF+1);
    int corB = rand()%(0xFF+1);
    
    if(escolheLinha) {
      desenhaLinha(surface, corR, corG, corB);
    } else {
      desenhaCirculo(surface, corR, corG, corB);
    }

    SDL_UpdateWindowSurface(window);
    SDL_Delay(200);  
  }
}

static int aguardaSair(void *ptr) {
  SDL_Event evento;

  while(true) {
    SDL_GetKeyboardState(NULL);
    SDL_PollEvent(&evento);
    
    if(evento.type == SDL_KEYDOWN) {
      if(evento.key.keysym.sym == SDLK_ESCAPE) {
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(0);
      } 
    }
  }
}

int main(int argc, char* args[]) {
	SDL_Surface* windowSurface = NULL;

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
  
  windowSurface = SDL_GetWindowSurface(window);

  SDL_FillRect(windowSurface, NULL, SDL_MapRGB(windowSurface->format, 0x00, 0x00, 0x00));

  srand(time(NULL));

  SDL_CreateThread(aguardaSair, "aguardaSair", (void *)NULL);
  desenhaLinhaOuCirculo(windowSurface);

  SDL_Delay(200); 

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
