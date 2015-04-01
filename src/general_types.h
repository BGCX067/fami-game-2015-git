#pragma once

/*
�������� �����, ����� ��� ���������� ���������
*/


/*����� ������*/
typedef unsigned int t_player_number;

/*���� ����� ������*/
 typedef int hit_points;

/* ��������� �� ����� */
struct PositionCoord {
	int x;
	int y;

	//�����������
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

/*����������� ��������/�������*/
enum class Direction {Left, Right, Up, Down};
// �������, ������� �������� �� GUI � ������. 
enum class GUICommand {Left, Right, Up, Down, Atack}; 

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
class CommandMove : public Command {


};

/*������� ��������*/
class CommandTurn : public CommandWithDirection {


};

/*������� ����� */
class CommandAttack : public Command {

};

/*������� �� GUI*/
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