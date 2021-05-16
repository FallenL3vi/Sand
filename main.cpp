#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <tuple>

using namespace std;

const short width = 20;
const short height = 20;

struct Vector2
{
    short x = 0;
    short y = 0;
};

struct Entity
{
    bool active = false;
    Vector2 pos;
};

void print(bool map[][height])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            //nie uzywac jak interesuje memory layout, bo jest wolniejsze
            cout << (map[j][i] ? "*" : " ");
            /*if(map[j][i] == true)
            {
                cout<< "*";
            }
            else
            {
                cout<< ".";
            }*/
        }
        cout<<endl;
    }
    Sleep(50);
    system("CLS");
}



int main()
{
    bool map[width][height] = {false};
    Vector2 spawn_p;
    spawn_p.x = 10;
    spawn_p.y = 0;

    short b_count = 200;
    Entity blocks[b_count];

    for(int i = 0; i < 600; i++)
    {
        for(int j = 0; j < b_count; j++)
        {
            Vector2 new_pos = blocks[j].pos;
            if(!map[spawn_p.x][spawn_p.y] && !blocks[j].active)
            {
                map[spawn_p.x][spawn_p.y] = true;
                blocks[j].active = true;
                blocks[j].pos = spawn_p;
                new_pos = spawn_p;
                continue;
            }
            else if(map[blocks[j].pos.x][blocks[j].pos.y+1] != true)
            {
                //cout <<"1"<<endl;
                new_pos.y++;
            }
            else if(!map[blocks[j].pos.x-1][blocks[j].pos.y+1])
            {
                //cout <<"2"<<endl;
                new_pos.x--;
                new_pos.y++;
            }
            else if(!map[blocks[j].pos.x+1][blocks[j].pos.y+1])
            {
                //cout <<"3"<<endl;
                new_pos.x++;
                new_pos.y++;
            }
            /*else if(!map[blocks[j].pos.x+1][blocks[j].pos.y])
            {
                new_pos.x++;
            }
            else if(!map[blocks[j].pos.x-1][blocks[j].pos.y])
            {
                new_pos.x--;
            }*/
            if(new_pos.x >= width || new_pos.y >= height || new_pos.x < 0 || new_pos.y < 0)
            {
                continue;
            }
            else if(blocks[j].active)
            {
                map[blocks[j].pos.x][blocks[j].pos.y] = false;
                map[new_pos.x][new_pos.y] = true;
                blocks[j].pos = new_pos;
                //cout<<"cycle"<<endl;
            }
        }
        print(map);
    }
    return 0;
}
