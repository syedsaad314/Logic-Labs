#include <iostream>
#include <vector>
#include <string>

using namespace std;

// System Aesthetic Configuration
#define RESET   "\033[0m"
#define EMERALD "\033[38;5;48m"
#define SLATE   "\033[38;5;244m"
#define AMBER   "\033[38;5;214m"
#define BOLD    "\033[1m"

struct Node {
    int data;
    Node *left, *right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class TreeMap {
    static const int ROWS = 25;
    static const int COLS = 80;
    char canvas[ROWS][COLS];

public:
    void clear() {
        for (int i = 0; i < ROWS; i++)
            for (int j = 0; j < COLS; j++) canvas[i][j] = ' ';
    }

    void map(Node* node, int r, int c, int h_gap) {
        if (!node || r >= ROWS || c < 0 || c >= COLS) return;

        string s = to_string(node->data);
        int pivot = s.length() / 2;
        for (int i = 0; i < s.length(); i++) {
            int pos = c + i - pivot;
            if (pos >= 0 && pos < COLS) canvas[r][pos] = s[i];
        }

        if (node->left) {
            canvas[r + 1][c - 1] = '/';
            map(node->left, r + 2, c - h_gap, max(1, h_gap / 2));
        }
        if (node->right) {
            canvas[r + 1][c + 1] = '\\';
            map(node->right, r + 2, c + h_gap, max(1, h_gap / 2));
        }
    }

    void display(Node* root) {
        clear();
        map(root, 0, COLS / 2, 8); 
        
        cout << SLATE << "\n[ SYSTEM_TREE_ARCHITECTURE ]" << RESET << "\n\n";
        for (int i = 0; i < ROWS; i++) {
            string rowStr = "";
            bool hasContent = false;
            for (int j = 0; j < COLS; j++) {
                if (isdigit(canvas[i][j])) {
                    rowStr += EMERALD; rowStr += canvas[i][j]; rowStr += RESET;
                    hasContent = true;
                } 
                else if (canvas[i][j] == '/' || canvas[i][j] == '\\') {
                    rowStr += SLATE; rowStr += canvas[i][j]; rowStr += RESET;
                    hasContent = true;
                } 
                else rowStr += canvas[i][j];
            }
            if (hasContent) cout << rowStr << endl;
        }
        cout << SLATE << "------------------------------------------------" << RESET << endl;
    }
};

Node* insert(Node* root, int val) {
    if (!root) return new Node(val);
    if (val < root->data) root->left = insert(root->left, val);
    else root->right = insert(root->right, val);
    return root;
}

int main() {
    Node* root = nullptr;
    TreeMap visualizer;
    int count, val;

    cout << BOLD << EMERALD << "BINARY-TREE-MAP // LOGIC-LABS BY SSBI" << RESET << endl;
    cout << SLATE << "OPERATOR: SYED SAAD BIN IRFAN" << RESET << "\n\n";

    cout << AMBER << "How many Nodes you want to enter?  " << RESET;
    if(!(cin >> count)) return 0;

    cout << SLATE << "\n[SYSTEM_ADVISORY]: To achieve a structurally balanced map, \n"
         << "it is recommended to input the median value of your dataset first.\n" << RESET;

    for (int i = 1; i <= count; i++) {
        cout << AMBER << "(" << i << "/" << count << ") " << RESET << "INSERT_NODE_VALUE: ";
        cin >> val;
        root = insert(root, val);

        if (i == 1) {
            cout << SLATE << "-> LOGIC_PATH: Try values significantly lower or higher than " << val 
                 << " to expand subtrees.\n" << RESET;
        }
    }

    cout << "\nINITIALIZING_ARCHITECTURE_RENDER...\n";
    visualizer.display(root);

    return 0;
}