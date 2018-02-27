# TwitterConnections

This windows application provides a simple way to search and analyse a network of twitter people. Here is the **[presentation](./presentation.pdf)** of the project. An android version of this concept is underdevelopment at <https://github.com/FlavioAmurrioCS/TwitSet>

## Building it

This project uses both Python and C++.

### Python

1. Download and install the latest version of [Python3](<https://www.python.org/downloads/>).
2. Install the following python libraries with the command in the parenthesis:
      * googletrans 2.2.0 (pip install googletrans)
      * Tweepy (pip install tweepy)
      * nltk (sudo pip install -U nltk)
      * numpy (sudo pip install -U numpy)
      * If the above command don't work on Windows, download the binaries from [this site](https://www.lfd.uci.edu/~gohlke/pythonlibs/) and install using the command **pip install [name of the file]**
3. In order to use tweepy, one needs to get a API key, follow these instructions (from [StackOverFlow](https://stackoverflow.com/a/12335636)):
      * Log into the Twitter Developers section.
      * If you don't already have an account, you can login with your normal Twitter credentials
      * Go to "Create an app"
      * Fill in the details of the application you'll be using to connect with the API
      * Your application name must be unique. If someone else is already using it, you won't be able to register your application until you can think of something that isn't being used.
      * Click on Create your Twitter application
      * Details of your new app will be shown along with your consumer key and consumer secret.
      * If you need access tokens, scroll down and click Create my access token
      * The page will then refresh on the "Details" tab with your new access tokens. You can recreate these at any time if you need to.
4. Once you have the keys/tokens, place it in the PreProcessing.py (consumer_key, consumer_secret, access_token, access_token_secret)

### Visual Studio (C++)

The GUI was built using Visual Studio 2015 and Qt. Install Visual Studio and then install Qt using the following instructions. (There may be a new version of the software so it may be a bit different.)

#### Qt 5.8

Qt is a toolkit for creating Graphical User Interfaces (GUIs).

1. It can be downloaded for free [here](http://download.qt.io/official_releases/online_installers/qtunified-windows-x86-online.exe)
2. Run the downloaded executable to install the software.
      * During the installation process, you’ll be asked to create a Qt login and password. Follow the directions and note it requires a strong password.
      * Use the default settings during installation.
      * Note, it might take a long time to install.
3. Install Qt VS tools for VS 2015.
      * Download it from this [link](http://download.qt.io/official_releases/vsaddin/qt-vs-toolsmsvc2015-2.0.0.vsix)
      * Run the downloaded file.
      * Run Qt 5.8 64 bit for Desktop (MSVC 2015).
      * Add Qt version 5.8 to Visual Studio
4. Open Visual Studio 2015.
5. Click on the Qt VS Tools > Qt Options > Qt Versions menu.
6. Add a version named msvc2015_64 and give it path C:\Qt\5.8\msvc2015_64
7. In the Default Qt/Win version: select the option you just added.

## How To Run It

In order to run this application, we must first run the python code with Runner.py in the following order.

* For initial fetching of data(uandk stands for username and keywords)

      python Runner.py uandk [username] [keywords]

* To search for new keywords from the user's network(This reuses the fetch network from the previous command to avoid too many API calls):

      python Runner.py newkey [keywords]
  * This command will will create a text file (tweetList.txt) that has "username<###>tweet".
  * tweetsList.txt contains the original tweets (ei: "_eglobaltech,billhepworth<###>b'@ChrisMurphyCT, did you really just say having")
  * On the username side, the users are stored in a chain (network path/connections) with the first being the original user and the last one being the user that made the tweet

* Next, we turn the tweetList.txt content into vectors based on their word frequency and store it in vector.txt

      python Runner.py wordfreq
  * vector.txt contains the same tweets but they are processed this time
  * __"\_eglobaltech,billhepworth<###>0<###> brt elonmusk offici verifi first product electr"__
  * In this file, the tweets are store in the following format __usernames<###>score<###>wordVector__
  * wordVector is a representation of the tweet but the words are processed by removing stopwords and stemming them to their linguistic root
  * This helps in improves the performance of future searches for this particular network

Since the GUI and the preprocessing were done separately, after finishing the previous steps, you have to manually place the python output into the folder where GUI is located (Or run the python script from inside the project folder).

### TODO

* [x] Finish [README](./README.md)
* [ ] Refactor code so that everything can be controlled from within the GUI application.
* [ ] Finish Android version prototype

## ***Note: Due to last semester of school, this project will be temporarily on hold.***