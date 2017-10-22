#  -*- coding: utf-8 -*-

import tweepy

from unicodedata import normalize

import codecs

consumer_key = "WPWjWNXmpNHNpcSqEs7n8swV4"
consumer_secret = "PehUYnIYP8AZj2A5Mgyal95Fw7uQ1PzhKFd581ZVkUf90jTHbc"
access_token = "18453520-6TMKtCuSgUlQXwi7ahNt48h4QrzJkwoeN92MWm9IC"
access_token_secret = "HlKsk3Dai9CUv3x4UeQm1UcKwVoLESWfAxlcdPfmPizAW"

auth = tweepy.OAuthHandler(consumer_key, consumer_secret)
auth.set_access_token(access_token, access_token_secret)

api = tweepy.API(auth)

# user = api.get_user('twitter')

# friends = user.friends()

# api.statuses_lookup(friends)






def getUser(userHandle):
    return api.get_user(userHandle)

def getUserFriends(userHandle):
    user = getUser(userHandle)
    friends = user.friends()
    ret = []
    for friend in friends:
        ret.append(friend.screen_name)
    return ret

#returns list of tweets
def getUserTimeline(userHandle):
    tweets = api.user_timeline(userHandle)
    ret = []
    for tweet in tweets:
        ret.append(tweet.text)
    return ret

def appendToFile(filename, users):
    handle = users.split(',')[-1]
    tweets = getUserTimeline(handle)
    with codecs.open(filename, 'a', encoding='utf8') as af:
        for tweet in tweets:
            af.write(users + "<###>" + tweet + "\n")
    return

userSet = set()
levels = 2

filename = "sergio.txt"
zero = 'lifeguardsergio'
zero = [zero]

def recursion(friends, fileout, userSet):
    friendsfriends = []
    for friend in friends:
        handle = friend.split(',')[-1]
        if handle not in userSet:
            appendToFile(fileout, friend)
            userSet.add(handle)
            fList = getUserFriends(handle)
            for f in fList:
                friendsfriends.append(friend + "," + f)
    return friendsfriends

ty = recursion(zero, filename, userSet)
ty = recursion(ty, filename,userSet)
    


# for tweet in public_tweets:
#     print (tweet.text)

# user = api.get_user('twitter')


# for friend in user.friends():
#    print friend.screen_name