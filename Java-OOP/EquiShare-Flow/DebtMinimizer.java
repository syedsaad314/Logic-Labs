/*
 * Problem (The Commons): A group goes on a trip. Person A pays for the hotel, Person B pays 
 * for food, Person C pays for gas. By the end, the debt network is a mess. 
 * Logic: Cash Flow Minimization Graph. We calculate everyone's net balance, then use a greedy 
 * algorithm to settle debts directly. The person who owes the most pays the person who is owed the most, 
 * bypassing unnecessary middle-man transactions.
 */

public class DebtMinimizer {
    
    // Returns index of the maximum value (Biggest Creditor)
    private static int getMax(int[] arr) {
        int maxInd = 0;
        for (int i = 1; i < arr.length; i++)
            if (arr[i] > arr[maxInd]) maxInd = i;
        return maxInd;
    }

    // Returns index of the minimum value (Biggest Debtor)
    private static int getMin(int[] arr) {
        int minInd = 0;
        for (int i = 1; i < arr.length; i++)
            if (arr[i] < arr[minInd]) minInd = i;
        return minInd;
    }

    private static void settleDebts(int[] amounts, String[] names) {
        int maxCredit = getMax(amounts);
        int maxDebit = getMin(amounts);

        // If both are 0, all debts are settled
        if (amounts[maxCredit] == 0 && amounts[maxDebit] == 0) return;

        // Find the minimum of the two amounts to settle
        int minTransaction = Math.min(-amounts[maxDebit], amounts[maxCredit]);
        
        amounts[maxCredit] -= minTransaction;
        amounts[maxDebit] += minTransaction;

        System.out.println("  \033[36m[Transfer]\033[0m \033[1m" + names[maxDebit] + "\033[0m pays $" + 
                           minTransaction + " to \033[1m" + names[maxCredit] + "\033[0m");

        // Recursively settle the rest
        settleDebts(amounts, names);
    }

    public static void main(String[] args) {
        System.out.println("\033[1m\n--- EquiShare Flow: Expense Settler ---\033[0m");
        System.out.println("\033[90mScenario: Saad paid $200 for servers. Ali paid $50 for domains. Bilal paid $0.\033[0m");
        System.out.println("\033[90mTotal cost is $250. Everyone should pay ~$83.33. Calculating optimal transfers...\033[0m\n");

        String[] users = {"Saad", "Ali", "Bilal"};
        // Net balances: Saad is owed $116, Ali owes $33, Bilal owes $83
        int[] netBalances = {116, -33, -83}; 

        settleDebts(netBalances, users);
        System.out.println("\n  \033[32m[✓] All accounts mathematically settled.\033[0m\n");
    }
}