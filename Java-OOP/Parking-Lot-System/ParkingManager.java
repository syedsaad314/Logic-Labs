/*
 * Problem: Managing physical space digitally requires strict state tracking. A parking lot 
 * must know exactly which spots are open, assign tickets, and prevent double-booking.
 * Logic: Core Object-Oriented Principles (Encapsulation and State Management). We model 
 * real-world entities (Lot and Spot) to maintain an accurate, visual data grid.
 */

import java.util.Scanner;

class ParkingSpot {
    private int id;
    private boolean isOccupied;
    private String vehiclePlate;

    public ParkingSpot(int id) {
        this.id = id;
        this.isOccupied = false;
        this.vehiclePlate = "";
    }

    public boolean park(String plate) {
        if (!isOccupied) {
            this.vehiclePlate = plate;
            this.isOccupied = true;
            return true;
        }
        return false;
    }

    public void leave() {
        this.isOccupied = false;
        this.vehiclePlate = "";
    }

    public boolean isOccupied() { return isOccupied; }
    public String getPlate() { return vehiclePlate; }
    public int getId() { return id; }
}

public class ParkingManager {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        ParkingSpot[] lot = new ParkingSpot[5]; // 5 spot lot for demonstration
        for (int i = 0; i < lot.length; i++) lot[i] = new ParkingSpot(i + 1);

        System.out.println("\033[1m\n--- Central Parking Management ---\033[0m");

        while (true) {
            System.out.println("\n\033[90mCommands: park <plate>, leave <spot_number>, exit\033[0m");
            
            // Render the Lot visually
            System.out.print("\033[36m  Lot Status: \033[0m");
            for (ParkingSpot spot : lot) {
                if (spot.isOccupied()) System.out.print("[\033[31m " + spot.getPlate() + " \033[0m] ");
                else System.out.print("[\033[32m Empty \033[0m] ");
            }
            System.out.println();

            System.out.print("\033[1m> \033[0m");
            String[] input = sc.nextLine().trim().split(" ");
            String cmd = input[0].toLowerCase();

            if (cmd.equals("exit")) break;

            if (cmd.equals("park") && input.length == 2) {
                boolean parked = false;
                for (ParkingSpot spot : lot) {
                    if (!spot.isOccupied()) {
                        spot.park(input[1]);
                        System.out.println("  \033[32m✓ Vehicle " + input[1] + " assigned to Spot " + spot.getId() + "\033[0m");
                        parked = true;
                        break;
                    }
                }
                if (!parked) System.out.println("  \033[31m✗ Lot is completely full.\033[0m");
            } 
            else if (cmd.equals("leave") && input.length == 2) {
                try {
                    int spotNum = Integer.parseInt(input[1]) - 1;
                    if (spotNum >= 0 && spotNum < lot.length && lot[spotNum].isOccupied()) {
                        System.out.println("  \033[90mVehicle " + lot[spotNum].getPlate() + " has departed.\033[0m");
                        lot[spotNum].leave();
                    } else {
                        System.out.println("  \033[31m✗ Spot is already empty or invalid.\033[0m");
                    }
                } catch (NumberFormatException e) {
                    System.out.println("  \033[31m✗ Invalid spot number.\033[0m");
                }
            } else {
                System.out.println("  \033[31m✗ Invalid command structure.\033[0m");
            }
        }
        sc.close();
    }
}