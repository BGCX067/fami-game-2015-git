#pragma once

/*
Описание типов, общих для нескольких подсистем
*/


/*Номер игрока*/
typedef unsigned int t_player_number;

/*Очки жизни игрока*/
 typedef int hit_points;

/* Положение на карте */
struct PositionCoord {
    int x;
    int y;

    //Конструктор
    PositionCoord(){};
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
enum class GUICommand {Left, Right, Up, Down, Atack, START, PAUSE, CONTINUE, EXIT, ABOUT};

class Wall {
public:
    Wall() {};
    ~Wall() {};
};

class Player {
public:
    Player() {};
    ~Player() {};
};

class Bullet {
public:
    Bullet() {};
    ~Bullet() {};
};

// ========================================================================
// ======================== Классы команд =================================
// ========================================================================

/*Базовый класс*/
class Command {
 public:
     //Конструкторы
     Command();
     Command(t_player_number s_player_number);

     //Set-функции
     void setPlayerNumber(t_player_number s_player_number);

     //Get-функции
     t_player_number getPlayerNumber();

 private:
   t_player_number player_number;
};

/*Команда с направлением */
class CommandWithDirection : public Command {
 public:
     CommandWithDirection();
     CommandWithDirection(t_player_number s_player_number, Direction s_command_direction);

     void setCommandDirection(Direction s_command_direction);
     Direction getCommandDirection();

 private:
     Direction command_direction;
};


class CommandMove : public Command {


};

class CommandTurn : public CommandWithDirection {


};

class CommandAttack : public Command {

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
