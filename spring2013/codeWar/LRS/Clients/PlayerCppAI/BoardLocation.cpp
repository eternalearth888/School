#include <cstdlib>
#include <iostream>
#include <sstream>
#include "BoardLocation.h"

using std::cout;
using std::endl;

using MapSquareProperty::str;

namespace PlayerCSharpAI
{
	namespace api
	{
		BoardLocation::BoardLocation()
		{
			m_dir = MapSquareProperty::D_EAST;
			m_mapPos = Point();
		}

		BoardLocation::BoardLocation(const BoardLocation& b)
		{
			m_dir = b.m_dir;
			m_mapPos = b.m_mapPos;
		}

		BoardLocation::BoardLocation(Point mapPosition, MapSquareProperty::DIRECTION direction)
		{
			m_mapPos = mapPosition;
			m_dir = direction;
		}

		BoardLocation::BoardLocation(const xml_node& element)
		{
			m_mapPos = Point(std::atoi(element.attribute("x").value()), std::atoi(element.attribute("y").value()));
			m_dir = MapSquareProperty::parseDirection(element.attribute("direction").value());
		}

		void BoardLocation::makeAttributes(xml_node& parent)
		{
			parent.append_attribute("direction").set_value(str(m_dir).c_str());
			parent.append_attribute("x").set_value(m_mapPos.X);
			parent.append_attribute("y").set_value(m_mapPos.Y);
		}

		Point BoardLocation::getMapPosition() const
		{
			return m_mapPos;
		}

		void BoardLocation::setMapPosition(Point value)
		{
			m_mapPos = value;
		}

		MapSquareProperty::DIRECTION BoardLocation::getDirection() const
		{
			return m_dir;
		}

		void BoardLocation::setDirection(MapSquareProperty::DIRECTION value)
		{
			m_dir = value;
		}

		PlayerCSharpAI::api::BoardLocation* BoardLocation::Move(int num) const
		{
			switch (m_dir)
			{
				case MapSquareProperty::D_NORTH:
					return new BoardLocation(Point(m_mapPos.X, m_mapPos.Y - num), m_dir);
				case MapSquareProperty::D_SOUTH:
					return new BoardLocation(Point(m_mapPos.X, m_mapPos.Y + num), m_dir);
				case MapSquareProperty::D_EAST:
					return new BoardLocation(Point(m_mapPos.X + num, m_mapPos.Y), m_dir);
				case MapSquareProperty::D_WEST:
					return new BoardLocation(Point(m_mapPos.X - num, m_mapPos.Y), m_dir);
			}
			return new BoardLocation(m_mapPos, m_dir);
		}

		PlayerCSharpAI::api::BoardLocation* BoardLocation::Rotate(int num) const
		{
			int dir = static_cast<int>(m_dir) + num;
			while (dir < 0)
				dir += 4;
			while (dir >= 4)
				dir -= 4;
			return new BoardLocation(m_mapPos, static_cast<MapSquareProperty::DIRECTION>(dir));
		}

		bool BoardLocation::operator==(const BoardLocation& loc) const
		{
			return m_dir == loc.m_dir && m_mapPos == loc.m_mapPos;
		}

		std::string BoardLocation::toStr() const
		{
			std::stringstream out;
			out << getMapPosition().toStr() << " - " << getDirection();
			return  out.str();
		}
	}
}
