from googletrans import Translator

translator = Translator()

def translate(sentence):
    return (translator.translate(sentence)).text
    