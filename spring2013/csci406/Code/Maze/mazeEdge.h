
class mazeEdge {
public:
	mazeEdge();
	mazeEdge(char i, char n, char c, char t, int s, int l);
	
	char getInitial();
	void setInitial(char i);

	char getNext();
	void setNext(char n);

	char getColor();
	void setColor(char c);

	char getType();
	void setType(char t);

	int getSeen();
	void setSeen(int s);

	int getLabel();
	void setLabel(int l);


private:
	char initial; // from this village
	char next; // to this village
	char color;
	char type;
	int seen;
	int label;
};