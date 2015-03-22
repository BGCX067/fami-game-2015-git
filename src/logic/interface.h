#pragma once

#include "../interface.h"
#include <string.h>
#include <queue>

/*
Интерфейсы взаимодействия с системой игровой логики (LOGIC).
*/
//Авторы(сначала руководитель, следом вся команда в алфавитном порядке по фамилии):
//Виктор Сарычев
//Михаил Александров
//Сергей Вайцель
//Пётр Жигалов
//Светлана Трофимова

namespace logic {
  class Logic 
  {
  public:
    Logic();
    ~Logic();

    string getStatusForGUI(); //gui отдаем статус игры
    void getNextCommandFromGUI(CommandFromGUI g_commandFromGUI); //мы забираем команду из gui
    void run(); //запуск логики, должна запускать gui    
  private:
    string _gameStatus; //текущий статус игры
    queue<CommandFromGUI> _commandsFromGUI; //очередь gui комманд

    void setCommandForPlayer(); //дать комманду игроку
    void updateMap(); //обновить карту после изменений
  };
	
}
