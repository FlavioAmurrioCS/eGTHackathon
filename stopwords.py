from nltk.tokenize import sent_tokenize, word_tokenize
from nltk.corpus import stopwords
# stops_words set is the list of stopwords(Global Variable)
stop_words = set(stopwords.words('english'))

def stopRem(sentence):
    word_tokens = word_tokenize(sentence)
    filtered_sentence = [w for w in word_tokens if not w in stop_words]
    return filtered_sentence