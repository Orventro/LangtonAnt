#include "Ant.h"

Ant::Ant(int field_width, int field_height, char colors_num, bool *commands){
    width = field_width;
    x = width/2;
    height = field_height;
    y = height/2;
    colors = colors_num;
    cmd = shared_ptr<bool[]>(commands);
    field = shared_ptr<char[]>(new char[width*height]);
}

Ant::Ant(int field_width, int field_height, int startX, int startY, char colors_num, bool *commands, char fill_color, char start_direction){
    width = field_width;
    x = startX;
    height = field_height;
    y = startY;
    colors = colors_num;
    cmd = shared_ptr<bool[]>(commands);
    field = shared_ptr<char[]>(new char[width*height]);
    for(int i = 0; i < width*height; i++) field[i] = fill_color;
    dir = start_direction;
}

Ant::~Ant(){};

bool Ant::move(){
    int addr = y*width + x;
    if(cmd[field[addr]]) dir = (dir+1)%4;
    else                 dir = (dir==0 ? 3 : dir-1);
    if     (dir == 0) y--;
    else if(dir == 1) x++;
    else if(dir == 2) y++;
    else if(dir == 3) x--;
    if(y<0 | y>=height | x<0 | x>=width){
        if(mode == Strict){
            if     (dir == 0) y++;
            else if(dir == 1) x--;
            else if(dir == 2) y--;
            else if(dir == 3) x++;
            if(cmd[field[addr]]) dir = (dir==0 ? 3 : dir-1);
            else                 dir = (dir+1)%4;
            return 0;
        } else if(mode == Open){
            if(y<0)            y = height-1;
            else if(y>=height) y = 0;
            if(x<0)            x = width-1;
            else if(x>=width)  x = 0;
        }
    }
    field[addr] = (field[addr]+1) % colors;
    return 1;
}

bool Ant::move(int num){
    while(num-- && move()) ;
    return ok;
}

bool* str_to_cmd(string str){
    bool *cmd = new bool[str.size()];
    for(int i = 0; i < str.size(); i++) {
        if(str[i] == '1' |
           str[i] == 'R' |
           str[i] == 'r' |
           str[i] == '>') cmd[i] = true;
        else cmd[i] = false;
    }
    return cmd;
}
