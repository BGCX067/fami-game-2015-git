#include "general_types.h"


/*Базовый класс*/
Command::Command() {
	player_number = 0;
}

Command::Command(t_player_number s_player_number) {
	setPlayerNumber(s_player_number);
}

void Command::setPlayerNumber(t_player_number s_player_number) {
	player_number = s_player_number;
}

t_player_number Command::getPlayerNumber() {
	return player_number;
}



/*Команда с направлением */
CommandWithDirection::CommandWithDirection() : 
	Command() {
	command_direction = Direction::Forward;
}

CommandWithDirection::CommandWithDirection(t_player_number s_player_number, Direction s_command_direction) :
	Command(s_player_number) {
	setCommandDirection(s_command_direction);
}

void CommandWithDirection::setCommandDirection(Direction s_command_direction) {
	command_direction = s_command_direction;
}

Direction CommandWithDirection::getCommandDirection() {
	return command_direction;
}