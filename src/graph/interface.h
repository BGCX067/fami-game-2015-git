#pragma once

#include "../interface.h"

/*
Интерфейсы взаимодействия с системой графики (GRAPH).
*/

namespace graph {
	class graphicManager {
        virtual void init(_map::MAP *mapObject)=0; // Присваивает карту для отрисовки виджету.
        virtual void free()=0; // Освобождает занятую память
        virtual void render()=0; // Рендерит 1 кадр.
    };
};
