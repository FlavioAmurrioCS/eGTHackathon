from googletrans import Translator

from nltk.tokenize import sent_tokenize, word_tokenize
from nltk.corpus import stopwords

from PyDictionary import PyDictionary as dict

from nltk.stem import PorterStemmer

from time import time

import nltk 
from nltk.corpus import wordnet

import tweepy

import codecs

############################### Twitter ###############################

consumer_key = "WPWjWNXmpNHNpcSqEs7n8swV4"
consumer_secret = "PehUYnIYP8AZj2A5Mgyal95Fw7uQ1PzhKFd581ZVkUf90jTHbc"
access_token = "18453520-6TMKtCuSgUlQXwi7ahNt48h4QrzJkwoeN92MWm9IC"
access_token_secret = "HlKsk3Dai9CUv3x4UeQm1UcKwVoLESWfAxlcdPfmPizAW"

auth = tweepy.OAuthHandler(consumer_key, consumer_secret)
auth.set_access_token(access_token, access_token_secret)

api = tweepy.API(auth)

def getUser(userHandle):
    return api.get_user(userHandle)

def getUserFriends(userHandle):
    user = getUser(userHandle)
    friends = user.friends()
    ret = []
    for friend in friends:
        ret.append(friend.screen_name)
    return ret

def getUserTimeline(userHandle):
    tweets = api.user_timeline(userHandle)
    ret = []
    for tweet in tweets:
        ret.append(tweet.text)
    return ret



############################### Extra Helpers ###############################
def tokenToString(tokens):
    return "".join(" " + str(x) for x in tokens)

def stringToToken(line):
    return word_tokenize(line)

############################### Translation ###############################
translator = Translator()

def translate(line):
    return (translator.translate(line)).text    

############################### StopWords ###############################
stop_words = set(stopwords.words('english'))

def stopRemToken(word_tokens):
    filtered_sentence = [w for w in word_tokens if not w in stop_words]
    return filtered_sentence

def stopRemSent(line):
    word_tokens = stringToToken(line)
    return stopRemToken(word_tokens)
    

############################### Synonyms ###############################
def synom(word):
    return dict.synonym(word)

############################### Stemmer ###############################
ps = PorterStemmer()

def stemToken(tokens):
    ret = []
    for token in tokens:
        ret.append(ps.stem(token))
    return ret

def stemSent(line):
    tokens = stringToToken(line)
    return stemToken(tokens)

def remSp(word):
    return ''.join(e for e in word if e.isalpha())

def remSpec(words_token):
    ret = []
    for word in words_token:
        temp = remSp(word)
        length = len(temp)
        if length > 1:
            ret.append(temp)            
    return ret

############################### Combined Tools ###############################

#returns string of the process 
def clean(sentence):
    line = translate(sentence)
    line = str.lower(line)
    tokens = stringToToken(line)
    tokens = stopRemToken(tokens)
    tokens = stemToken(tokens)
    tokens = remSpec(tokens)
    return tokens

def tokenToSet(tokens):
    k = set()
    for token in tokens:
        k.add(token)
    return k


def readfile(filename):
    with open(filename, 'r') as f:
        lines = f.readlines()
        with open(filename + "-output", 'w') as w:
            for line in lines:
                w.write(clean(line) + "\n")

def tokenToHashTable(tokens):
    D = {}    
    for token in tokens:
        if token in D:
            D[token] = D[token] + 1
        else:
            D[token] = 1
    return D

def jaccardIndex(s1, s2):
    u = s1.union(s2)
    i = s1.intersection(s2)
    return len(i)/len(u)

def commonTerm(s1, s2):
    return s1.union(s2)

def readSergioFile(input, output, keywords):
    kSet = tokenToSet(clean(keywords))
    lines = []
    with open(output, 'w') as wf:
        with open(input, 'r') as rf:
            lines = rf.readlines()
            for line in lines:
                sp = line.split("<###>")
                cToken = clean(sp[1])
                outStr = sp[0] + "<###>" + tokenToString(cToken)
                # s1 = tokenToSet(cToken)
                # ct = commonTerm(s1, kSet)
                ct = keyCount(cToken, kSet)
                outStr = sp[0] + "<###>" + str(ct) + "<###>" + tokenToString(cToken) + "\n"
                wf.write(outStr)
    return

def keyCount(tokens, kSet):
    count = 0
    for token in tokens:
        if token in kSet:
            count+=1
    return count

def readNewSergio(input, output, kSet):
    lines = []
    with codecs.open(input, 'r', encoding='utf8') as rf:
        with open(output, 'w') as wf:
            lines = rf.readlines()
            for line in lines:
                line = line.encode('ascii','ignore')
                line = str(line)
                token = clean(line)
                value = keyCount(token, kSet)
                wf.write(str(value) + "\n")
                print(str(value))
    return


def readFlavioFile(input, output, kSet):
    lines = []
    with open(input,'r') as rf:
        lines = rf.readlines()
    with open(output, 'w') as wf:
        for line in lines:
            sp = line.split("###")
            parent = sp[0]
            sp = sp[1].split(",,,")
            token = stringToToken(sp[0])
            s1 = tokenToSet(token)
            value = s1.union(kSet)
    return

def appendToFile(filename, users):
    handle = users.split(',')[-1]
    tweets = getUserTimeline(handle)
    with open(filename, 'a') as af:
        for tweet in tweets:
            out = tweet.encode('ascii','ignore')
            out = str(out)
            out = out.replace('\n', ' ')
            af.write(users + "<###>" + out + "\n")
    return

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

def recursionLevel2(friends, fileout, userSet):
    for friend in friends:
        handle = friend.split(',')[-1]
        if handle not in userSet:
            appendToFile(fileout, friend)
            userSet.add(handle)
    return

def newKeyword(input, keywords):
    kSet = tokenToSet(clean(keywords))
    lines = []
    with open(input, 'r') as rf:
        lines = rf.readlines()
    with open(input, 'w') as wf:
        for line in lines:
            sect = line.split("<###>")
            username = sect[0]
            score = sect[1]
            comment = sect[-1]
            token = word_tokenize(comment)
            score = keyCount(token, kSet)
            outStr = username + "<###>" + str(score) + "<###>" + comment
            wf.write(outStr)
    return


outFile = 'tweetsList.txt'
vectFile = 'vector.txt'

zero = word_tokenize('_eglobaltech')

userSet = set()

nlist = recursion(zero, outFile, userSet)
# nlist = recursion(nList, outFile, userSet)
recursionLevel2(nlist, outFile, userSet)

keywords = 'internet technology security'

readSergioFile(outFile, vectFile, keywords)

keywords = 'internet technology security rt comment'

newKeyword(vectFile, keywords)
