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
enum class GUICommand {Left, Right, Up, Down, Atack}; 

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
	 //Конструкторы
	 CommandWithDirection();
	 CommandWithDirection(t_player_number s_player_number, Direction s_command_direction);

	 //Set-функции
	 void setCommandDirection(Direction s_command_direction);

	//Get-функции
	 Direction getCommandDirection();

 private:
	 Direction command_direction;
};


/*Команда движения */
class CommandMove : public Command {


};

/*Команда поворота*/
class CommandTurn : public CommandWithDirection {


};

/*Команда атаки */
class CommandAttack : public Command {

};

/*Команды от GUI*/
class CommandFromGUI
{
public:
  CommandFromGUI();
  ~CommandFromGUI();

  //Set-Function
  void setPlayerNumber(t_player_number s_player_number);
  void setFromGUICommand(GUICommand s_gui_command);

  //Get-Function
  t_player_number getPlayerNumber();
  GUICommand getGUICommand();
private:
  t_player_number _playerNumber;
  GUICommand _guiCommand;
};