from PreProcessing import *

import sys

args = sys.argv[1:]

function = args[0]

outFile = 'tweetsList.txt'
vectFile = 'vector.txt'
wordFreqFile = 'wordfreq.txt'

if function == 'uandk':
    zero = word_tokenize(args[1])
    keywords = tokenToString(args[2:])
    print("Root User: " + args[1])
    print("Searching for: " + keywords)
    userSet = set()

    try:
        nlist = recursion(zero, outFile, userSet)
        nlist = recursion(nlist, outFile, userSet)
        recursionLevel2(nlist, outFile, userSet)
    except:
        print("Reached Api limit")    
    readSergioFile(outFile, vectFile, keywords)
    print("File Written")

elif function == 'newkey':
    keywords = tokenToString(args[1:])
    print("Searching for: " + keywords)
    newKeyword(vectFile, keywords)
    print("File Written")
elif function == 'wordfreq':
    print("Calculating Word Frequency")
    wordFreq(vectFile, wordFreqFile)
    print("File Written")
else:
    print("Wrong option\n")
    print("python Runnner.py [func] [args]\n")
    print("Available func:\n")
    print("uandk [username keywords]")
    print("newKey [keywords]")
    print("wordfreq")