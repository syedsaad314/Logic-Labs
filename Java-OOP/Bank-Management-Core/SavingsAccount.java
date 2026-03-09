public class SavingsAccount extends BaseAccount {
    public SavingsAccount(String id, String holder, double initial) {
        super(id, holder, initial);
    }

    @Override
    public void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            addLog("Deposited: $" + amount);
        }
    }

    @Override
    public boolean withdraw(double amount) {
        if (amount > 0 && balance >= amount) {
            balance -= amount;
            addLog("Withdrew: $" + amount);
            return true;
        }
        addLog("REJECTED: Insufficient funds for $" + amount);
        return false;
    }
}