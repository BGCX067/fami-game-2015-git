#pragma once

#include "..\interface.h"

/*
Интерфейсы взаимодействия с системой игровой карты (MAP).
*/

namespace map {
	class MAP
	{
	public:
		virtual bool IsEmpty(PositionCoord coord) = 0; //Necessary for tank moving
	};
	
	
};