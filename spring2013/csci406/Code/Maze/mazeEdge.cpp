
#include "mazeEdge.h"

mazeEdge::mazeEdge() {}

mazeEdge::mazeEdge(char i, char n, char c, char t, int s, int l) {
	initial = i;
	next = n;
	color = c;
	type = t;
	seen = s;
	label = l;
}

char mazeEdge::getInitial() {
	return initial;
}

void mazeEdge::setInitial(char i) {
	initial = i;
}

char mazeEdge::getNext() {
	return next;
}

void mazeEdge::setNext(char n) {
	next  = n;	
}

char mazeEdge::getColor() {
	return color;
}

void mazeEdge::setColor(char c) {
	color = c;
}

char mazeEdge::getType() {
	return type;
}

void mazeEdge::setType(char t) {
	type = t;
}

int mazeEdge::getSeen() {
	return seen;
}

void mazeEdge::setSeen(int s) {
	seen = s;
}

int mazeEdge::getLabel() {
	return label;
}

void mazeEdge::setLabel(int l) {
	label = l;
}