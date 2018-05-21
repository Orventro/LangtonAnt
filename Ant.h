#include <memory>
#include <string>

using namespace std;

class Ant{
    char dir, colors;
    int width, height, x, y;
    shared_ptr<bool[]> cmd;

    //Strict - if Ant is out of field - error
    //Open - if Ant is out of field - returning to field on opposite side
    enum EdgeMode {Strict, Open};
    EdgeMode mode = Open;

public:
    shared_ptr<char[]> field;
    bool ok = true;

    Ant(int field_width, int field_height, char colors_num, bool *commands);
    Ant(int field_width, int field_height, int startX, int startY, char colors_num, bool *commands, char fill_color, char start_direction);

    ~Ant();

    bool move();
    bool move(int num);

    /*
    int get_width();
    int get_height();
    int get_posX();
    int get_posY();
    char get_direction(); // 0 - up, 1 - right, 2 - down, 3 - left
    */

};

bool *str_to_cmd(string str);
