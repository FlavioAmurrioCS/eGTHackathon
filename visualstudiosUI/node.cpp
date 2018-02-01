#include "node.h"


Node::~Node() {
	//delete this->parent;
	delete this->children;
}
Node::Node(std::string s) {
	this->name = s;
	this->parent = NULL;
	this->textFileName = "";
	this->strength = 0;
	this->tweets = "";
	this->children = new std::list<Node*>();

}
Node::Node() {
	this->parent = NULL;
	this->children = new std::list<Node*>();

}

void Node::setPolyTrue() {
	this->isPoly = true;
}

void Node::addChild(Node * child)
{
	if (child != NULL) 
	{
         child->parent = this;
	     this->children->push_back(child);
	}
}
void Node::removeNode(Node * rNode)
{
	for (std::list<Node*>::iterator it = this->children->begin(); it !=
		this->children->end(); ++it)
	{
		if ((*it) == rNode)
		{
			(this->children)->erase(it);
			return;
		}
	}
}
void Node::setTextFileName(std::string n)
{
	textFileName = n;

}

std::list<Node*>* Node::getChildren(){return this->children;}

void Node::setChildren(std::list<Node*>* c) {
	this->children = c;
}

Node* Node::getParent(){return this->parent;}

void Node::setParent(Node * p){this->parent = p;}


