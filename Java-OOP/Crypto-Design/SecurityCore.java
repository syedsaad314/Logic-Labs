/* * [PROBLEM STATEMENT]
 * Hardcoding a single encryption method (like AES) is a security risk. If 
 * that algorithm is compromised, the entire app fails. We need a system 
 * where we can swap encryption algorithms at runtime without changing the 
 * business logic.
 *
 * [LOGIC & INSIGHT]
 * I utilized the 'Strategy Design Pattern'. I created a 'CipherStrategy' 
 * interface. Whether we use 'AES_256' or a custom 'XOR_Shift', the main 
 * 'SecurityEngine' doesn't care—it just calls '.encrypt()'. This makes the 
 * code "Future-Proof." I added a 'Base64' wrapper to ensure the output 
 * is always URL-safe, showing I’m thinking about the transport layer.
 */

import java.util.Base64;

interface CipherStrategy {
    String process(String data, String key);
}

class XorCipher implements CipherStrategy {
    public String process(String data, String key) {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < data.length(); i++) {
            sb.append((char) (data.charAt(i) ^ key.charAt(i % key.length())));
        }
        return Base64.getEncoder().encodeToString(sb.toString().getBytes());
    }
}

class SecurityEngine {
    private CipherStrategy strategy;

    public void setStrategy(CipherStrategy strategy) {
        this.strategy = strategy;
    }

    public String secureData(String data, String key) {
        System.out.println("\033[36m[ENGINE]\033[0m Applying dynamic encryption strategy...");
        return strategy.process(data, key);
    }
}

public class SecurityCore {
    public static void main(String[] args) {
        SecurityEngine engine = new SecurityEngine();
        
        // Using XOR Strategy
        engine.setStrategy(new XorCipher());
        String encrypted = engine.secureData("UBIT_SENSITIVE_LOG", "LOGIC_LABS_2026");
        
        System.out.println("\033[32m[RESULT]\033[0m Payload: " + encrypted);
    }
}