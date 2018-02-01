
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "window.h"
#include "ui_window.h"
#include "node.h"
#include "SceneGraph.h"


Q_DECLARE_METATYPE(Node*);  // Tell Qt that Data is a type.

std::string getNewName() // return a unique name 
{
	static int count = 0;	// keep counting the number of objects

	std::string s;
	std::stringstream out;	// a stream for outputing to a string
	out << count++;			// make the current count into a string
	s = out.str();

	return "Node_" + s;	// append the current count onto the string
}

Window::Window(QWidget *parent) :  // Window constructor
    QWidget(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);				// Standard Qt stuff
	model = new QStandardItemModel();  // Tree views have to be populated with models, so create one
	sceneList = new std::vector<SceneGraph*>();
 
	Node* d = new Node("Root_User");
	QStandardItem* rootItem = new QStandardItem(QString::fromStdString(d->name));	// These would correspond to your scene graph nodes
	rootItem->setData(QVariant::fromValue(d));
	model->appendRow(rootItem);

	Node* friendRoot = createFriend();
	setupTreeView(friendRoot, rootItem);  // sets up treeview using QStandardItem
	
	setupListView(friendRoot);
	
	ui->treeView->setModel(model); // ui needs to include treeView, so create one in Qt Creator and make sure it is named treeView
								   // in the ui, I also made the header of the treeView not visible. 
	ui->treeView->expandAll();	   // show all of the items at all levels 

	// When a user selects an item in the treeView have a signal sent to a method in this class, on_treeView_currentItemChanged
	connect(ui->treeView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &Window::on_treeView_currentItemChanged);

	//when user presses a button in modeling mode
	connect(ui->searchButton, &QPushButton::clicked, this, &Window::search_button);
	
	currentNode = NULL; // Currently no node in the treeView is selected, so reflect that. 
}

Window::~Window()
{
    delete ui;
}

Node* Window::getRoot()
{
	return this->root;
}

SceneGraph* Window::getCurrentSceneGraph() {
	return this->currentScene;
}


void Window::setupTreeView(Node* n, QStandardItem* row) {

	QStandardItem* qItem = new QStandardItem(QString::fromStdString(n->name));
	qItem->setData(QVariant::fromValue(n));
	row->appendRow(qItem);
	for (std::list<Node*>::const_iterator it = n->getChildren()->cbegin(); it != n->getChildren()->end(); ++it) {
		setupTreeView((*it), qItem);
	}
}

void Window::setupListView(Node* n) {

	using namespace std;

	std::vector <Node*> sortedVector;

	/*  example to display twitter account names on the ranked list 
	
	Node* a = new Node("KremlinRussia_E");
	a->strength = 9;
	sortedVector.push_back(a);
	Node* b = new Node("kheadman");
	b->strength = 7;
	sortedVector.push_back(b);
	Node* c = new Node("VRSoloviev");
	c->strength = 4;
	sortedVector.push_back(c);
	Node* d = new Node("JustinWilliams");
	d->strength = 3;
	sortedVector.push_back(d);
	Node* e = new Node("MedvedevRussiaE");
	e->strength = 1;
	sortedVector.push_back(e);

	*/

	int length = sortedVector.size();
	for (int i = 0; i < length; i++) {

		int v = sortedVector[i]->strength;
		std::string ss = std::to_string(v) +"    " + sortedVector[i]->name;

		const char * c = ss.c_str();

		ui->listWidget->addItem(c);
	}
}

//sorts all the names of the node according to strength
std::vector <Node*> Window::sortStringNames(Node* n) {

	using namespace std;

	std::vector <Node*> nodes;
	for (std::list<Node*>::const_iterator it = n->getChildren()->cbegin(); it != n->getChildren()->end(); ++it) {
		
		nodes.push_back((*it));
	}

	Node* temp;
	int len = nodes.size();

	for(int i=0; i<=len;i++)
	{
		for(int j=0; j<=len-i;j++)
		{
			if(nodes[j]->strength > nodes[j+1]->strength)
			{
				temp = nodes[j];
				nodes[j] = nodes[j+1];
				nodes[j+1] = temp;
			}
		}
	}
	return nodes;

}

Node* Window::readTextFile() {

	using namespace std;
	string str;
	const int SIZE = 5;
	std::string wordy[SIZE];
	std::string words2[SIZE];


	// important! Looks at this text file and gets the data from here
	ifstream myfile("tweeters.txt");

	Node* r = new Node("FriendLevel1");
	Node* t = new Node("FriendLevel2");
	//Node* s = new Node("FriendLevel3");
	
	std::string hashes = "#####";
	std::string stars = "***";

	//for (int i = 0; (myfile >> str) && (i < SIZE); ++i) // Will read up to eof() and stop at every
	int i = 0;
	int offset;

	while(myfile>>str && myfile.good())
		{

			if (str == stars) {

				while (str == stars) {
					myfile >> str;
					Node* q = new Node(str);
					t->addChild(q);

					myfile >> str;
					if (str == hashes) {

						//int j = 0;
						myfile >> str;
						ofstream file;
						std::string fname = "tweetData" + std::to_string(i);
						std::string textFileN = fname + ".txt";
						file.open(textFileN);

						while (!(str == hashes)) {
							file << str;
							file << " ";
							myfile >> str;
						}
						q->setTextFileName(textFileN);
						file.close();
					}			
				r->addChild(t);
				  }
			    }		
				else {
					Node* q = new Node(str);
					r->addChild(q);
					//checks if there are #####
					//if ((offset = str.find(hashes, 0)) != string::npos) {
					/***check strength***
					***
					myfile >> str;
					if (str == stars) {
						myfile >> str;
						int value = atoi(str.c_str());
						q->strength = value;
					}
					**/
					myfile >> str;
					if (str == hashes) {
						//int j = 0;
						myfile >> str;
						ofstream file;
						std::string fname = "tweetData" + std::to_string(i);
						std::string textFileN = fname + ".txt";
						file.open(textFileN);

						while (!(str == hashes)) {

							file << str;
							file << " ";
							myfile >> str;
						}

						q->setTextFileName(textFileN);
						file.close();

					}
				}

			i++;
			//adds user to friend level1
			//r->addChild(q);
		}
		myfile.close();

	//ui->treeView->update();
	return r;
}

void Window::keyPressEvent(QKeyEvent *e)
// If the user hits esc, close the program. 
// can add other keyPressEvents
{
	if (e->key() == Qt::Key_Escape){
		close();
	}
    else
        QWidget::keyPressEvent(e);
}

// This methods automatically gets called when a different item is selected in the treeView.
// It is in a slot of this class and connected to a signal in the constructor of this class. 
void Window::on_treeView_currentItemChanged(const QItemSelection &selected, const QItemSelection &deselected)  
{
	Node* d;

	QModelIndex index;
	QModelIndexList items = selected.indexes(); // It is possible to select more than one item. 

	foreach(index, items) {				// For each item selected look at the data. 
		d = index.data(Qt::UserRole + 1).value<Node*>();
	}

	currentNode = d; // keep a pointer to the node that corresponds to the currently selected tree item. Makes things easier. 
	
	//get the contents of current node and open the textfile and display on textEditor
	std::string str = d->textFileName;
	displayTweets(str);

}

//displays the tweets into the text box
void Window::displayTweets(std::string str)
{
	const char * c = str.c_str();
	QFile myFile(c);
	myFile.open(QIODevice::ReadOnly);
	QTextStream textStream(&myFile);
	QString line = textStream.readAll();
	myFile.close();
	ui->textEdit->setPlainText(line);
	//ui->textEdit->setPlainText(str);
}

// implements searching through twitter once the search button is pressed
void Window::search_button() {
	
	QString user_data = ui->user_text->text();
	QString keyword_data = ui->keyword_text->text();
	using namespace std;

	std::string user = user_data.toLocal8Bit().constData();
	std::string keywords = keyword_data.toLocal8Bit().constData();

	ofstream file;
	file.open("user_keyword.txt");

	file << "python ";
	file << "runner.py ";
	file << user;
	file << " ";
	file << keywords;

	//from here we get the data then implement a tree view

	ui->treeView->update();	//updates tree view
}

// creates friends and enters them unto the tree
Node* Window::createFriend() {

	//model->clear();

	Node* r = readTextFile();

	return r;
}


