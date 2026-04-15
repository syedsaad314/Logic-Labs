/*
 * Problem: Caching data is great for performance, but stale data causes bugs. We need 
 * a way to store data that automatically "expires" and deletes itself after a set time (TTL).
 * Logic: We wrap our stored values in a CacheItem object that records its creation time 
 * and Time-To-Live (TTL). When the system requests a key, we check if CurrentTime > ExpiryTime. 
 * If it is, we delete it on the fly and return null.
 */

import java.util.HashMap;
import java.util.Scanner;

class CacheItem {
    Object value;
    long expiryTime;

    public CacheItem(Object value, long ttlMilliseconds) {
        this.value = value;
        this.expiryTime = System.currentTimeMillis() + ttlMilliseconds;
    }

    public boolean isExpired() {
        return System.currentTimeMillis() > expiryTime;
    }
}

public class ExpiringCache {
    private HashMap<String, CacheItem> storage = new HashMap<>();

    public void set(String key, Object value, long ttlSeconds) {
        storage.put(key, new CacheItem(value, ttlSeconds * 1000));
        System.out.println("  \033[32m✓ Stored:\033[0m [" + key + "] = " + value + " (Expires in " + ttlSeconds + "s)");
    }

    public Object get(String key) {
        CacheItem item = storage.get(key);
        if (item == null) {
            System.out.println("  \033[31m✗ Miss:\033[0m Key [" + key + "] does not exist.");
            return null;
        }
        if (item.isExpired()) {
            storage.remove(key);
            System.out.println("  \033[33m⚠ Expired:\033[0m Key [" + key + "] has lived past its TTL and was purged.");
            return null;
        }
        
        long remaining = (item.expiryTime - System.currentTimeMillis()) / 1000;
        System.out.println("  \033[36m✓ Hit:\033[0m [" + key + "] = " + item.value + " (" + remaining + "s remaining)");
        return item.value;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        ExpiringCache cache = new ExpiringCache();

        System.out.println("\033[1m\n--- Time-Limited Memory Cache ---\033[0m");
        System.out.println("\033[90mCommands:\033[0m");
        System.out.println("\033[90m  set <key> <value> <ttl_seconds>  (e.g., set token 12345 10)\033[0m");
        System.out.println("\033[90m  get <key>                        (e.g., get token)\033[0m");
        System.out.println("\033[90m  exit\033[0m\n");

        while (true) {
            System.out.print("\033[1m> \033[0m");
            String[] input = sc.nextLine().trim().split(" ");
            String cmd = input[0].toLowerCase();

            if (cmd.equals("exit")) break;

            if (cmd.equals("set") && input.length == 4) {
                try {
                    cache.set(input[1], input[2], Long.parseLong(input[3]));
                } catch (NumberFormatException e) {
                    System.out.println("  \033[31mTTL must be a number in seconds.\033[0m");
                }
            } else if (cmd.equals("get") && input.length == 2) {
                cache.get(input[1]);
            } else {
                System.out.println("  \033[31mInvalid command.\033[0m");
            }
        }
        sc.close();
    }
}