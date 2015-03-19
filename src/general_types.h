#pragma once

/*
�������� �����, ����� ��� ���������� ���������
*/


/*����� ������*/
typedef unsigned int t_player_number;

/*����� ����� ������*/
 typedef unsigned int hit_points;

/* ��������� �� ����� */
struct PositionCoord { 		 
	int x; 		 
	int y; 		 
};

/*����������� ��������/�������*/
enum class Direction {Left, Right, Up, Down};

// ========================================================================
// ======================== ������ ������ =================================
// ========================================================================

/*������� �����*/
class Command {
 public:
	 //������������
	 Command();
	 Command(t_player_number s_player_number);

	 //Set-�������
	 void setPlayerNumber(t_player_number s_player_number);

	 //Get-�������
	 t_player_number getPlayerNumber();

 private:
	 t_player_number player_number;

};

/*������� � ������������ */
class CommandWithDirection : public Command {
 public:
	 //������������
	 CommandWithDirection();
	 CommandWithDirection(t_player_number s_player_number, Direction s_command_direction);

	 //Set-�������
	 void setCommandDirection(Direction s_command_direction);

	//Get-�������
	 Direction getCommandDirection();

 private:
	 Direction command_direction;
};


/*������� �������� */
class CommandMove : public CommandWithDirection {


};

/*������� ����� */
class CommandAttack : public Command {

};