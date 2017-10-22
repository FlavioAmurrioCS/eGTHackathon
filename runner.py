from PreProcessing import *

user_keywords = "hockey fan"

sergioFile = 'tweets.txt'
flavioFile = 'score.txt'

kSet = tokenToSet(clean(user_keywords))

readNewSergio(sergioFile, flavioFile, kSet)