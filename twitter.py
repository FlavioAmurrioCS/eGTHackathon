import tweepy
from PyDictionary import PyDictionary
from nltk.stem import PorterStemmer
from nltk.tokenize import sent_tokenize, word_tokenize


consumer_key = "WPWjWNXmpNHNpcSqEs7n8swV4"
consumer_secret = "PehUYnIYP8AZj2A5Mgyal95Fw7uQ1PzhKFd581ZVkUf90jTHbc"
access_token = "18453520-6TMKtCuSgUlQXwi7ahNt48h4QrzJkwoeN92MWm9IC"
access_token_secret = "HlKsk3Dai9CUv3x4UeQm1UcKwVoLESWfAxlcdPfmPizAW"

auth = tweepy.OAuthHandler(consumer_key, consumer_secret)
auth.set_access_token(access_token, access_token_secret)

api = tweepy.API(auth)

public_tweets = api.home_timeline()
for tweet in public_tweets:
    print (tweet.text)

user = api.get_user('twitter')

print user.screen_name
print user.followers_count
for friend in user.friends():
   print friend.screen_name


def getUser(userHandle):
    return api.get_user(userHandle)

def getUserFriends(userHandle):
    user = getUser(userHandle)
    return user.friends()

def getUserTimeline(userHandle):
    return api.user_timeline(userHandle)
