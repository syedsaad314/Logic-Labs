"""
Problem: When traveling with friends, a complex web of debts forms (A owes B, B owes C, C owes A). 
We need an algorithm that simplifies the network so the minimum number of transactions occur.
Logic: Cash Flow Minimization Graph. We calculate the *net* balance for each person 
(Total Owed - Total Debt). We then pair the person with the highest debt with the person 
who is owed the most, resolving balances iteratively.
"""

from collections import defaultdict

def simplify_debts():
    print("\033[1m\n--- Debt Simplification Engine ---\033[0m")
    print("\033[90mEnter debts. Format: 'Saad owes Ali 50'\033[0m")
    print("\033[90mType 'calc' to resolve and minimize transactions.\033[0m\n")

    balances = defaultdict(int)

    while True:
        try:
            line = input("\033[1m> \033[0m").strip()
            if line.lower() == 'calc':
                break
            
            parts = line.split()
            if len(parts) == 4 and parts[1].lower() == "owes":
                debtor, creditor, amount = parts[0], parts[2], int(parts[3])
                balances[debtor] -= amount
                balances[creditor] += amount
            else:
                print("  \033[31mInvalid format. Use: [Name1] owes [Name2] [Amount]\033[0m")
        except EOFError:
            break
        except ValueError:
             print("  \033[31mAmount must be a whole number.\033[0m")

    # Separate into positive (creditors) and negative (debtors) balances
    debtors = []
    creditors = []
    
    for person, amount in balances.items():
        if amount < 0:
            debtors.append([person, amount])
        elif amount > 0:
            creditors.append([person, amount])

    print("\n\033[1mOptimized Transaction Plan:\033[0m")
    transactions = 0

    while debtors and creditors:
        debtor = debtors[0]
        creditor = creditors[0]
        
        # Settle the maximum possible amount between the two
        settle_amount = min(-debtor[1], creditor[1])
        
        print(f"  \033[36m✓ {debtor[0]} pays {creditor[0]} ${settle_amount}\033[0m")
        transactions += 1
        
        debtor[1] += settle_amount
        creditor[1] -= settle_amount
        
        if debtor[1] == 0: debtors.pop(0)
        if creditor[1] == 0: creditors.pop(0)

    if transactions == 0:
        print("  \033[32mAll balances are already settled.\033[0m")

if __name__ == "__main__":
    simplify_debts()