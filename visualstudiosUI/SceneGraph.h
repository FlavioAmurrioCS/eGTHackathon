#pragma once


#include "node.h"
#include <list>

class SceneGraph{

private:

public:
	Node* root;
	SceneGraph();
	SceneGraph(const SceneGraph & sg);
	void setRoot(Node * r);
	~SceneGraph();
	Node* getRoot();
	void addKid(Node* parent, Node* kid);

};
