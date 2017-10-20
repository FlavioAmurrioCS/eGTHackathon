from nltk.stem import PorterStemmer
from nltk.tokenize import sent_tokenize, word_tokenize

ps = PorterStemmer()

def stemSent(sentence):
    words = word_tokenize(sentence)
    stem_token = stemToken(words)
    retStr = "".join(str(x) for x in stem_token)
    return retStr

def stemToken(words):
    ret = []
    for word in words:
        ret.append(ps.stem(word))
    return ret

