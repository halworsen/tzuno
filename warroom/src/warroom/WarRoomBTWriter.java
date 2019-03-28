package warroom;

import javafx.concurrent.Task;

import javax.microedition.io.StreamConnection;
import java.io.IOException;
import java.io.OutputStream;
import java.nio.charset.StandardCharsets;

public class WarRoomBTWriter extends Task<Void> {

	private WarRoomController controller;

	private boolean stop = false;
	private boolean sendMsg = false;
	private String queuedMsg;

	private OutputStream btOS;

	WarRoomBTWriter(WarRoomController controller, StreamConnection stream) {
		super();

		this.controller = controller;

		try {
			this.btOS = stream.openOutputStream();
		} catch (IOException e) {
			controller.log("Failed to initialize the BT output stream");
			stop();
		}
	}

	protected void stop() {
		stop = true;
	}

	protected void sendMsg(String msg) {
		sendMsg = true;
		queuedMsg = msg;
	}

	@Override
	protected Void call() throws IOException {
		if(btOS == null) {
			return null;
		}

		controller.log("BT writer is ready!");

		while(true) {
			if(stop) {
				btOS.close();
				controller.log("BT writer successfully stopped");
				return null;
			}

			if(!sendMsg) {
				// Yield while there is no message to send
				Thread.yield();
				continue;
			}

			sendMsg = false;

			btOS.write(("<" + queuedMsg + ">").getBytes());
		}
	}

}
