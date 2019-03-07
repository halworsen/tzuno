package warroom;

import java.io.IOException;
import java.io.InputStream;

import javafx.concurrent.Task;

public class WarRoomBTReader extends Task<Void> {

    private WarRoomControllerController controller;

    private InputStream btIS;

    WarRoomBTReader(WarRoomController controller, InputStream btIS) {
        super();

        this.controller = controller;
        this.btIS = btIS;
    }

    @Override
    protected Void call() throws IOException, InterruptedException {
        if(btIS == null) {
            return null;
        }

        System.out.println("Attempting read");

        String msg = "";
        boolean reading = false;

        // Vent på meldinger fra Arduinoen
        while(true) {
            int available = btIS.available();
            if(available == 0) {
                Thread.yield();
                continue;
            }

            // Les meldingen
            for(int i = 0; i < available; i++) {
                int b = btIS.read(); // Les en byte
                char c = (char)b; // Gjør den om til en bokstav

                if(c == '#') {
                    if(reading) {
                        // Meldingen er ferdig
                        reading = false;

                        controller.msgReceived(msg);
                    } else {
                        // Ny melding
                        reading = true;
                        msg = "";
                    }
                } else {
                    if(reading) {
                        msg += c;
                    }
                }
            }
        }
    }
}
