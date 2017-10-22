import sys

arguments = sys.argv[1:]

zero = arguments[0]
keywords = arguments[1:]

with open("calvinRead.txt", 'w') as wf:
    wf.write('original: ' + str(zero) + '\n')
    wf.write('keywords: ')
    for key in keywords:
        wf.write(key + ' ')