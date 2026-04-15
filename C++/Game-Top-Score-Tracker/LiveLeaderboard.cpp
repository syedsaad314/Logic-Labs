/*
 * Problem: A gaming server receives thousands of scores a second. We only care about 
 * the "Top K" players. Sorting the entire list every time a new score arrives is O(N log N) 
 * and too slow.
 * Logic: We use a Min-Heap (Priority Queue) locked to size K. When a new score arrives, 
 * we compare it to the *lowest* score in our Top K (the root of the min-heap). If it's higher, 
 * we pop the lowest and push the new one. This reduces the time complexity to O(log K).
 */

#include <iostream>
#include <queue>
#include <vector>
#include <string>

using namespace std;

#define BOLD "\033[1m"
#define GRAY "\033[90m"
#define YELLOW "\033[33m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

struct Player {
    string name;
    int score;
    // Overload for Min-Heap comparison
    bool operator>(const Player& other) const {
        return score > other.score;
    }
};

class Leaderboard {
private:
    int capacity;
    priority_queue<Player, vector<Player>, greater<Player>> minHeap;

public:
    Leaderboard(int k) : capacity(k) {}

    void addScore(string name, int score) {
        if (minHeap.size() < capacity) {
            minHeap.push({name, score});
            cout << GREEN << "  [Added] " << name << " enters the leaderboard!" << RESET << "\n";
        } else if (score > minHeap.top().score) {
            cout << YELLOW << "  [Rank Up] " << name << " knocked " << minHeap.top().name << " off the board!" << RESET << "\n";
            minHeap.pop();
            minHeap.push({name, score});
        } else {
            cout << GRAY << "  [Ignored] " << name << "'s score isn't high enough." << RESET << "\n";
        }
    }

    void display() {
        // To display without destroying the heap, we make a copy
        priority_queue<Player, vector<Player>, greater<Player>> temp = minHeap;
        vector<Player> displayList;
        while (!temp.empty()) {
            displayList.push_back(temp.top());
            temp.pop();
        }
        
        cout << BOLD << "\n  --- Current Top " << capacity << " ---" << RESET << "\n";
        // Print in descending order
        for (int i = displayList.size() - 1; i >= 0; i--) {
            cout << "  " << (displayList.size() - i) << ". " << displayList[i].name << " - " << displayList[i].score << " pts\n";
        }
        cout << "\n";
    }
};

int main() {
    cout << BOLD << "\n--- Live Leaderboard Engine ---" << RESET << "\n";
    int k;
    cout << GRAY << "Set the maximum number of players on the leaderboard (e.g., 3): " << RESET;
    cin >> k;

    Leaderboard board(k);
    string name;
    int score;

    cout << GRAY << "\nEnter scores format: <Name> <Score> (e.g., 'Ali 500'). Type 'exit 0' to quit.\033[0m\n";

    while (true) {
        cout << BOLD << "> " << RESET;
        cin >> name >> score;
        if (name == "exit") break;

        board.addScore(name, score);
        board.display();
    }
    return 0;
}