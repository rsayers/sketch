#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>
#include <iostream>
using namespace std;

#define PI 3.14159265
#define TWO_PI PI * 2
#define ROUND_2_INT(f) ((int)(f >= 0.0 ? (f + 0.5) : (f - 0.5)))

class Color
{
public:
    int r, g, b;
};

inline int f2i( double d )
{
   union Cast
   {
      double d;
      long l;
    };
   volatile Cast c;
   c.d = d + 6755399441055744.0;
   return c.l;
}

class Sketch
{
public:
    int width, height;
    unsigned int *pixels;
    SDL_Surface *window_surface;
    SDL_Window *window;
    SDL_Event event;

    Sketch(int w, int h)
    {
        SDL_Init(SDL_INIT_VIDEO);
        window = SDL_CreateWindow(
            "",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            w,
            h,
            SDL_WINDOW_RESIZABLE);
        set_props();
    }

    void set_props()
    {
        window_surface = SDL_GetWindowSurface(window);
        pixels = (unsigned int *)window_surface->pixels;
        width = window_surface->w;
        height = window_surface->h;
    }

    void run()
    {
        setup();

        while (1)
        {
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                    exit(0);
                if (event.type == SDL_WINDOWEVENT)
                {
                    if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                    {
                        set_props();
                    }
                }
                if (event.type == SDL_KEYDOWN){
                    cout << "Key press\n";
                }
            }

           draw();

           SDL_UpdateWindowSurface(window);
        }
    }

    virtual void setup()
    {
    }

    virtual void draw()
    {
        
    }

    void set(double x, double y, int r, int g, int b)
    {
        set(f2i(x), f2i(y), r, g, b);
    }

    void set(int x, int y, int r, int g, int b)
    {
        if (x < 0 || x > width || y < 0 || y > height) return;
        pixels[x + y * width] = SDL_MapRGBA(window_surface->format, r, g, b, 255);
    }

    int get(int x, int y)
    {
        return pixels[x + y * width];
    }

    void line(int x1, int y1, int x2, int y2, int r, int b, int g){
        int dx = x2 - x1;
        int dy = y2 - y1;
        
        double step = min((double)dx/(double)dy, 1.0);
        
        for (double x = x1; x < x2; x+=step){
            double y = y1 + dy * (x - x1) / dx;
            set(x, y, r, g, b);
        }
    }

    void circle(int x, int y, int radius, int r, int g, int b){
        double step = 0.5/radius;
        for (double a = 0; a < TWO_PI; a+=step){
            set(
                x + f2i(cos(a) * radius),
                y + f2i(sin(a) * radius),
                r, g, b
            );
        }
    }

    void fcircle(int x, int y, int radius, int r, int g, int b){
        for(int i=0; i<radius; i++){
            circle(x, y, i, r, g, b);
        }
    }
};