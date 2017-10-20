from googletrans import Translator

from nltk.tokenize import sent_tokenize, word_tokenize
from nltk.corpus import stopwords

from PyDictionary import PyDictionary as dict

from nltk.stem import PorterStemmer

############################### Translation ###############################
translator = Translator()

def translate(sentence):
    return (translator.translate(sentence)).text

############################### StopWords ###############################
stop_words = set(stopwords.words('english'))

def stopRemToken(word_tokens):
    filtered_sentence = [w for w in word_tokens if not w in stop_words]
    return filtered_sentence

def stopRemSent(sentence):
    word_tokens = word_tokenize(sentence)
    tokens = stopRemToken(word_tokens)
    retStr = "".join(" " + str(x) for x in tokens)
    return retStr

############################### Synonyms ###############################
def synom(word):
    return dict.synonym(word)

############################### Stemmer ###############################
ps = PorterStemmer()

def stemToken(words):
    ret = []
    for word in words:
        ret.append(ps.stem(word))
    return ret

def stemSent(sentence):
    words = word_tokenize(sentence)
    stem_token = stemToken(words)
    retStr = "".join(" " + str(x) for x in stem_token)
    return retStr

def remSp(word):
    return ''.join(e for e in word if e.isalpha())

def remSpec(words_token):
    ret = []
    for word in words_token:
        temp = remSp(word)
        length = len(temp)
        if length > 0:
            ret.append(temp)            
    return ret

############################### Combined Tools ###############################

comment = "This book is such a life saver.  It has been so helpful to be able to go back to track trends, answer pediatrician questions, or communicate with each other when you are up at different times of the night with a newborn.  I think it is one of those things that everyone should be required to have before they leave the hospital.  We went through all the pages of the newborn version, then moved to the infant version, and will finish up the second infant book (third total) right as our baby turns 1.  See other things that are must haves for baby at [...]"

def clean(sentence):
    # sentence = translate(sentence)
    sentence = str.lower(sentence)
    words = word_tokenize(sentence)
    words = stopRemToken(words)
    words = stemToken(words)
    words = remSpec(words)
    line = "".join(" " + str(x) for x in words)
    return line

def readfile(filename):
    with open(filename, 'r') as f:
        lines = f.readlines()
        with open(filename + "-output", 'w') as w:
            for line in lines:
                w.write(clean(line) + "\n")


readfile('file.txt')