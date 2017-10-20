from stemmer import *
from stopwords import *
from synonyms import *
#from twitter import *


comment = "The problem basically consists on this, we have created an Array of Object ArrayLists "
stemSent(comment)

def clean(sentence):
    print(sentence)
    sentence = str.lower(sentence)
    print(sentence)
    words = word_tokenize(sentence)
    print(words)
    words = stopRemToken(words)
    print(words)
    words = stemToken(words)
    print(words)
    words = stopRemToken(words)

def cleanLess(sentence):
    
