package warroom;

import java.io.IOException;
import java.io.InputStream;

import javafx.concurrent.Task;

public class WarRoomBTReader extends Task<Void> {

    private WarRoomController controller;

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

        String msg = "";

        // Wait for messages from the Arduino
        while(true) {
            int available = btIS.available();
            if(available == 0) {
                // Yield while there is no data to read
                Thread.yield();
                continue;
            }

            // Read each byte of the message
            for(int i = 0; i < available; i++) {
                int b = btIS.read(); // Read a byte
                char c = (char)b;

                if(c == '<') {
                    // New message
                    msg = "";
                } else if(c == '>') {
                    // Message is over
                    controller.msgReceived(msg);
                } else {
                    msg += c;
                }
            }
        }
    }
}
