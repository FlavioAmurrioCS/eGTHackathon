# TwitterConnections

      This windows application provides a simple way to search and analyse a network of twitter people.

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

- On top of PreProcessing.py can find the libraries we imported.
      - This file contains the functions we used in the runner.py     
      - Google translate was downloaded from here https://pypi.python.org/pypi/googletrans
      - NLTK - http://www.Tweepy - nltk.org/
      - Tweepy - http://www.tweepy.org/
      - In order to use the Twitter API, you should generate your own API key from the Twitter developer account
- Runner.py contains the main logic of the process, Here is a transcript of the explanation of how it works:
Inline image 1

- As for the GUI,  we used Visual Studio 2015. After installing it, we installed Qt. Here are the instructions we used for when we took the class. There may be a new version of the software so it may be a bit different. 
Inline image 2
- After installation, you should be able to open the project from within Visual Studio.
- Since the GUI and the preprocessing were done separately, you have to manually place the python output into the folder where GUI is located(Or run the python script from inside the project folder). Last time I checked I think all the necessary libraries are available online for a Java-only implementation.