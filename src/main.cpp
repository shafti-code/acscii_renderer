#include <ncurses.h>
#include <cmath>
#include <unistd.h>
#include <clocale>
#include <vector>
double width {}, height {};
struct Vector2d {
    double x;
    double y;
    Vector2d screen();
};

struct Vector3d {
    double x;
    double y;
    double z;
    Vector2d project(){
        return {
            this->x/this->z,
            this->y/this->z
        };
    }
    Vector3d rotate_xz(double angle);
    Vector3d translate_z(double z);
};

Vector2d Vector2d::screen(){
        return {
            (this->x + 1.0) / 2.0 * width/2,
            (1 - (this->y + 1.0) / 2.0) * height
        };
}


Vector3d Vector3d::rotate_xz(double angle){
    double c = cos(angle);
    double s = sin(angle);
    return {
        this->z*s + this->x*c,
        this->y,
        this->z*c - this->x*s,
    };
};

Vector3d Vector3d::translate_z(double z){
    return{
        this->x,
        this->y,
        this->z + z,
    };
}

double angle{};
void draw(std::vector<Vector3d> vertisies){
    Vector2d vec2;
    for(int i{};i < vertisies.size();i++){
        vec2 = vertisies.at(i).rotate_xz(angle).translate_z(4).project();
        vec2 = vec2.screen();
        mvaddch(vec2.y,vec2.x,'o');
    }
};

int main(){
    setlocale(LC_ALL,"");
    initscr();
    const double FPS = 60.0;
    std::vector<Vector3d> vertisies{
        {-0.25,0.25,0.25},
        {0.25,0.25,0.25},
        {0.25,-0.25,0.25},
        {-0.25,-0.25,0.25},

        {-0.25,0.25,-0.25},
        {0.25,0.25,-0.25},
        {0.25,-0.25,-0.25},
        {-0.25,-0.25,-0.25}
    };
    getmaxyx(stdscr,height,width);
    height--;
    while(true){
        refresh();
        clear();
        angle += 1* M_PI * 1/FPS;
        getmaxyx(stdscr,height,width);
        height--;
        width--;
        draw(vertisies);
        move(height,width);
        usleep(1e6/FPS);

    }
    getch();
    endwin();
}
