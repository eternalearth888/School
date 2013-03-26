#include "stdafx.h"
#include "SimpleAStar.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Drawing;
using namespace System::Linq;
using namespace PlayerCPPAI::api;
namespace PlayerCPPAI
{
	namespace AI
	{

		SimpleAStar::TrailPoint::TrailPoint(Point pt, Point end, int cost)
		{
			MapTile = pt;
			Neighbors = gcnew List<TrailPoint^>();
			Distance = Math::Abs(MapTile.X - end.X) + Math::Abs(MapTile.Y - end.Y);
			Cost = cost;
		}

		void SimpleAStar::TrailPoint::RecalculateDistance(Point mapTileCaller, int remainingSteps)
		{

			Trap::trap(Distance == 0);
			// if no neighbors then this is in notEvaluated and so can't recalculate.
			if (Neighbors->Count == 0)
				return;

			int shortestDistance;
			// if just 1 neighbor, then it's a dead end
			if (Neighbors->Count == 1)
				shortestDistance = DEAD_END;
			else
			{
				shortestDistance = Int32::MaxValue;
				for each (TrailPoint^ neighborOn in Neighbors)
					if (neighborOn->Distance < shortestDistance)
						shortestDistance = neighborOn->Distance;
				// it's 1+ lowest neighbor value (unless a dead end)
				if (shortestDistance != DEAD_END)
					shortestDistance++;
			}

			// no change, no need to recalc neighbors
			if (shortestDistance == Distance)
				return;

			// new value (could be longer or shorter)
			Distance = shortestDistance;

			// if gone to far, no more recalculate
			if (remainingSteps-- < 0)
				return;

			//  Need to tell our neighbors - except the one that called us
			for each (TrailPoint ^neighborOn in Neighbors)
				if (neighborOn->MapTile != mapTileCaller)
					neighborOn->RecalculateDistance(MapTile, remainingSteps);

			// and we re-calc again because that could have changed our neighbor's values
			shortestDistance = Int32::MaxValue;
				for each (TrailPoint^ neighborOn in Neighbors)
					if (neighborOn->Distance < shortestDistance)
						shortestDistance = neighborOn->Distance;
			// it's 1+ lowest neighbor value (unless a dead end)
			if (shortestDistance != DEAD_END)
				shortestDistance++;
			Distance = shortestDistance;
		}

		String ^SimpleAStar::TrailPoint::ToString()
		{
			return String::Format("Map={0}, Cost={1}, Distance={2}, Neighbors={3}", MapTile, Cost, Distance, Neighbors->Count);
		}

		List<Point> ^SimpleAStar::CalculatePath(Map ^map, Point start, Point end)
		{

			// should never happen but just to be sure
			if (start == end)
				return gcnew List<Point>(gcnew array<Point> {start});

			// nodes are points we have walked to
			Dictionary<Point, TrailPoint^> ^nodes = gcnew Dictionary<Point, TrailPoint^>();
			// points we have in a TrailPoint, but not yet evaluated.
			List<TrailPoint^> ^notEvaluated = gcnew List<TrailPoint^>();

			TrailPoint ^tpOn = gcnew TrailPoint(start, end, 0);
			while (true)
			{
				nodes->Add(tpOn->MapTile, tpOn);

				// get the neighbors
				TrailPoint ^tpClosest = nullptr;
				for each (Point ptOffset in offsets)
				{
					Point pt = Point(tpOn->MapTile.X + ptOffset.X, tpOn->MapTile.Y + ptOffset.Y);
					MapSquare ^square = map->SquareOrDefault(pt);
					// off the map or not a road/bus stop
					if ((square == nullptr) || (!square->IsDriveable))
						continue;

					// already evaluated - add it in
					if (nodes->ContainsKey(pt))
					{
						TrailPoint ^tpAlreadyEvaluated = nodes[pt];
						tpAlreadyEvaluated->Cost = Math::Min(tpAlreadyEvaluated->Cost, tpOn->Cost + 1);
						tpOn->Neighbors->Add(tpAlreadyEvaluated);
						continue;
					}

					// add this one in
					TrailPoint ^tpNeighbor = gcnew TrailPoint(pt, end, tpOn->Cost + 1);
					tpOn->Neighbors->Add(tpNeighbor);
					// may already be in notEvaluated. If so remove it as this is a more recent cost estimate
					int indTp = -1;
					for (int i = 0; i < notEvaluated->Count; i++)
						if (notEvaluated[i]->MapTile == tpNeighbor->MapTile) {
							indTp = i;
							break;
						}
					if (indTp != -1)
						notEvaluated->RemoveAt(indTp);

					// we only assign to tpClosest if it is closer to the destination. If it's further away, then we
					// use notEvaluated below to find the one closest to the dest that we have not walked yet.
					if (tpClosest == nullptr)
					{
						if (tpNeighbor->Distance < tpOn->Distance)
							// new neighbor is closer - work from this next. 
							tpClosest = tpNeighbor;
						else
							// this is further away - put in the list to try if a better route is not found
							notEvaluated->Add(tpNeighbor);
					}
					else
						if (tpClosest->Distance <= tpNeighbor->Distance)
							// this is further away - put in the list to try if a better route is not found
							notEvaluated->Add(tpNeighbor);
						else
						{
							// this is closer than tpOn and another neighbor - use it next.
							notEvaluated->Add(tpClosest);
							tpClosest = tpNeighbor;
						}
				}

				// re-calc based on neighbors
				tpOn->RecalculateDistance(ptOffMap, map->Width);

				// if no closest, then get from notEvaluated. This is where it guarantees that we are getting the shortest
				// route - we go in here if the above did not move a step closer. This may not either as the best choice
				// may be the neighbor we didn't go with above - but we drop into this to find the closest based on what we know.
				if (tpClosest == nullptr)
				{
					if (notEvaluated->Count == 0)
					{
						Trap::trap();
						break;
					}
					// We need the closest one as that's how we find the shortest path.
					tpClosest = notEvaluated[0];
					int index = 0;
					for (int ind = 1; ind < notEvaluated->Count; ind++)
					{
						TrailPoint ^tpNotEval = notEvaluated[ind];
						if (tpNotEval->Distance >= tpClosest->Distance)
							continue;
						tpClosest = tpNotEval;
						index = ind;
					}
					notEvaluated->RemoveAt(index);
				}

				// if we're at end - we're done!
				if (tpClosest->MapTile == end)
				{
					tpClosest->Neighbors->Add(tpOn);
					nodes->Add(tpClosest->MapTile, tpClosest);
					break;
				}

				// try this one
				tpOn = tpClosest;
			}

			// Create the return path - from end back to beginning.
			List<Point> ^path = gcnew List<Point>();
			tpOn = nodes[end];
			path->Add(tpOn->MapTile);
			while (tpOn->MapTile != start)
			{
				List<TrailPoint^> ^neighbors = tpOn->Neighbors;
				int cost = tpOn->Cost;

				tpOn = tpOn->Neighbors[0];
				for (int ind = 1; ind < neighbors->Count; ind++)
					if (neighbors[ind]->Cost < tpOn->Cost)
						tpOn = neighbors[ind];

				// we didn't get to the start.
				if (tpOn->Cost >= cost)
				{
					Trap::trap();
					return path;
				}
				path->Insert(0, tpOn->MapTile);
			}

			return path;
		}
	}
}
