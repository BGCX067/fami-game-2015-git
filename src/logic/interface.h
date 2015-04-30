#pragma once

#include <string>
#include <queue>
#include "../map/interface.h"
using namespace std;
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
    Logic(shared_ptr<tmap::TMap> map);

    LOGICCommand getStatusForGUI();                                 // Передача gui статуса игры
    void setNextCommandFromGUI(CommandFromGUI g_commandFromGUI);    // Передача команд gui
    void run();                                                     // Запуск логики по таймеру
private:
    LOGICCommand _gameStatus;                                       // Текущий статус игры
    queue<CommandFromGUI> _commandsFromGUI;                         // Очередь gui комманд
    shared_ptr<tmap::TMap> _currentMap;
};

}
