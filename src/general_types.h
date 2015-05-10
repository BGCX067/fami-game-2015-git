#pragma once

#define DEFAULT_CONFIG_MAP "../conf/map.json"

/*
Описание типов, общих для нескольких подсистем
*/

#include <map>

/*Номер игрока*/
typedef unsigned int t_player_number;
typedef unsigned int player_type;
typedef unsigned int bullet_type;

/*Очки жизни игрока*/
typedef int hit_points;

struct PLAYER_TYPE_STRUCT {
    unsigned int tank_size;
    hit_points default_hp;
    unsigned int velocity;
    bullet_type bullet_type_id;
};

struct BULLET_TYPE_STRUCT {
    hit_points damage;
    unsigned int damage_size;
    unsigned int velocity;
};

/* Положение на карте */
struct PositionCoord {
    int x;
    int y;

    //Конструктор
    PositionCoord() {};
    PositionCoord(int X, int Y) {
        x = X;
        y = Y;
    }

    PositionCoord(const PositionCoord & f) {
        x = f.x;
        y = f.y;
    }

    bool operator == (const PositionCoord & t) const {
        return x == t.x && y == t.y;
    }

    PositionCoord & operator = (const PositionCoord & other) {
        if(this != & other)
        {
            this->x = other.x;
            this->y = other.y;
        }
        return *this;
    }
};

/*Направление движения/стельбы*/
enum class Direction {Left, Right, Up, Down};

// Команды, которые приходят от GUI в логику.
enum class GUICommand {Left, Right, Up, Down, Atack, START, PAUSE, CONTINUE, STOP, ABOUT};
// Команды, которые приходят от логики в GUI.
enum class LOGICCommand {GAME_CONTINUE, GAME_OVER, PLAYER_1_WIN, PLAYER_2_WIN};

class Wall {
    int type;
public:
    Wall(int type) : type(type) {};
    ~Wall() {};
    int getType() {return this->type;}
};

class CommandFromGUI
{
public:
    CommandFromGUI();
    ~CommandFromGUI();

    void setPlayerNumber(t_player_number s_player_number);
    void setFromGUICommand(GUICommand s_gui_command);

    t_player_number getPlayerNumber();
    GUICommand getGUICommand();
private:
    t_player_number _playerNumber;
    GUICommand _guiCommand;
};
