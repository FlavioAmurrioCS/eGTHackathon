# TwitterConnections(ReadMe Under Construction)

This windows application provides a simple way to search and analyse a network of twitter people. An android versison of this concept is underdevelopment at <https://github.com/FlavioAmurrioCS/TwitSet>

## Building it

      This project uses both python and c++.

### Python

1. Download and install the latest version of Python3 (<https://www.python.org/downloads/>).
2. Install the following python libraries with the command in the paranthesis:
      * googletrans 2.2.0 (pip install googletrans)
      * Tweepy (pip install tweepy)
      * nltk (sudo pip install -U nltk)
      * numpy (sudo pip install -U numpy)
      * If the above command don't work
3. In order to use tweepy, one needs to get a API key, follow these instructions (from <https://stackoverflow.com/a/12335636>):
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

* As for the GUI,  we used Visual Studio 2015. After installing it, we installed Qt. Here are the instructions we used for when we took the class. There may be a new version of the software so it may be a bit different.

        Qt 5.8
        a. It is a toolkit for creating Graphical User Interfaces (GUIs).
        b. It can be downloaded for free here: http://download.qt.io/official_releases/online_installers/qtunified-windows-x86-online.exe
        c. Run the downloaded executable to install the software.
        i. During the installation process, you’ll be asked to create a Qt login and password. Follow
        the directions and note it requires a strong password.
        ii. Use the default settings during installation.
        iii. Note, it might take a long time to install.
        d. Install Qt VS tools for VS 2015.
        i. It can be downloaded from: http://download.qt.io/official_releases/vsaddin/qt-vs-toolsmsvc2015-2.0.0.vsix
        ii. Run the downloaded file.
        iii. Run Qt 5.8 64 bit for Desktop (MSVC 2015).
        iv. Add Qt version 5.8 to Visual Studio
        1. Open Visual Studio 2015.
        2. Click on the Qt VS Tools > Qt Options > Qt Versions menu.3. Add a version named msvc2015_64 and give it path C:\Qt\5.8\msvc2015_64
        4. In the Default Qt/Win version: select the option you just added.

## How To Run It

* Runner.py contains the main logic of the process, Here is a transcript of the explanation of how it works:

        the command is
        python Runner.py uandk [username] [keywords]
        for initial fetching of data
        python Runner.py newkey [keywords]
        to search for new keywords from the user
        python Runner.py wordfreq
        will create a text file that has the word count for each word
        tweetsList.txt contains the original tweets
        ei
        _eglobaltech,billhepworth<###>b'@ChrisMurphyCT, did you really just say having
        split at "<###>" to get user and comment and then split user at ',' to get users chain
        _gloabaltech is patient zero
        vector.txt contains the same tweet but they are processed this time
        _eglobaltech,billhepworth<###>0<###> brt elonmusk offici verifi first product electr
        first is the user name then the value of the tweet and then the process tweet
        i use that to search the keywords faster for future search
        both vector.txt and tweetList.txt have the same information on the same line so you should be able to map them easily

* After installation, you should be able to open the project from within Visual Studio.
* Since the GUI and the preprocessing were done separately, you have to manually place the python output into the folder where GUI is located(Or run the python script from inside the project folder). Last time I checked I think all the necessary libraries are available online for a Java-only implementation.