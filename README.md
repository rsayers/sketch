# sketch
A simple library for coding graphics. Heavily influenced by Processing. In extremely early development.

Written by a Pythonista just learning c++, i'm sure it shows.

Example:
```c++
#include "sketch.h"

class Example : public Sketch {
    public:
        double ball_x, ball_y, radius, dx, dy;

        Example(int w, int h): Sketch(w, h){ }

        void setup(){
            ball_x = width/2.0;
            ball_y = height/2.0;
            dx = 0.3;
            dy = 0.5;
            radius = 75;
        }
        
        void draw(){
            for (int y = 0; y < height; ++y)
            {
                for (int x = 0; x < width; ++x)
                {
                    set(x, y, x % 255, y % 255, (x+y) % 255);
                }
            }
            line(0, 0, width, height, 0, 0, 0);
            fcircle(ball_x, ball_y, radius, 255, 0, 0);
            if (ball_x-radius < 0 || ball_x+radius > width) dx = -dx;
            if (ball_y-radius < 0 || ball_y+radius > height) dy = -dy;
            ball_x += dx;
            ball_y += dy;
        }
};


int main()
{
   Example ex (640, 480);
   ex.run();
}
```
Which produces:
![screenshot](/screenshot.png)

Currently you can:
* set(x, y, r, g, b) - Sets pixel
* circle(x, y, radius, r, g, b) - Draw an empty circle
* fcircle(x, y, radius, r, g, b) - Draw a filled circle
* line(x1, y1, x2, y2, r, g, b) - Draws a line

Do you setup in `setup()`, and do your drawing in `draw()` which will be called once per frame.