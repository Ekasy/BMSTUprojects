import re
import random


class MarkovChain:
    def __init__(self, tokenize_='char', n_gram_=2, cleaning_=False):
        self.tokenize = tokenize_
        if self.tokenize == 'word':
            self.separator = ' '
        else:
            self.separator = ''
        self.n_gram = n_gram_ - 1
        self.cleaning = cleaning_
        self.vocabulary = []

    def fit(self, carcase_):
        # make 1 long string
        self.carcase = ''.join(' '.join(carcase_).split('\n')).lower()

        # cleaning of punctuation marks
        if self.cleaning:
            TOKENIZE_RE = re.compile(r'\w+-\w+|\w+', re.I)
            self.carcase = ' '.join(TOKENIZE_RE.findall(self.carcase))

        if self.tokenize == 'word':
            self.carcase = self.carcase.split(' ')
        else:
            self.carcase = list(self.carcase)

        # create context's table
        v = {}
        for i in range(len(self.carcase) - self.n_gram):
            context = self.separator.join(self.carcase[i:i + self.n_gram])
            token = self.carcase[i + self.n_gram]

            if v.get(context) is None:
                v[context] = {}
                v[context][token] = 1
            else:
                if v[context].get(token) is None:
                    v[context][token] = 1
                else:
                    v[context][token] += 1

        # convert frequencies to probabilities
        for context in v.keys():
            total = sum(v[context].values())
            for token in v[context]:
                v[context][token] /= total

        self.proba = v

    def __generate_token(self, context):
        # remember last n_gram chars
        if self.tokenize == 'word':
            last_context = ' '.join(context.split(' ')[-self.n_gram:])
        else:
            last_context = context[-self.n_gram:]

        if self.proba.get(last_context) is None:
            return " "

        tokens = list(self.proba[last_context].keys())
        probas = list(self.proba[last_context].values())

        return random.choices(tokens, weights=probas)[0]

    def generate_text(self, context, max_len=100):
        text = context
        if self.tokenize == 'word':
            last_context = ' '.join(context.split(' ')[-self.n_gram:])
        else:
            last_context = context[-self.n_gram:]

        while len(text) < max_len:
            text += self.separator + str(self.__generate_token(last_context))

            if self.tokenize == 'word':
                last_context = ' '.join(text.split(' ')[-self.n_gram:])
            else:
                last_context = text[-self.n_gram:]

        return text


if __name__ == "__main__":
    carcase = []

    with open('eugene_onegin.txt', 'r', encoding='utf-8') as f:
        for line in f.readlines():
            carcase.append(line)

    mc = MarkovChain(n_gram_=5, tokenize_='char', cleaning_=False)
    mc.fit(carcase)

    print(mc.generate_text('мой', 200))
