#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <math.h>
#define max 29
#define storeys 2
using namespace std;
class Queue;
class Node {
	int x;
	int y;
	int floor;
	bool E;
	bool W;
	bool N;
	bool S;
	bool T;
	bool B;
public:
	string name;
	char symb;
	friend void inp(Node x[storeys][max][max], Queue landmark[4], char a[storeys][max][max]);
	friend void ewns(Node x[storeys][max][max]);
	friend void nomenclature(Node m[storeys][max][max]);
	friend void code(Node x[storeys][max][max]);
	friend void display(Node x[storeys][max][max]);
	friend int path(Node mymap[storeys][max][max], int i, int j, int f, int symb);
	friend Node search(Node x[storeys][max][max], string n);
	void print() {
		cout << symb;
	}
	void p() {
		cout << symb;
		cout << "(" << x << ',' << y << ',' << floor << ")";
	}
	bool check(Node a) {
		if (x == a.x && y == a.y && floor == a.floor)
			return 1;
		return 0;
	}
	Node() {
		name = "NULL";
		x = 0;
		y = 0;
		floor = 0;
		symb = '#';
		E = 0;
		W = 0;
		N = 0;
		S = 0;
	}
}mymap[storeys][max][max];
class Queue {
	Node a[1000];
	int front;
	int rear;
public:
	Queue() {
		front = -1;
		rear = -1;
	}
	void enqueue(Node x) {
		if (front == -1) {
			front++;
		}
		a[++rear] = x;
	}
	bool isEmpty() {
		return front == -1;
	}
	Node dequeue() {
		int f = front;
		if (front == rear) {
			front = -1;
			rear = -1;
		}
		else
			front++;
		return a[f];
	}
	bool search(Node m) {
		for (int i = front; i <= rear; i++) {
			if (a[i].check(m)==1) {
				return 1;
			}
		}
		return 0;
	}
	Node peek() {
		return a[rear];
	}
	void number() {
		cout << front << ',' << rear << endl;
	}
	void print() {
		if (this->isEmpty() == 0) {
			for (int i = front; i <= rear; i++) {
				a[i].p();
				cout << '\t';
			}
			cout << endl;
		}
		else
			cout << "empty" << endl;
	}
	void clear() {
		front = -1;
		rear = -1;
	}
}frontier, explored, landmark[4];

class LLNode {
public:
	Node key;
	Node value;
	LLNode* next;

	LLNode(Node key, Node value)
	{
		this->key = key;
		this->value = value;
		this->next = NULL;
	}
	bool check(Node a) {
		if (key.check(a)==1)
			return 1;
		return 0;
	}
};

class Dict {
	LLNode* head;

public:
	Dict() { head = NULL; }
	void append(Node, Node);
	Node value(Node);
	bool c(Node);

	void print() {
		LLNode* temp = head;
		cout << "{";
		while (temp != NULL) {
			cout << "[";
			temp->key.p();
			cout << ":";
			temp->value.p();
			cout << "]";
			temp = temp->next;
		}
		cout << "}";
	}

};


void Dict::append(Node key, Node value)
{
	LLNode* newNode = new LLNode(key, value);
	if (head == NULL) {
		//cout << this->c(key) << endl;
		head = newNode;
		//cout << "add kardiya " << endl;
		//cout << this->c(key) << endl;
		//this->print();
		return;
	}
	LLNode* temp = head;
	while (temp->next != NULL) {
		if (temp->key.check(key) == 1) {
			//cout << this->c(key) << endl;
			//cout << "Nahi ho paya" << endl;
			//cout << this->c(key) << endl;
			//this->print();
			return;
		}
		temp = temp->next;
	}
	//cout << this->c(key) << endl;
	temp->next = newNode;
	//cout << "add kardiya " << endl;
	//cout << this->c(key) << endl;
	//this->print();
	return;
}

Node Dict::value(Node x)
{
	LLNode* temp = head;
	Node n;
	if (head == NULL) {
		cout << "List empty" << endl;
		return n;
	}
	while (temp != NULL) {
		if (temp->check(x) == 1) {
			return temp->value;
		}
		temp = temp->next;
	}
	return n;

}
bool Dict::c(Node x)
{
	LLNode* temp = head;
	if (head == NULL) {
		return 0;
	}
	while (temp != NULL) {
		if (temp->check(x) == 1) {
			return 1;
		}
		temp = temp->next;
	}
	return 0;
}

void inp(Node x[storeys][max][max], Queue landmark[4], char a[storeys][max][max]) {
	for (int k = 0; k < storeys; k++) {
		for (int j = 0; j < max; j++) {
			for (int i = 0; i < max; i++) {
				x[k][i][j].x = i;
				x[k][i][j].y = j;
				x[k][i][j].floor = k;
				x[k][i][j].symb = a[k][i][j];
				if (x[k][i][j].symb == 'B') {
					landmark[0].enqueue(x[k][i][j]);
				}
				else if (x[k][i][j].symb == 'G') {
					landmark[1].enqueue(x[k][i][j]);
				}
				else if (x[k][i][j].symb == 'W') {
					landmark[2].enqueue(x[k][i][j]);
				}
				else if (x[k][i][j].symb == 'S') {
					landmark[3].enqueue(x[k][i][j]);
				}
			}
		}
	}
}
void ewns(Node x[storeys][max][max]) {
	for (int k = 0; k < storeys; k++) {
		for (int j = 0; j < max; j++) {
			for (int i = 0; i < max; i++) {
				if (i - 1 < 0 || x[k][i - 1][j].symb == '#')
					x[k][i][j].N = 0;
				else
					x[k][i][j].N = 1;
				if (j - 1 < 0 || x[k][i][j - 1].symb == '#')
					x[k][i][j].W = 0;
				else
					x[k][i][j].W = 1;
				if (i + 1 > max - 1 || x[k][i + 1][j].symb == '#')
					x[k][i][j].S = 0;
				else
					x[k][i][j].S = 1;
				if (j + 1 > max - 1 || x[k][i][j + 1].symb == '#')
					x[k][i][j].E = 0;
				else
					x[k][i][j].E = 1;
				if (k - 1 < 0 || x[k][i][j].symb != 'S')
					x[k][i][j].B = 0;
				else
					x[k][i][j].B = 1;
				if (k + 1 > storeys - 1 || x[k][i][j].symb != 'S')
					x[k][i][j].T = 0;
				else
					x[k][i][j].T = 1;
				if (x[k][i][j].symb == 'R') {
					x[k][i][j].N = 0;
					x[k][i][j].S = 0;
					x[k][i][j].E = 0;
					x[k][i][j].W = 0;
				}

			}
		}
	}
}
int strtoint(string s) {
	int k = 0;
	for (int i = 0; i < s.length(); i++) {
		k += (s[i] - '0') * (pow(10, (s.length() - 1 - i)));
	}
	return k;
}
void nomenclature(Node m[storeys][max][max]) {
	vector<vector<string>> content;
	vector<string> row;
	string line, word;

	fstream file("Book3.csv", ios::in);
	if (file.is_open())
	{
		while (getline(file, line))
		{
			row.clear();

			stringstream str(line);

			while (getline(str, word, ','))
				row.push_back(word);
			content.push_back(row);
		}
	}
	else
		cout << "Could not open the file\n";
	int x, y, z;

	for (int i = 0; i < content.size(); i++)
	{
		x = strtoint(content[i][0]);
		y = strtoint(content[i][1]);
		z = strtoint(content[i][2]);
		if (m[z][x][y].symb == 'R')
			m[z][x][y].name = content[i][3];
		else
			cout << "check room name co-ordinates";
	}
	file.close();
}
void code(Node x[storeys][max][max]) {
	for (int k = 0; k < storeys; k++) {
		for (int i = 0; i < max; i++) {
			for (int j = 0; j < max; j++) {
				if (x[k][i][j].symb == 'R') {
					x[k][i][j].p();
					cout << ":-" << x[k][i][j].name << endl;
				}
			}
		}
	}
}


void display(Node x[storeys][max][max]) {
	for (int k = 0; k < storeys; k++) {
		cout << "Floor #" << k << ":-" << endl;
		for (int i = -1; i < max; i++) {
			if (i < 0) {
				cout << " \t";
				for (int j = 0; j < max; j++) {
					cout << j;
					if (j < 10)
						cout << " ";
				}
				cout << endl;
			}
			else {
				cout << i << '\t';
				for (int j = 0; j < max; j++) {
					x[k][i][j].print();
					cout << ' ';
				}
				cout << endl;
			}
		}
		cout << endl;
	}
}
void copy(Node x[storeys][max][max], Node y[storeys][max][max]) {
	for (int k = 0; k < storeys; k++) {
		for (int i = 0; i < max; i++) {
			for (int j = 0; j < max; j++) {
				y[k][i][j] = x[k][i][j];
			}
		}
	}
}
Node search(Node x[storeys][max][max], string n) {
	Node a;
	for (int k = 0; k < storeys; k++) {
		for (int i = 0; i < max; i++) {
			for (int j = 0; j < max; j++) {
				if (x[k][i][j].name == n) {
					return x[k][i][j];
				}
			}
		}
	}
	return a;
}
int path(Node mymap[storeys][max][max], int i, int j, int f, int symb) {
	Node end;
	string name;
	if (symb == 4) {
		int x, y, z;
		do {
			code(mymap);
			cout << "Enter Class/Office Co-ordinates:-";
			cin >> x >> y >> z;
			if (x > max - 1 || y > max - 1 || z > storeys - 1 || x < 0 || y < 0 || z < 0 || mymap[z][x][y].symb != 'R') {
				cout << "incorrect co-ordinate" << endl;
				continue;
			}
			break;
		} while (1);
		end = mymap[z][x][y];
	}
	Node m[storeys][max][max];
	copy(mymap, m);
	Node start = m[f][i][j];
	frontier.enqueue(start);
	explored.enqueue(start);
	Dict bfs, fwd;
	Node currCell;
	Node childCell;
	Node cell;
	//cout << "frontier:-" << '\t';
	//frontier.print();
	//cout<<endl;
	//cout << frontier.isEmpty() << endl;
	while (frontier.isEmpty() == 0) {
		currCell = frontier.dequeue();
		//cout << "current element:-" << '\t';
		//currCell.p();
		//cout<<endl;
		//cout << "frontier:-" << '\t';
		//frontier.print();
		//cout<<endl;
		if (symb != 4) {
			if (landmark[symb].search(currCell) == 1) {
				cell = currCell;
				if (symb != 3)
					m[currCell.floor][currCell.x][currCell.y].symb = 'F';
				break;
			}
		}
		else {
			if (currCell.x == end.x && currCell.y == end.y && currCell.floor == end.floor) {
				cell = currCell;
				if (symb != 3)
					m[currCell.floor][currCell.x][currCell.y].symb = 'F';
				break;
			}
		}
		if (currCell.E == 1) {
			//cout << "east:-" << '\t';
			childCell = m[currCell.floor][currCell.x][currCell.y + 1];
			//childCell.p();
			//cout<<endl;
			if (explored.search(childCell) == 0) {
				//cout << "added" << endl;
				frontier.enqueue(childCell);
				explored.enqueue(childCell);
				bfs.append(childCell, currCell);
			}
		}
		if (currCell.W == 1) {
			//cout << "west:-" << '\t';
			childCell = m[currCell.floor][currCell.x][currCell.y - 1];
			//childCell.p();
			//cout<<endl;
			if (explored.search(childCell) == 0) {
				//cout << "added" << endl;
				frontier.enqueue(childCell);
				explored.enqueue(childCell);
				bfs.append(childCell, currCell);
			}
		}
		if (currCell.N == 1) {
			//cout << "north:-" << '\t';
			childCell = m[currCell.floor][currCell.x - 1][currCell.y];
			//childCell.p();
			//cout<<endl;
			if (explored.search(childCell) == 0) {
				//cout << "added" << endl;
				frontier.enqueue(childCell);
				explored.enqueue(childCell);
				bfs.append(childCell, currCell);
			}
		}
		if (currCell.S == 1) {
			//cout << "south:-" << '\t';
			childCell = m[currCell.floor][currCell.x + 1][currCell.y];
			//childCell.p();
			//cout<<endl;
			if (explored.search(childCell) == 0) {
				//cout << "added" << endl;
				frontier.enqueue(childCell);
				explored.enqueue(childCell);
				bfs.append(childCell, currCell);
			}
		}
		if (currCell.T == 1 && currCell.floor < storeys - 1) {
			//cout << "UPSTAIRS:-" << '\t';
			childCell = m[currCell.floor + 1][currCell.x][currCell.y];
			//childCell.p();
			//cout<<endl;
			if (explored.search(childCell) == 0) {
				//cout << "added" << endl;
				frontier.enqueue(childCell);
				explored.enqueue(childCell);
				bfs.append(childCell, currCell);
			}
		}
		if (currCell.B == 1 && currCell.floor > 0) {
			//cout << "DOWNSTAIRS:-" << '\t';
			childCell = m[currCell.floor - 1][currCell.x][currCell.y];
			//childCell.p();
			//cout<<endl;
			if (explored.search(childCell) == 0) {
				//cout << "added" << endl;
				frontier.enqueue(childCell);
				explored.enqueue(childCell);
				bfs.append(childCell, currCell);
			}
		}
		//cout << "frontier:-" << '\t';
		//frontier.print();
		//cout<<endl;
		//cout << "explored:-" << '\t';
		//explored.print();
		//cout<<endl;
	}
	if (cell.symb == '#') {
		cout << "Not Found" << endl;
		return 1;
	}
	//cout<<"Exploration pairs:-"<<endl;
	//bfs.print();
	//cout << endl;
	Node co = cell;
	while (co.x != i || co.y != j || co.floor != f) {
		//co.p();
		fwd.append(bfs.value(co), co);
		co = bfs.value(co);
		if (co.symb != 'S')
			m[co.floor][co.x][co.y].symb = '*';
	}
	//cout<<"Path:-"<<endl;
	//fwd.print();
	//cout<<endl;
	m[f][i][j].symb = 'I';
	frontier.clear();
	explored.clear();
	cout << "Path:-" << endl;
	display(m);
	cout << endl;
	return 1;
}


void read(char a[storeys][max][max])
{
	vector<vector<string>> content;
	vector<string> row;
	string line, word;

	fstream file("Book1.csv", ios::in);
	if (file.is_open())
	{
		while (getline(file, line))
		{
			row.clear();

			stringstream str(line);

			while (getline(str, word, ','))
				row.push_back(word);
			content.push_back(row);
		}
	}
	else
		cout << "Could not open the file\n";

	for (int i = 0; i < content.size(); i++)
	{
		for (int j = 0; j < content[i].size(); j++)
		{
			a[0][i][j] = content[i][j][0];
		}
	}
	file.close();
	fstream file1("Book2.csv", ios::in);
	if (file1.is_open())
	{
		while (getline(file1, line))
		{
			row.clear();

			stringstream str(line);

			while (getline(str, word, ','))
				row.push_back(word);
			content.push_back(row);
		}
	}
	else
		cout << "Could not open the file\n";

	for (int i = 0; i < content.size(); i++)
	{
		for (int j = 0; j < content[i].size(); j++)
		{
			a[0][i][j] = content[i][j][0];
		}
	}
	file1.close();
}
int main() {
	int x, y, z, n, final;
	int ok = 1;
	char a[storeys][max][max];
	read(a);
	string name = "None";
	inp(mymap, landmark, a);
	ewns(mymap);
	nomenclature(mymap);
	do {
		cout << "Map:-" << endl;
		display(mymap);
		cout << "enter your co-ordinates";
		cin >> x >> y >> z;
		if (x > max - 1 || y > max - 1 || z > storeys - 1 || x < 0 || y < 0 || z < 0 || mymap[z][x][y].symb == '#') {
			cout << "incorrect co-ordinate" << endl;
			cout << "continue?\n yes:1\n no:2" << endl;
			cin >> ok;
			continue;
		}
		cout << "\nwhere you wanna go?\n boys toilet:1\n girls toilet:2\n water cooler:3\n staircase or lift:4\n Room:5\n";
		cin >> n;
		switch (n) {
		case 1:
			final = 0;
			break;
		case 2:
			final = 1;
			break;
		case 3:
			final = 2;
			break;
		case 4:
			final = 3;
			break;
		case 5:
			final = 4;
			break;
		default:
			break;
		}
		path(mymap, x, y, z, final);
		cout << "continue?\n yes:1\n no:2" << endl;
		cin >> ok;

	} while (ok == 1);
	cout << "bye";
	return 0;
}
