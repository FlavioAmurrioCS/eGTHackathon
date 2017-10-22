//Demonstrating connecting the Qt Tree View widget to another class (like a scene graph)

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "window.h"
#include "ui_window.h"
#include "node.h"
//#include "myglwidget.h"
#include "SceneGraph.h"




// The code is all put here for ease of explanation. Your node classes would be in a separate .cpp file 
// Some of the other code may be not be in the window constructor. Do a better code design.

Q_DECLARE_METATYPE(Node*);  // Tell Qt that Data is a type.
//Q_DECLARE_METATYPE(SceneGraph*);

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

	// You should be able to traverse your scene graph and set these up as you traverse or you can do it as you create your scene graph. 
	// Also, realize you will need to create and delete these items when you create and delete nodes in your scene graph
	//SceneGraph* scene = new SceneGraph();

	//Node* d = new Node("Root");		// Create a new node
	//QStandardItem* rootItem = new QStandardItem(QString::fromStdString(d->name));	// These would correspond to your scene graph nodes
	//rootItem->setData(QVariant::fromValue(d)); // Store a pointer to data in the tree item so that you can retrieve it when an item is selected. 
	Node* d = new Node("Root_User");
	QStandardItem* rootItem = new QStandardItem(QString::fromStdString(d->name));	// These would correspond to your scene graph nodes
	rootItem->setData(QVariant::fromValue(d));
	model->appendRow(rootItem);

	


	//Node* animalRoot = createAnimal();
	Node* friendRoot = createFriend();
	setupTreeView(friendRoot, rootItem);  // sets up treeview using QStandardItem
	
	setupListView(friendRoot);
	
	
	//ui->listView->expandAll();
	//ui->myGLWidget->glScene->root = animalRoot; //sets MyGlWidget root node to torso node
	//currentScene = ui->myGLWidget->glScene;


	//setupTreeView(animalRoot, rootItem);  // sets up treeview using QStandardItem
	//ui->myGLWidget->glScene->root = animalRoot; //sets MyGlWidget root node to torso node
	//currentScene = ui->myGLWidget->glScene;

	ui->treeView->setModel(model); // ui needs to include treeView, so create one in Qt Creator and make sure it is named treeView
								   // in the ui, I also made the header of the treeView not visible. 
	ui->treeView->expandAll();	   // show all of the items at all levels 

	// When a user selects an item in the treeView have a signal sent to a method in this class, on_treeView_currentItemChanged
	connect(ui->treeView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &Window::on_treeView_currentItemChanged);

	// Set up initial sliders values
	//ui->xTransSlider->setVisible(FALSE);
	//ui->yTransSlider->setVisible(FALSE);
	//ui->xTransSlider->setMinimum(-10); ui->xTransSlider->setMaximum(10); ui->xTransSlider->setSingleStep(1); // These are just sample to show how to do it. You decide on appropriate values. To use floats instead of ints, divide the values the sliders return by 100.0
	//ui->yTransSlider->setMinimum(-10); ui->yTransSlider->setMaximum(10); ui->yTransSlider->setSingleStep(1);
	//scale slider values
	//ui->xScaleSlider->setVisible(FALSE);
	//ui->yScaleSlider->setVisible(FALSE);
	//ui->xScaleSlider->setMinimum(-10); ui->xScaleSlider->setMaximum(10); ui->xScaleSlider->setSingleStep(1); // These are just sample to show how to do it. You decide on appropriate values. To use floats instead of ints, divide the values the sliders return by 100.0
	//ui->yScaleSlider->setMinimum(-10); ui->yScaleSlider->setMaximum(10); ui->yScaleSlider->setSingleStep(1);
	//rotation dial values
	//ui->rotationDial->setVisible(FALSE);
	//ui->rotationDial->setMinimum(-180); ui->rotationDial->setMaximum(180); ui->rotationDial->setSingleStep(1);
	//animation scroll bar values
	//ui->animationScrollBar->setVisible(FALSE);
	//ui->animationScrollBar->setMinimum(0); ui->animationScrollBar->setMaximum(0); ui->animationScrollBar->setSingleStep(1);

	// When a user moves a slider/dialer, update the label value to show it
	//connect(ui->xTransSlider, &QSlider::valueChanged, this, &Window::on_xTransSlider_valueChanged);
	//connect(ui->yTransSlider, &QSlider::valueChanged, this, &Window::on_yTransSlider_valueChanged);
	//connect(ui->xScaleSlider, &QSlider::valueChanged, this, &Window::on_xScaleSlider_valueChanged);
	//connect(ui->yScaleSlider, &QSlider::valueChanged, this, &Window::on_yScaleSlider_valueChanged);
	//connect(ui->rotationDial, &QDial::valueChanged, this, &Window::on_rotateDialer_valueChanged);
	// in animation mode
	//connect(ui->animationScrollBar, &QScrollBar::valueChanged, this, &Window::on_animation_valueChanged);

	//when user presses a button in modeling mode
	connect(ui->searchButton, &QPushButton::clicked, this, &Window::search_button);
	
	//connect(ui->addButton, &QPushButton::clicked, this, &Window::add_Node);
	//connect(ui->removeButton, &QPushButton::clicked, this, &Window::remove_Node);
	//connect(ui->magicButton, &QPushButton::clicked, this, &Window::restartAnimal);
	//connect(ui->colorPicker, &QPushButton::clicked, this, &Window::color_Box);
	//connect(ui->saveFrameButton, &QPushButton::clicked, this, &Window::save_Frame);
	//connect(ui->numberFramesButton, &QPushButton::clicked, this, &Window::on_number_frames);

	//when user presses a button in animation mode
	//connect(ui->playButton, &QPushButton::clicked, this, &Window::play_Animation);
	//connect(ui->backwardButton, &QPushButton::clicked, this, &Window::go_Backward);
	//connect(ui->fowardButton, &QPushButton::clicked, this, &Window::go_Foward);
	//connect(ui->animateButton, &QPushButton::clicked, this, &Window::save_Animation);


	//timer for playing animation
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(animate()));
	
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

	//std::list<Node*> children;
	using namespace std;
	//string nodeNames[] = {"hi", "due", "false", "cold"};

	//sorted vector
	

	//vector <string> nodeNames;
	//nodeNames.push_back("blue");
	//nodeNames.push_back("red");



	//sort list by strength
	//QListWidgetItem *newItem = new QListWidgetItem;
	//newItem->setText(itemText);
	//ui->listView->insertItem(row, newItem);
	//ui->listView->
	//ui->listView->update();
	//QListWidgetItem item =

	//std::string str = "Hello";

	//ui->listWidget->addItem("Hello");

	/****
	//Call sortStringNames()
	*/
	//std::vector <Node*> sortedVector = sortStringNames(n);
	std::vector <Node*> sortedVector;
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

	int length = sortedVector.size();
	for (int i = 0; i < length; i++) {

		int v = sortedVector[i]->strength;
		std::string ss = std::to_string(v) +"    " + sortedVector[i]->name;

		const char * c = ss.c_str();

		//const char * c = (sortedVector[i]->name).c_str();
		//convert int to string
		//int value = atoi((sortedVector[i]->strength).c_str());
		
		//q->strength = value;

		ui->listWidget->addItem(c);
	}
}

//sorts all the names of the node according to strength
std::vector <Node*> Window::sortStringNames(Node* n) {

	using namespace std;
	//std::vector <int> r;
	//std::vector <string> str;
	std::vector <Node*> nodes;
	for (std::list<Node*>::const_iterator it = n->getChildren()->cbegin(); it != n->getChildren()->end(); ++it) {
		//setupTreeView((*it), qItem);
		nodes.push_back((*it));
	}

	//can do a for loop of all children of node n
	//r.push_back(n->name);
	

	
	//Node* nodeArray[nodes.size];

	//for (int x = 0; x < nodes.size; x++) {
		//nodeArray[x] = nodes[x];
	//}
	//Sorts array by strength
	//for(int i=0;i<=nodes.size();i++)
	//{
	//	cin>>a[i];
	//}
	//cout<<"\nData before sorting: ";
	//for(int j=0;j<nodes.size;j++)
	//{
	//cout<<a[j];
	//}
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
	 //cout<<"\nData after sorting: ";
	


}

Node* Window::readTextFile() {

	using namespace std;
	//string line;
	string str;
	const int SIZE = 5;
	std::string wordy[SIZE];
	std::string words2[SIZE];
	//std::vector <std::string> words; // Vector to hold our words we read in.

	ifstream myfile("tweeters.txt");

	Node* r = new Node("FriendLevel1");
	Node* t = new Node("FriendLevel2");
	//Node* s = new Node("FriendLevel3");
	
	//if (!myfile.is_open())
	//{
	std::string hashes = "#####";
	std::string stars = "***";

		//for (int i = 0; (myfile >> str) && (i < SIZE); ++i) // Will read up to eof() and stop at every
	int i = 0;
	int offset;

	while(myfile>>str && myfile.good())
		{
			//i = i + 1;
			//wordy[i] = str;

			
			//r->addChild(q);
			//if (myfile >> str != hashes) {

			//}
			//myfile >> str;
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
						//store whatever in here in a textfile
						//ofstream file;


						//myfile << "Writing this to a file.\n";
						//while () {
						//file << str;
						//}
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
						//store whatever in here in a textfile
						//ofstream file;


						//myfile << "Writing this to a file.\n";
						//while () {
							//file << str;
						//}
						q->setTextFileName(textFileN);
						file.close();

						//if (str == hashes) {


							//myfile.close();
						//j = 1;



					}
				}
			//else if (str == strength) {

				//int value = atoi(str.c_str());
				//q->strength = value;

			//}

			/*else {
				//goes to next level of friends

			}*/

			//words.push_back(str);
			//cout << word << '\n';
			//Node* t = new Node(word);
			//r->addChild(t);
			i++;


			//adds user to friend level1
			//r->addChild(q);
		}
		myfile.close();
		/*
		for (int i = 0; i < SIZE; i=i+2) { //++i) {
			//std::cout << words.at(i) << std::endl; // Print so I can see this all worked!
			//Node* p = new Node("Level3");
			Node* w = new Node(wordy[i]);
			r->addChild(w);

			if (i + 1 < SIZE) {
				Node* q = new Node(wordy[i+1]);
				t->addChild(q);
				r->addChild(t);
			}
			//Node* q = new Node(wordy[i+1]);
			//Node* t = new Node("FriendLevel2");
			//t->addChild(q);
			
			
			
			if (i == 0) {
				//Node* e = new Node(wordy[i]);
				t->addChild(w);
				//r->addChild(t);
			}
			//else if (i % 3 == 0) {
				//Node* t = new Node(wordy[i]);
				//t->addChild(t);
			//}
			else {
				//Node* w = new Node(wordy[i]);
				r->addChild(w);
			}
			

		}
		*/
	//}
	/*
	if (myfile.is_open())
	{
	while (getline(myfile, line))
	{
		//cout << line << '\n';
		Node* t = new Node(line);
		r->addChild(t);

	}
	

	myfile.close();
	}
	*/
	//else cout << "Unable to open file";

	//ui->treeView->update();
	return r;
}

void Window::keyPressEvent(QKeyEvent *e)
// If the user hits esc, close the program. 
//add other keyPressEvents
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
		//std::cout << "My data is " << d->x << ", " << d->y << std::endl; // Does not actually do anything because there is no console.
	}

	currentNode = d; // keep a pointer to the node that corresponds to the currently selected tree item. Makes things easier. 
	
	//get the contents of current node and open the textfile and display on textEditor
	std::string str = d->textFileName;
	displayTweets(str);




	/*
	ui->xTransSlider->setValue(d->transX);     // Set the values of the slides to what is currently in the node
	ui->yTransSlider->setValue(d->transY);
	ui->xTransSlideLabel->setNum(d->transX);		// Show the value in the label for the x slider
	ui->yTransSlideLabel->setNum(d->transY);     // Show the value in the label for the y slider

	ui->xScaleSlider->setValue(d->scaleX);     // Set the values of the slides to what is currently in the node
	ui->yScaleSlider->setValue(d->scaleY);
	ui->xScaleSliderLabel->setNum(d->scaleX);		// Show the value in the label for the x slider
	ui->yScaleSliderLabel->setNum(d->scaleY);

	ui->rotationDial->setValue(d->rot);
	ui->rotationDialLabel->setNum(d->rot);

	//animation widget
	ui->animationScrollBar->setValue(0);
	ui->animationLabel->setNum(0);

	ui->xTransSlider->setVisible(TRUE);   // Make the sliders visible
	ui->yTransSlider->setVisible(TRUE);
	ui->xScaleSlider->setVisible(TRUE);
	ui->yScaleSlider->setVisible(TRUE);
	ui->rotationDial->setVisible(TRUE);
	ui->animationScrollBar->setVisible(TRUE);
	*/
}

void Window::displayTweets(std::string str)
{
	
	//std::string d = ":/" + str;
	//QFile s = d;
	//QString s = str;

	//QFileDialog *filedlg;
	//QString fname;
	//filedlg->getOpenFileName(filedlg);

	//QString fname = QFileDialog::getOpenFileName("tweetsdata.txt");

	//QFile myFile("tweetData1.txt");
	//std::string str;
	const char * c = str.c_str();

	QFile myFile(c);
	myFile.open(QIODevice::ReadOnly);
	QTextStream textStream(&myFile);
	QString line = textStream.readAll();
	myFile.close();
	ui->textEdit->setPlainText(line);
	//ui->textEdit->setPlainText(str);
}




void Window::search_button() {
	//searches and updates tree view according to the searched user and keyword
	//gets user name
	//gets keyword

	//char username[] = "";
	//char keyword[] = "";

	
	

	QString user_data = ui->user_text->text();
	QString keyword_data = ui->keyword_text->text();
	using namespace std;

	std::string user = user_data.toLocal8Bit().constData();
	std::string keywords = keyword_data.toLocal8Bit().constData();


	//QProcess p;
	//QStringList params;
	//params << "calvin.py -" + user + " " + keyword;
	//params << "calvin.py ovi8 some keywords";
	//p.start("python", params);
	//p.waitForFinished(-1);
	
	//QString p_stdout = p.readAll();

	//ui->listWidget->setCurrentRow;


	ofstream file;
	file.open("user_keyword.txt");

	//std::string fname = "tweetData" + std::to_string(i);
	//std::string textFileN = fname + ".txt";
	
	file << "python ";
	file << "runner.py ";
	file << user;
	file << " ";
	file << keywords;

	

	//std::cout << user_data.toLocal8Bit() << std::endl;
	//std::cout << keyword_data.toLocal8Bit().constData() << std::endl;
	//std::cout << user_data;
	//std::cout << keyword_data;



	//QtString::fromStdString(ui->user_text->text());


	//from here we get the data then implement a tree view

	

	ui->treeView->update();	//updates tree view
}


/*

void Window::save_Animation() {
	//saves the screen output for the series of key frames in animation mode
	SceneGraph* newScene = new SceneGraph();
	newScene->setRoot(this->currentScene->getRoot());
	this->sceneList->push_back(newScene);
	QImage image = ui->myGLWidget->grabFrameBuffer();
	image.save("frame.jpg");
	restartAnimal();
}

void Window::save_Frame() { 
	//saves current frame in modeling mode
	//SceneGraph* nextScene = new SceneGraph(*currentScene);

	SceneGraph* newScene = new SceneGraph();
	newScene->root = currentScene->getRoot();
	this->sceneList->push_back(newScene);

	restartAnimal();  
}



void Window::transform(Node* current) {
	// Create a scale matrix from the x and y sliders' values 
	mat3 scale = mat3::scale2D(current->scaleX, current->scaleY);
	mat3 rotate = mat3::rotation2D(current->rot);
	mat3 translate = mat3::translation2D(current->transX, current->transY);
	current->setTransformation(scale, rotate, translate);
}




void Window::add_Node() {

	Node* n = new Node(getNewName());
	n->setPolyTrue();
	n->shape->setColor(.5, .5, 1);
	n->setTransformation(mat3::identity(), mat3::identity(), mat3::identity());
	std::list <vec3> *v = new std::list<vec3>();
	v->push_back(vec3(-1, -1, 1));
	v->push_back(vec3(-1, 1, 1));
	v->push_back(vec3(1, 1, 1));
	v->push_back(vec3(1, -1, 1));
	n->shape->setVertices(v);

	QModelIndex id = ui->treeView->currentIndex();

	QStandardItem* item1 = new QStandardItem(QString::fromStdString(n->name));	// These would correspond to your scene graph nodes
	item1->setData(QVariant::fromValue(n)); // Store a pointer to data in the tree item so that you can retrieve it when an item is selected. 
	model->appendRow(item1);
	//setupTreeView(currentNode, item);
	
	currentNode->addChild(n);
	//ui->treeView->model()->insertRow(id.row(), id.parent());

	ui->treeView->update();	//updates tree view

	ui->myGLWidget->update();
}

void Window::remove_Node() {
	
	QModelIndex id = ui->treeView->currentIndex();
	currentNode->parent->removeNode(currentNode);
	ui->treeView->model()->removeRow(id.row(), id.parent());
	//currentNode->removeNode(currentNode);
	
	ui->treeView->update();
	ui->myGLWidget->update();
}
*/
Node* Window::createFriend() {

	//model->clear();

	Node* r = readTextFile();

	//Node* userData = new Node("Sergio");
	/*
	//torso->setPolyTrue();
	//torso->shape->setColor(.5, 1, .5);
	//torso->transX = 0;
	//torso->transY = 0;
	torso->setTransformation(mat3::identity(), mat3::identity(), mat3::identity());
	std::list <vec3> *v = new std::list<vec3>();
	v->push_back(vec3(-4, -2, 1));
	v->push_back(vec3(-4, 2, 1));
	v->push_back(vec3(4, 2, 1));
	v->push_back(vec3(4, -2, 1));
	torso->shape->setVertices(v);
	*/

	//Node* friendData2 = new Node("Flavio");
	/*
	head->setPolyTrue();
	head->shape->setColor(.4, 1, .8);
	head->transX = 6;
	head->transY = 3;
	head->setTransformation(mat3::identity(), mat3::identity(), mat3::translation2D(head->transX, head->transY));
	std::list <vec3> *h = new std::list<vec3>();
	h->push_back(vec3(-2, -1, 1));
	h->push_back(vec3(-2, 2, 1));
	h->push_back(vec3(0, 3, 1));
	h->push_back(vec3(2, 2, 1));
	h->push_back(vec3(2, -1, 1));
	head->shape->setVertices(h);
	*/

	//Node* friendData3 = new Node("Bob");
	/*
	leftEar->setPolyTrue();
	leftEar->shape->setColor(.4, .4, .6);
	leftEar->transX = -1;
	leftEar->transY = 2;
	leftEar->setTransformation(mat3::identity(), mat3::identity(), mat3::translation2D(leftEar->transX, leftEar->transY));
	std::list <vec3> *e = new std::list<vec3>();
	e->push_back(vec3(-1, 0, 1));
	e->push_back(vec3(.5, .5, 1));
	e->push_back(vec3(-.5, 2, 1));
	leftEar->shape->setVertices(e);
	*/
	//userData->addChild(friendData2);
	//friendData2->addChild(friendData3);
	return r;
}


