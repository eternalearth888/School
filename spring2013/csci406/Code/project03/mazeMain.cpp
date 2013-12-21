#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "mazeEdge.h"

using namespace std;

vector<mazeEdge> allEdges;
vector<mazeEdge> finalPath;

void readFile();
void printAllEdges();
void printFinalPath();
void depthFirstSearch(int vertex);

int main() {
	readFile();
//	printAllEdges();
	depthFirstSearch(0);

	return 0;
}

void readFile() {

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
	cout << "Depth First Search:" << endl;

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
	allEdges.pop_back();
	allEdges.pop_back();

	inputFile.close();
}

void printAllEdges() {
	for (int i = 0; i < allEdges.size(); i++) {
		cout << "Start: " << allEdges.at(i).getInitial() << " Next: " << allEdges.at(i).getNext() << " Color: " << allEdges.at(i).getColor() << " Type: " << allEdges.at(i).getType() << endl;
	}
}

void printFinalPath() {
	cout << "Path Length: " << finalPath.size() << endl;
	cout << "[A, ";
	for (int i = 0; i < finalPath.size(); i++) {
		cout << finalPath.at(i).getInitial() << ", ";
	}
	cout << "j]" << endl;
}


void depthFirstSearch(int vertex) {
	int currentVertex = vertex;

	allEdges.at(currentVertex).setSeen(1);

//	cout << "DFS allEdges: " << allEdges.at(currentVertex).getInitial() << endl;

	for (int i = 0; i < allEdges.size(); i++) {
		if (i != currentVertex) {
			if (allEdges.at(currentVertex).getInitial() != allEdges.at(i).getNext()) {	
				if (allEdges.at(i).getSeen() == 0 && allEdges.at(i).getInitial() == allEdges.at(currentVertex).getNext()) {
					if (allEdges.at(i).getColor() == allEdges.at(currentVertex).getColor() || allEdges.at(i).getType() == allEdges.at(currentVertex).getType()) {
						if (allEdges.at(i).getNext() != 'j') {
							finalPath.push_back(allEdges.at(i));
							depthFirstSearch(i);
						} else {
							finalPath.push_back(allEdges.at(i));
							printFinalPath();
						}
					}
				}
			}
		}
	}
	finalPath.pop_back();
	allEdges.at(currentVertex).setSeen(2);
}
