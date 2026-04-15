"""
Problem: When users make typos, systems like Google or MS Word instantly suggest corrections 
("Did you mean...?"). 
Logic: We use Dynamic Programming to calculate the "Levenshtein Distance" (Edit Distance). 
This algorithm computes the exact minimum number of single-character edits (insertions, deletions, 
or substitutions) required to change the misspelled word into a valid dictionary word.
"""

def edit_distance(word1, word2):
    m, n = len(word1), len(word2)
    # Create a 2D matrix to store subproblem distances
    dp = [[0] * (n + 1) for _ in range(m + 1)]

    for i in range(m + 1):
        for j in range(n + 1):
            if i == 0:
                dp[i][j] = j    # Min operations = inserting all chars
            elif j == 0:
                dp[i][j] = i    # Min operations = deleting all chars
            elif word1[i-1] == word2[j-1]:
                dp[i][j] = dp[i-1][j-1] # Chars match, no operation needed
            else:
                dp[i][j] = 1 + min(dp[i][j-1],      # Insert
                                   dp[i-1][j],      # Remove
                                   dp[i-1][j-1])    # Replace
    return dp[m][n]

def get_suggestions(typo, dictionary, max_results=3):
    # Calculate edit distance for every word in the dictionary
    distances = [(word, edit_distance(typo.lower(), word)) for word in dictionary]
    
    # Sort by closest match (lowest edit distance)
    distances.sort(key=lambda x: x[1])
    
    return [word for word, dist in distances[:max_results]]

if __name__ == "__main__":
    print("\033[1m\n--- Typo Correction Engine ---\033[0m")
    print("\033[90mBooting language model dictionary...\033[0m")
    
    # A small targeted dictionary for the demonstration
    valid_words = [
        "algorithm", "application", "backend", "database", "engineer", 
        "function", "network", "python", "software", "variable", "system"
    ]
    
    print("\033[90mType a misspelled tech word (e.g., 'siftware', 'pyhton', 'enginer'). Type 'quit' to exit.\033[0m\n")

    while True:
        try:
            word = input("\033[1m> \033[0m").strip()
            if word.lower() == 'quit':
                break
                
            if word.lower() in valid_words:
                print("  \033[32m✓ Spelling is correct.\033[0m\n")
            else:
                suggestions = get_suggestions(word, valid_words)
                print(f"  \033[33mDid you mean:\033[0m {', '.join(suggestions)}?\n")
                
        except EOFError:
            break