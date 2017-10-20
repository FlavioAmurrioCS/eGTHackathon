from stemmer import *
from stopwords import *
from synonyms import *
#from twitter import *
from translate import *
from stemmer import*


comment = "The problem basically consists on this, we have created an Array of Object ArrayLists "
stemSent(comment)

def clean(sentence):
    sentence = translate(sentence)
    sentence = str.lower(sentence)
    words = word_tokenize(sentence)
    words = stopRemToken(words)
    words = stemToken(words)
    return words