#pragma once
#include <functional>
#include <map>
#include "../interface.h"
#include <memory>
/*
Интерфейсы взаимодействия с системой игровой карты (MAP).
*/

namespace map {
	class MAP
	{
	public:
		virtual bool IsEmpty(PositionCoord coord) = 0; //Necessary for tank moving
		virtual void EnumerateWallObjects(std::function<void(PositionCoord, std::shared_ptr<class WallOblect>)> fun) = 0;
		virtual void EnumeratePlayerObjects(std::function<void(PositionCoord, std::shared_ptr<class Player>)> fun) = 0;
		virtual void EnumerateBulletObjects(std::function<void(PositionCoord, std::shared_ptr<class Bullet>)> fun) = 0;
	};
	
	class MapExample:public MAP
	{
		int sizex, sizey;
		std::map<int, std::map<int, std::shared_ptr<class WallOblect> > > Wall;
		std::map<int, std::map<int, std::shared_ptr<class Player> > > Players;
		std::map<int, std::map<int, std::shared_ptr<class Bullet> > > Bullets;

	public:

		virtual bool IsEmpty(PositionCoord coord)
		{
			auto finded = Wall.find(coord.x);
			if (finded == Wall.end())return true;
			auto findedy = finded->second.find(coord.y);
			if (findedy == finded->second.end())return true;
			return false;		
		}

		virtual void EnumerateWallObjects(std::function<void(PositionCoord, std::shared_ptr<class WallOblect>) > fun)
		{
			for (auto& xi : Wall)
				for (auto&yi : xi.second)fun(PositionCoord(xi.first, yi.first), yi.second);
		}

		virtual void EnumeratePlayerObjects(std::function<void(PositionCoord, std::shared_ptr<class Player>) > fun)
		{
			throw std::logic_error("The method or operation is not implemented.");
		}

		virtual void EnumerateBulletObjects(std::function<void(PositionCoord, std::shared_ptr<class Bullet>) > fun)
		{
			throw std::logic_error("The method or operation is not implemented.");
		}

	};
};
