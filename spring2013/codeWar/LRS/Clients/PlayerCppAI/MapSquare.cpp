#include <cstdlib>
#include "MapSquare.h"

namespace PlayerCSharpAI
{
	namespace api
	{
		MapSquare::MapSquare() : m_walls(NULL), m_conveyor(NULL), m_laser(NULL)
		{

		}

		MapSquare::MapSquare(const xml_node& element)
		{
			m_type = MapSquareProperty::parseType(element.attribute("type").value());
			m_walls = MapSquareProperty::parseSide(element.attribute("walls").value());
			m_flag = element.attribute("flag").as_int();

			xml_node elemConveyor = element.child("conveyor");
			m_conveyor = elemConveyor ? new Conveyor(elemConveyor) : NULL;

			xml_node elemLaser = element.child("laser");
			m_laser = elemLaser ? new Laser(elemLaser) : NULL;
		}

		MapSquare::MapSquare(const MapSquare& m)
		{
			m_type = m.m_type;
			if (m.m_walls != NULL)
				m_walls = new vector<MapSquareProperty::SIDE>(*m.m_walls);
			else
				m_walls = NULL;
			m_flag = m.m_flag;
			if (m.m_conveyor != NULL)
				m_conveyor = new Conveyor(*m.m_conveyor);
			else
				m_conveyor = NULL;
			if (m.m_laser != NULL)
				m_laser = new Laser(*m.m_laser);
			else
				m_laser = NULL;
		}

		MapSquare::~MapSquare()
		{
			delete m_walls;
			delete m_conveyor;
			delete m_laser;
		}

		MapSquareProperty::TYPE MapSquare::getType()
		{
			return m_type;
		}

		/*void MapSquare::setType(MapSquareProperty::TYPE value)
		{
			m_type = value;
		}*/

		vector<MapSquareProperty::SIDE>* MapSquare::getWalls()
		{
			return m_walls;
		}

		/*void MapSquare::setWalls(vector<MapSquareProperty::SIDE> value)
		{
			m_walls = value;
		}*/

		PlayerCSharpAI::api::Conveyor* MapSquare::getConveyor()
		{
			return m_conveyor;
		}

		/*void MapSquare::setConveyor(Conveyor* value)
		{
			m_conveyor = value;
		}*/

		PlayerCSharpAI::api::Laser* MapSquare::getLaser()
		{
			return m_laser;
		}

		/*void MapSquare::setLaser(Laser* value)
		{
			m_laser = value;
		}*/

		int MapSquare::getFlag()
		{
			return m_flag;
		}

		/*void MapSquare::setFlag(int value)
		{
			m_flag = value;
		}*/

		MapSquare& MapSquare::operator=(const MapSquare& m)
		{
			delete m_walls;
			delete m_conveyor;
			delete m_laser;

			m_type = m.m_type;
			if (m.m_walls != NULL)
				m_walls = new vector<MapSquareProperty::SIDE>(*m.m_walls);
			else
				m_walls = NULL;
			m_flag = m.m_flag;
			if (m.m_conveyor != NULL)
				m_conveyor = new Conveyor(*m.m_conveyor);
			else
				m_conveyor = NULL;
			if (m.m_laser != NULL)
				m_laser = new Laser(*m.m_laser);
			else
				m_laser = NULL;

			return *this;
		}
	}
}
