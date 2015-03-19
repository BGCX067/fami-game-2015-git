#pragma once

/*
Описание типов, общих для нескольких подсистем
*/

/*Отчки жизни игрока*/
 typedef unsigned int t_player_number;

/*Номер игрока*/
typedef unsigned int t_player_number;

/* Положение на карте */
struct PositionCoord { 		 
	int x; 		 
	int y; 		 
};

/*Направление движения/стельбы*/
enum class Direction {Left, Right, Forward, Backward};

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
class CommandMove : public CommandWithDirection {


};

/*Команда атаки */
class CommandAttack : public Command {

};