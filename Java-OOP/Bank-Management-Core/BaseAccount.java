import java.util.ArrayList;
import java.util.List;

public abstract class BaseAccount {
    protected String accountNumber;
    protected String accountHolder;
    protected double balance;
    protected List<String> transactionHistory;

    public BaseAccount(String accountNumber, String accountHolder, double initialBalance) {
        this.accountNumber = accountNumber;
        this.accountHolder = accountHolder;
        this.balance = initialBalance;
        this.transactionHistory = new ArrayList<>();
        addLog("Account Created with initial deposit: $" + initialBalance);
    }

    protected void addLog(String message) {
        transactionHistory.add(message);
    }

    public String getAccountNumber() { return accountNumber; }
    public double getBalance() { return balance; }

    public abstract void deposit(double amount);
    public abstract boolean withdraw(double amount);

    public void showFullReport() {
        System.out.println("\n--- OFFICIAL BANK REPORT ---");
        System.out.println("Holder: " + accountHolder);
        System.out.println("Account #: " + accountNumber);
        System.out.println("Current Balance: $" + balance);
        System.out.println("Transaction History:");
        for (String log : transactionHistory) {
            System.out.println(" >> " + log);
        }
        System.out.println("---------------------------\n");
    }
}