#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "mazeEdge.h"

using namespace std;

vector<mazeEdge> allEdges;
vector<mazeEdge> path;

void printAllEdges();
void printPath();
void depthFirstSearch(int vertex);

int main() {

	/** inputFile, Error Checking and whatnot **/
	ifstream inputFile;
	string numVillages, numTransit;
	char start, end, color, type;
	int visited = 0; // 0 = white, 1 = grey, 2 = black
	int label = 0;

	if (!inputFile) {
		cerr << "ERROR: File does not open or does not exist." << endl;
		exit(1);
	}

	// Assuming no errors, open the input file
	inputFile.open("input.txt");
	
	// Grab the first line
	inputFile >> numVillages >> numTransit;
	cout << "Villages: " << numVillages << " Transit Lines: " << numTransit << endl;

	while (!inputFile.eof()) {
		// read the information
		inputFile >> start >>  end >> color >> type;

		// cout << start << end << color << type << endl;

		// Add edge going forward
		mazeEdge village(start, end, color, type, visited, label);
		label += 1;

		// Add edge going backward
		mazeEdge village2(end, start, color, type, visited, label);
		label += 1;

		allEdges.push_back(village);
		allEdges.push_back(village2);		
	}

	inputFile.close();

	cout << "depthFirstSearch: " << endl;
	depthFirstSearch(0);

	return 0;
}

void printAllEdges() {
	for (int i = 0; i < allEdges.size(); i++) {
		cout << "Start: " << allEdges.at(i).getInitial() << " Next: " << allEdges.at(i).getNext() << " Color: " << allEdges.at(i).getColor() << " Type: " << allEdges.at(i).getType() << endl;
	}
}

void printPath() {
	cout << "Path Length: " << path.size() << endl;
	cout << "A ";
	for (int i = 0; i < path.size(); i++) {
		cout << path.at(i).getInitial() << " ";
	}
	cout << "j" << endl;
}


void depthFirstSearch(int vertex) {
	int currentVertex = vertex;

	allEdges.at(currentVertex).setSeen(1);

	cout << "DFS allEdges: " << allEdges.at(currentVertex).getInitial() << endl;

	for (int i = 0; i < allEdges.size(); i++) {
		if (i != currentVertex) {
			if (allEdges.at(currentVertex).getInitial() != allEdges.at(i).getNext()) {	
				if (allEdges.at(i).getSeen() == 0 && allEdges.at(i).getInitial() == allEdges.at(currentVertex).getNext()) {
					if (allEdges.at(i).getColor() == allEdges.at(currentVertex).getColor() || allEdges.at(i).getType() == allEdges.at(currentVertex).getType()) {
						if (allEdges.at(i).getNext() != 'j') {
							path.push_back(allEdges.at(i));
							cout << "hello" << endl;
							depthFirstSearch(i);
						} else {
							path.push_back(allEdges.at(i));
							printPath();
						}
					}
				}
			}
		}
	}
	path.pop_back();
	allEdges.at(currentVertex).setSeen(2);
}
