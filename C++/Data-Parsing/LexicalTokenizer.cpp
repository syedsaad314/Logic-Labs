/* * [PROBLEM STATEMENT]
 * When building custom configuration files or domain-specific languages, 
 * reading raw strings line-by-line is error-prone. We need an engine that 
 * can break down raw text into actionable "Tokens" (like Identifiers, 
 * Numbers, and Operators) before the system tries to execute them.
 *
 * [LOGIC & INSIGHT]
 * I engineered a basic Lexical Analyzer using a State Machine logic. 
 * Instead of messy regex, it reads character by character (O(N) time). 
 * It categorizes chunks of text into 'Syntax Tokens'. This is the exact 
 * foundation of how compilers (like GCC or V8) process code. Demonstrating 
 * this shows a deep understanding of low-level data structures and 
 * parsing algorithms.
 */

#include <iostream>
#include <string>
#include <vector>
#include <cctype>

enum class TokenType { IDENTIFIER, NUMBER, OPERATOR, UNKNOWN };

struct Token {
    TokenType type;
    std::string value;
};

class LexicalTokenizer {
public:
    std::vector<Token> tokenize(const std::string& input) {
        std::vector<Token> tokens;
        size_t i = 0;

        while (i < input.length()) {
            if (isspace(input[i])) {
                i++;
                continue;
            }

            if (isalpha(input[i])) {
                std::string id = "";
                while (i < input.length() && isalnum(input[i])) {
                    id += input[i++];
                }
                tokens.push_back({TokenType::IDENTIFIER, id});
            } 
            else if (isdigit(input[i])) {
                std::string num = "";
                while (i < input.length() && isdigit(input[i])) {
                    num += input[i++];
                }
                tokens.push_back({TokenType::NUMBER, num});
            } 
            else {
                std::string op(1, input[i++]);
                tokens.push_back({TokenType::OPERATOR, op});
            }
        }
        return tokens;
    }

    void printTokens(const std::vector<Token>& tokens) {
        std::cout << "\033[1;36m[LEXICAL_ANALYSIS_COMPLETE]\033[0m\n";
        for (const auto& t : tokens) {
            std::cout << "  ";
            switch(t.type) {
                case TokenType::IDENTIFIER: std::cout << "\033[32m[ID]\033[0m      "; break;
                case TokenType::NUMBER:     std::cout << "\033[33m[NUM]\033[0m     "; break;
                case TokenType::OPERATOR:   std::cout << "\033[35m[OP]\033[0m      "; break;
                default:                    std::cout << "\033[31m[UNKNOWN]\033[0m "; break;
            }
            std::cout << t.value << "\n";
        }
    }
};

int main() {
    LexicalTokenizer lexer;
    std::string rawData = "serverPort = 8080;";
    
    std::cout << "--- INCOMING RAW STREAM ---\nRaw: \"" << rawData << "\"\n\n";
    auto tokens = lexer.tokenize(rawData);
    lexer.printTokens(tokens);

    return 0;
}