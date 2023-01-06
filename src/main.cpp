#include "SDL2/SDL.h"
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>
using namespace std;
int p = 0;
class Particle{
  int x, y;
  SDL_Rect rect;
  vector<int> v;
  int speed = 15;
  public:
  Particle(){
    srand(time(NULL) + p);
    x = rand() % 995;
    y = rand() % 995;
    p += rand();
    v.push_back(rand() % speed);
    v.push_back(sqrt(speed * speed - v[0] * v[0]));
    rect = {x, y, 5, 5};
  }
  void Render(SDL_Renderer* rend){
    SDL_SetRenderDrawColor(rend, 0x20, 0x20, 255, 255);
    SDL_RenderFillRect(rend, &rect);
    SDL_RenderPresent(rend);
  }
  void Move(){
    for (int i = 0; i < 2; i++)
    {
      rect.x += v[0];
      rect.y += v[1];
    }
    if (rect.x <= 0 || rect.y <= 0 || rect.x >= 995 || rect.y >= 995)
    {
      v[0] = -(v[0] / 1);
      v[1] = -(v[1] / 1);
    }
  }
};
int main(int argc, char* argv[]){
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		return 0;
	}
  SDL_Window* w = SDL_CreateWindow("physics2d", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,1000, 1000, 0);
	SDL_Renderer* rend = SDL_CreateRenderer(w, -1, SDL_RENDERER_ACCELERATED);
	SDL_Event event;
  char running = 1;
  Particle part[320];
  for(int i = 0; i < 320; i++) part[i] = Particle();
  while(running)
  {
    SDL_SetRenderDrawColor(rend, 0x20, 0x20, 0x20, 255); //render
    SDL_RenderClear(rend);
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT) running = 0;
    for (int i = 0; i < 320; i++)
    {
      part[i].Render(rend);
      part[i].Move();
    }
    //SDL_Delay(1000 / 165);
  }
  SDL_Quit();
  return 0;
}
