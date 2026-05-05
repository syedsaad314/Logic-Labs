/*
 * Problem: Tight coupling. If your Database class directly tells the UI to update, 
 * you can't change the UI without breaking the Database.
 * Logic: The Observer Pattern. The DataStream (Subject) maintains a list of listeners. 
 * When new data arrives, it broadcasts to everyone on the list. The DataStream doesn't 
 * know *who* is listening, only that it needs to send the signal.
 */

import java.util.*;

interface DataListener { void onDataReceived(String data); }

class LiveStream {
    private List<DataListener> listeners = new ArrayList<>();

    public void subscribe(DataListener listener) { listeners.add(listener); }

    public void emit(String telemetry) {
        System.out.println("  \033[35m[Stream]\033[0m Emitting: " + telemetry);
        for (DataListener l : listeners) l.onDataReceived(telemetry);
    }
}

public class StreamObserver {
    public static void main(String[] args) {
        System.out.println("\033[1m\n--- Reactive Stream Observer ---\033[0m");
        LiveStream telemetryBus = new LiveStream();

        // Anonymous subscriber (e.g., a Dashboard Widget)
        telemetryBus.subscribe(data -> System.out.println("  \033[32m[UI Widget]\033[0m Rendering: " + data));
        
        telemetryBus.emit("CPU_LOAD: 42%");
        telemetryBus.emit("MEM_USAGE: 1.2GB");
    }
}