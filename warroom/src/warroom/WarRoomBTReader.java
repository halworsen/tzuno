package warroom;

import java.io.IOException;
import java.io.InputStream;

import javafx.concurrent.Task;

import javax.microedition.io.StreamConnection;

public class WarRoomBTReader extends Task<Void> {

    private WarRoomController controller;

    private boolean stop = false;
    private InputStream btIS;

    WarRoomBTReader(WarRoomController controller, StreamConnection stream) {
        super();

        this.controller = controller;

        try {
            this.btIS = stream.openInputStream();
        } catch (IOException e) {
            System.out.println("Failed to initialize the BT input stream");
            stop();
        }
    }

    protected void stop() {
        stop = true;
    }

    @Override
    protected Void call() throws IOException, InterruptedException {
        if(btIS == null) {
            return null;
        }

        String msg = "";
        controller.log("BT reader is ready!");

        // Wait for messages from the Arduino
        while(true) {
            // Stans tråden
            if(stop) {
                btIS.close();
                controller.log("BT reader successfully stopped");
                return null;
            }

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
