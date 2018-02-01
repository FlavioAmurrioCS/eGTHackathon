
// The Window class has the main Qt components and links together the GUI with the scene graph

#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QtWidgets>
#include <QSlider>
#include <QColorDialog>
#include <QColor>
#include <list>
//#include "SceneGraph.h"


//class Data;  // forward declaration of my simple little data class
class Node;   //foward declaration of Node class
class SceneGraph;

namespace Ui {
class Window;
}

class Window : public QWidget
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = 0);
	//Window(QWidget * parent);
	~Window();
	Node* getRoot();

protected:
    void keyPressEvent(QKeyEvent *event);
	//void save_Frame();
	SceneGraph * getCurrentSceneGraph();
	void setupTreeView(Node * n, QStandardItem * row);
	void setupListView(Node* n);
	std::vector<Node*> sortStringNames(Node* n);
	Node* createFriend();

	signals:
	
	public slots :
		// Called when a different item in the tree view is selected.
		void on_treeView_currentItemChanged(const QItemSelection &selected, const QItemSelection &deselected);   
		
		//void displayTweets();
		void displayTweets(std::string str);
		void search_button();
		Node* readTextFile();

private:
    Ui::Window *ui;				// A Qt internal mechanism
	QStandardItemModel* model;  // Links Qt with your scene graph 
	QStandardItem* tempItem;
	QTimer* timer;

	std::vector<SceneGraph*>* sceneList; //used to store frames and used for animation
	int count;
	SceneGraph* currentScene;

	Node* currentNode;  //pointer to the currently selected "node"
	Node* root;	//variable to store the root
	
};

#endif // WINDOW_H
