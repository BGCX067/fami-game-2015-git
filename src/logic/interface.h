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
    class Logic {
    private:
        std::string gameStatus; //текущий статус игры
        std::queue commandsFromGUI; //очередь gui комманд

        std::string getNextCommandFromGUI(); //мы забираем команду из gui
        setCommandForPlayer(); //дать комманду игроку
        void updateMap(); //обновить карту после изменений

    public:
        void run(); //запуск логики, должна запускать gui
        std::string getStatusForGUI(); //gui отдаем статус игры
    };
	
}
