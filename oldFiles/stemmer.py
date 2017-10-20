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