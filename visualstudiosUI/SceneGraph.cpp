#include "SceneGraph.h"

SceneGraph::SceneGraph()
{
	this->root = new Node();
}
//makes a copy of the scene graph also copying the root
SceneGraph::SceneGraph(const SceneGraph &sg) {
	this->root = new Node();
	*root = *sg.root;
}
void SceneGraph::setRoot(Node* r) {
	this->root = r;
}
Node* SceneGraph::getRoot()
{
	return this->root;
}
SceneGraph::~SceneGraph() {
	delete root;
	this->root = new Node();
}
void SceneGraph::addKid(Node* parent, Node* child) {
	parent->addChild(child);
	//->setParent(parent);
}

