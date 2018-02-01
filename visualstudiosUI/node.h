#pragma once

#include <list>
#include <vector>

class Node {
private:
	std::list<Node*>* children;	//list of pointers for children Nodes
	
public:

	std::string name;
	std::string textFileName;
	std::string tweets;
	int strength;

	Node(std::string s);
	Node();
	~Node();
	Node* parent; //pointer to parent node
	bool isPoly = false;

	void setPolyTrue();
	//void transform();
	std::list<Node*>* getChildren();
	void setChildren(std::list<Node*>* c);
	Node* getParent();
	void setParent(Node* p);

	void addChild(Node* n);
	void removeNode(Node * r);
	//void setName(std::string n);
	void setTextFileName(std::string n);
	//void setTweets(std::string n);
};
