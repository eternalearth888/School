#pragma once

#include "Trap.h"
#include "Map.h"
#include "MapSquare.h"

// No comments about how this is the world's worst A* implementation. It is purposely simplistic to leave the teams
// the opportunity to improve greatly upon this. (I was yelled at last year for making the sample A.I.'s too good.)
//
// Also there is (at least) one very subtle bug in the below code. It is very rarely hit.

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Drawing;
using namespace System::Linq;
using namespace PlayerCPPAI::api;

namespace PlayerCPPAI
{
	namespace AI
	{
		// The Pathfinder (maybe I should name it Frémont).
		// Good intro at http://www.policyalmanac.org/games/aStarTutorial.htm
		public ref class SimpleAStar
		{
		private:
			ref class TrailPoint
			{
			public:
				// The Map tile for this point in the trail.
				property Point MapTile;

				// The neighboring tiles (up to 4). If 0 then this point has been added as a neighbor but is in the
				// notEvaluated List because it has not yet been tried.
				property List<TrailPoint^> ^Neighbors;

				// Estimate of the distance to the end. Direct line if have no neighbors. Best neighbor.Distance + 1
				// if have neighbors. This value is bad if it's along a trail that failed.
				property int Distance;

				// The number of steps from the start to this tile.
				property int Cost;

				TrailPoint(Point pt, Point end, int cost);

				void RecalculateDistance(Point mapTileCaller, int remainingSteps);

				virtual String ^ToString() override;
			};

			static initonly array<Point> ^offsets = {Point(-1, 0), Point(1, 0), Point(0, -1), Point(0, 1)};

			literal int DEAD_END = 10000;

			static initonly Point ptOffMap = Point(-1, -1);

		public:
			// Calculate a path from start to end. No comments about how this is the world's worst A* implementation. It is purposely 
			// simplistic to leave the teams the opportunity to improve greatly upon this. (I was yelled at last year for making the 
			// sample A.I.'s too good.)
			// map: The game map.
			// start: The tile units of the start point (inclusive).
			// end: The tile units of the end point (inclusive).
			// returns: The path from start to end.
			static List<Point> ^CalculatePath(Map ^map, Point start, Point end);

		};
	}
}
