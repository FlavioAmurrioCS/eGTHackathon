from nltk.tokenize import sent_tokenize, word_tokenize
from nltk.corpus import stopwords
# stops_words set is the list of stopwords(Global Variable)
stop_words = set(stopwords.words('english'))

def stopRemSent(sentence):
    word_tokens = word_tokenize(sentence)
    tokens = stopRemToken(word_tokens)
    retStr = "".join(" " + str(x) for x in tokens)
    return retStr

def stopRemToken(word_tokens):
    filtered_sentence = [w for w in word_tokens if not w in stop_words]
    return filtered_sentence