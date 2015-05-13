#ifndef LOGIC_INTERFACE_H
#define LOGIC_INTERFACE_H

#include <string>
#include <queue>
#include <mutex>
#include "../map/interface.h"

using namespace std;

// Интерфейсы взаимодействия с системой игровой логики (LOGIC).

namespace logic
{
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
    shared_ptr<tmap::TMap> _currentMap;                             // Ссылка на глобальную карту

    mutex _logicRun;
};

}

#endif // LOGIC_INTERFACE_H

