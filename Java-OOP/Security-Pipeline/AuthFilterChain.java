/* * [PROBLEM STATEMENT]
 * When a request hits a server, it must go through multiple checks: 
 * Logging -> Authentication -> Sanitization. If we hardcode these in one 
 * function, it becomes a "God Object" that is impossible to test. 
 *
 * [LOGIC & INSIGHT]
 * I implemented the 'Chain of Responsibility' pattern. Each 'Filter' is 
 * an independent object that either handles the request or passes it to 
 * the next 'Link' in the chain. My personal addition is the 'Sanitization 
 * Link'—it strips out dangerous characters before the data ever reaches 
 * the database. This is how professional enterprise middleware is built.
 */

abstract class Filter {
    protected Filter next;
    public void setNext(Filter next) { this.next = next; }
    public abstract void process(String request);
}

class AuthFilter extends Filter {
    public void process(String req) {
        if (req.contains("TOKEN_VALID")) {
            System.out.println("\033[32m[AUTH]\033[0m Token Verified.");
            if (next != null) next.process(req);
        } else {
            System.out.println("\033[31m[AUTH]\033[0m Access Denied: Invalid Token.");
        }
    }
}

class XSSFilter extends Filter {
    public void process(String req) {
        System.out.println("\033[34m[XSS]\033[0m Sanitizing script tags...");
        String clean = req.replace("<script>", "[REDACTED]");
        if (next != null) next.process(clean);
    }
}

public class AuthFilterChain {
    public static void main(String[] args) {
        Filter auth = new AuthFilter();
        Filter xss = new XSSFilter();
        
        auth.setNext(xss); // Linking the chain

        System.out.println("--- INCOMING REQUEST ---");
        auth.process("USER_ID:314 | TOKEN_VALID | DATA:<script>alert(1)</script>");
    }
}