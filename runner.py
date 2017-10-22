from PreProcessing import *

tweet = "This book is such a life saver.  football vic It has been so helpful to be able to go back to track trends, answer pediatrician questions, or communicate with each other when you are up at different times of the night with a newborn.  I think it is one of those things that everyone should be required to have before they leave the hospital.  We went through all the pages of the newborn version, then moved to the infant version, and will finish up the second infant book (third total) right as our baby turns 1.  See other things that are must haves for baby at [...]"
user_keywords = "football nfl vic"



ctweet = clean(tweet)
stweet = tokenToSet(ctweet)

key = clean(user_keywords)
sKey = tokenToSet(key)


print(jaccardIndex(stweet, sKey))

