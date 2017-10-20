from googletrans import Translator as translator

from nltk.tokenize import sent_tokenize, word_tokenize
from nltk.corpus import stopwords

from PyDictionary import PyDictionary as dict





#################### Translation ###################
# translator = Translator()

def translate(sentence):
    return (translator.translate(sentence)).text

#################### StopWords ###################    
stop_words = set(stopwords.words('english'))

def stopRemToken(word_tokens):
    filtered_sentence = [w for w in word_tokens if not w in stop_words]
    return filtered_sentence

def stopRemSent(sentence):
    word_tokens = word_tokenize(sentence)
    tokens = stopRemToken(word_tokens)
    retStr = "".join(" " + str(x) for x in tokens)
    return retStr

################### Synonyms ################################
def synom(word):
    return dict.synonym(word)

##################################################
from nltk.stem import PorterStemmer
from nltk.tokenize import sent_tokenize, word_tokenize

ps = PorterStemmer()

def stemSent(sentence):
    words = word_tokenize(sentence)
    stem_token = stemToken(words)
    retStr = "".join(" " + str(x) for x in stem_token)
    return retStr

def stemToken(words):
    ret = []
    for word in words:
        ret.append(ps.stem(word))
    return ret

def remSpec(words_token):
    ret = []
    for word in words_token:
        temp = remSp(word)
        length = len(temp)
        if length > 0:
            ret.append(temp)            
    return ret

def remSp(word):
    return ''.join(e for e in word if e.isalpha())


####################
def clean(sentence):
    sentence = translate(sentence)
    sentence = str.lower(sentence)
    words = word_tokenize(sentence)
    words = stopRemToken(words)
    words = stemToken(words)
    words = remSpec(words)
    return words

