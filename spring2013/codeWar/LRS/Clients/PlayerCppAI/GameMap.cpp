#include <cstdlib>
#include <string>
#include <sstream>
#include "GameMap.h"

using std::string;
using std::stringstream;

namespace PlayerCSharpAI
{
	namespace api
	{

		GameMap::GameMap(const xml_node& element) : m_flags(NULL)
		{
			int width = element.attribute("width").as_int();
			int height = element.attribute("height").as_int();
			m_squares = new vector< vector<MapSquare> >(width);
			for (int x = 0; x < width; x++)
			{
				(*m_squares)[x] = vector<MapSquare>(height);
				for (int y = 0; y < height; y++)
				{
					stringstream out;
					out << "//square[@x=" << x << " and @y=" << y << "]";
					xml_node elemSquare = element.select_single_node(out.str().c_str()).node();
					(*m_squares)[x][y] = MapSquare(elemSquare);
				}
			}
		}

		GameMap::~GameMap()
		{
			delete m_squares;
			delete m_flags;
		}

		int GameMap::getWidth()
		{
			return m_squares->size();
		}

		int GameMap::getHeight()
		{
			return m_squares->at(0).size();
		}

		vector< vector<MapSquare> >* GameMap::getSquares()
		{
			return m_squares;
		}

		/*void GameMap::setSquares(vector<vector<MapSquare>> value)
		{
			m_squares = value;
		}*/

		vector<Point>* GameMap::getFlags()
		{
			return m_flags;
		}

		/*void GameMap::setFlags(vector<Point> value)
		{
			m_flags = value;
		}*/

		MapSquare* GameMap::GetSquare(Point location)
		{
			return &(*m_squares)[location.X][location.Y];
		}
	}
}
