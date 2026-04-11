/*
 * Problem: Applications need a way to revert and re-apply actions without losing data.
 * Logic: We use Two Stacks (undoStack and redoStack). When you type, we push to undo. 
 * When you undo, we pop from undo and push to redo. 
 */

import java.util.Scanner;
import java.util.Stack;

public class EditorHistory {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        Stack<String> history = new Stack<>();
        Stack<String> redoBuffer = new Stack<>();

        System.out.println("\033[1m\n--- Text Editor State Manager ---\033[0m");
        System.out.println("\033[90mCommands: type <word>, undo, redo, exit\033[0m\n");

        while (true) {
            System.out.print("\033[1m> \033[0m");
            String input = sc.nextLine().trim();

            if (input.equalsIgnoreCase("exit")) break;

            if (input.equalsIgnoreCase("undo")) {
                if (!history.isEmpty()) {
                    redoBuffer.push(history.pop());
                    System.out.println("  \033[90m[Action Reverted]\033[0m");
                } else {
                    System.out.println("  \033[31mNothing to undo.\033[0m");
                }
            } else if (input.equalsIgnoreCase("redo")) {
                if (!redoBuffer.isEmpty()) {
                    history.push(redoBuffer.pop());
                    System.out.println("  \033[90m[Action Reapplied]\033[0m");
                } else {
                    System.out.println("  \033[31mNothing to redo.\033[0m");
                }
            } else if (input.toLowerCase().startsWith("type ")) {
                String word = input.substring(5);
                history.push(word);
                redoBuffer.clear(); // Clear redo buffer on new action
            } else {
                System.out.println("  \033[31mInvalid command.\033[0m");
            }

            // Render current state
            System.out.print("  \033[1mDocument State:\033[0m \"");
            for (String w : history) {
                System.out.print(w + " ");
            }
            System.out.println("\"\n");
        }
        sc.close();
    }
}