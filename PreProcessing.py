from googletrans import Translator

from nltk.tokenize import sent_tokenize, word_tokenize
from nltk.corpus import stopwords

from PyDictionary import PyDictionary as dict

from nltk.stem import PorterStemmer

from time import time

import nltk 
from nltk.corpus import wordnet

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

def readSergioFile(input, output, kSet):
    lines = []
    values = []
    with open(output, 'w') as wf:
        with open(input, 'r') as rf:
            lines = rf.readlines()
            for line in lines:
                sp = line.split("###")
                cToken = clean(sp[1])
                outStr = sp[0] + "###" + tokenToString(cToken)
                s1 = tokenToSet(cToken)
                ct = commonTerm(s1, kSet)
                values.append(ct)
                outStr = outStr + ",,," + ct
                wf.write(outStr)

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
            


