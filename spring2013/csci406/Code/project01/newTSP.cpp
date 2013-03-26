#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <algorithm>

// I had help from Tri Nguyen in fixing my code for distance. We ended
// up refactoring all my code
struct Point{
	int x, y;
};


bool comparePoints(Point p1, Point p2) {
	return p1.x < p2.x;
}

double calcDistance(Point& p1, Point& p2) {
	return sqrt( pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2) );
}

double showPoints(Point p[], int SIZE) {
	for (int i = 0; i < SIZE; i++) {
		std::cout << " (" << p[i].x << "," << p[i].y << ")";
	}
	std::cout << std::endl;
}

void switchPoint(Point p[], int m, int n) {
	Point temp;

	temp.x = p[m].x;
	temp.y = p[m].y;

	p[m].x = p[n].x;
	p[m].y = p[n].y;

	p[n].x = temp.x;
	p[n].y = temp.y;
}

void copyPoints(Point original[], Point next[], int SIZE) {
	for (int i = 0; i < SIZE; i++) {
		next[i].x = original[i].x;
		next[i].y = original[i].y;
	}
}

double finalDistance(Point p[], int SIZE) {
	double totalDistance = 0;
	for (int i = 0; i < (SIZE-1); i++) {
		totalDistance += calcDistance(p[i], p[i+1]);
	}

	totalDistance += calcDistance(p[0], p[SIZE-1]);

	return totalDistance;
}

void nearestNeighbor(Point p[], int SIZE) {
	std::clock_t startClock;
    std::clock_t finishClock;
    double timeCount =  0;

    startClock=clock();

	int seen = 0;

	for (int i = (seen+1); i < SIZE; i++) {
		double smallDistance = calcDistance(p[seen], p[i]);
		int nearestPoint = i;

		for (int j = (i+1); j < SIZE; j++) {
			double temp = calcDistance(p[seen], p[j]);

			if (smallDistance > temp) {
				smallDistance = temp;
				nearestPoint = j;
			}
		}

		if (nearestPoint != i) {
			switchPoint(p, i, nearestPoint);
		}

		seen = i;
	}

    finishClock = clock();

    timeCount = finishClock-startClock;
    timeCount = timeCount/1000;

    std::cout << "Total time: " << timeCount << " microseconds" << std::endl;
}

void exhaustiveSearch(Point p[], int SIZE) {

    std::clock_t startClock;
    std::clock_t finishClock;
    double timeCount =  0;

    startClock=clock();

	Point *minimum = new Point[SIZE];
    copyPoints(p, minimum, SIZE);
    double smallDistance = finalDistance(p, SIZE);

    std::sort(p, p+SIZE, comparePoints);

    do{
        double temp = finalDistance(p, SIZE);
        if(temp <= smallDistance) {
            smallDistance = temp;
            copyPoints(p, minimum, SIZE);
            }
    } while (std::next_permutation(p,p+SIZE,comparePoints));
    copyPoints(minimum, p, SIZE);

    finishClock = clock();

    timeCount = finishClock-startClock;
    timeCount = timeCount/1000;

    std::cout << "Total time: " << timeCount << " microseconds" << std::endl;
}

int main(){
	int n = 0;

	std::ifstream myData("input1copy.txt");

	if (!myData) {
		std::cerr << "ERROR: File will not open or does not exist" << std::endl;
		exit(1);
	}

	// Grab the number of points
	

	myData >> n;
	std::cout << "Total Points: " << n << std::endl;

	Point *points = new Point[n];

	for (int i = 0; i < n; i++) {
		myData >> points[i].x;
		myData >> points[i].y;
	}

	myData.close();

	//NEAREST NEIGHBOR
	std::cout << "NEAREST NEIGHBOR: " << std::endl;
	nearestNeighbor(points, n);
	showPoints(points, n);
	if (n > 1) {
		showPoints(points, 1);
	}

	std::cout << "Total distance: " << finalDistance(points, n) << std::endl;


	//EXHAUSTIVE SEARCH
	//std::cout << "EXHAUSTIVE SEARCH: " << std::endl;
	//exhaustiveSearch(points, n);
	//showPoints(points, n);
	//if (n > 1) {
	//	showPoints(points, 1);
	//}

	//std::cout << "Total distance: " << finalDistance(points, n) << std::endl;

	return 0;
}


