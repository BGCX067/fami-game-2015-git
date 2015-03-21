#pragma once

/*
�������� �����, ����� ��� ���������� ���������
*/


/*����� ������*/
typedef unsigned int t_player_number;

/*���� ����� ������*/
 typedef unsigned int hit_points;

/* ��������� �� ����� */
struct PositionCoord {
	int x;
	int y;

	//�����������
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
