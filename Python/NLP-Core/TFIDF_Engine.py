"""
* [PROBLEM STATEMENT]
* Before building LLM agents, we need to understand how machines "read." 
* Counting words isn't enough; a system needs to know which words are 
* mathematically important in a document versus words that are just common 
* filler (like "the", "and").
*
* [LOGIC & INSIGHT]
* I developed a raw mathematical TF-IDF (Term Frequency - Inverse Document 
* Frequency) engine without using heavy libraries like scikit-learn. 
* It calculates how frequently a word appears in a specific document, 
* heavily penalized by how common it is across the entire corpus. 
* This lays the exact algorithmic groundwork needed for building 
* Vector Databases and Semantic Search functionality.
"""

import math
from collections import Counter

class TFIDF_Engine:
    def __init__(self, corpus):
        self.corpus = corpus
        self.doc_count = len(corpus)

    def _term_frequency(self, term, document):
        words = document.lower().split()
        return words.count(term) / float(len(words))

    def _inverse_document_frequency(self, term):
        docs_with_term = sum(1 for doc in self.corpus if term in doc.lower().split())
        if docs_with_term == 0: return 0
        # +1 to prevent division by zero, logarithmic scale to dampen massive numbers
        return math.log(self.doc_count / float(docs_with_term))

    def calculate_score(self, term, document_index):
        doc = self.corpus[document_index]
        tf = self._term_frequency(term, doc)
        idf = self._inverse_document_frequency(term)
        return tf * idf

# Mini knowledge base
documents = [
    "Machine learning algorithms process massive data sets",
    "Data sets in university labs need high security",
    "Algorithms are the core of artificial intelligence and machine learning"
]

engine = TFIDF_Engine(documents)
target_word = "algorithms"

print("\033[1m--- TF-IDF SEMANTIC ANALYSIS ---\033[0m")
print(f"Target Term: '\033[36m{target_word}\033[0m'")

for i, doc in enumerate(documents):
    score = engine.calculate_score(target_word, i)
    color = "\033[32m" if score > 0 else "\033[90m"
    print(f"{color}Doc {i} Score: {score:.4f}\033[0m | {doc[:30]}...")