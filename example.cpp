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
