package warroom;

import java.io.IOException;
import java.io.InputStream;
import java.net.ConnectException;
import java.net.URL;
import java.util.ResourceBundle;

import javafx.application.Platform;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;

import javax.microedition.io.StreamConnection;

public class WarRoomController {

    @FXML
    private ResourceBundle resources;

    @FXML
    private URL location;

    @FXML
    private Button searchButton;

    @FXML
    private TextField msgField;

    @FXML
    private Button sendButton;

    @FXML
    private TextArea commArea;

    private StreamConnection stream;
    private WarRoomBTSearcher searcher;
    private WarRoomBTReader reader;

    @FXML
    void searchButtonPress(ActionEvent event) throws InterruptedException {
        searchButton.setDisable(true);
        searchButton.setText("Søker...");

        // Begynn å søke
        searcher = new WarRoomBTSearcher(this);
        new Thread(searcher).start();
    }

    @FXML
    void sendMessage(ActionEvent event) {

    }

    protected void msgReceived(String msg) {
        // Oppdater tekst
        Platform.runLater(new Runnable() {
            @Override public void run() {
                commArea.appendText(msg + "\n");

                if(msg == "closeconn") {
                    try {
                        closeStream();
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
            }
        });
    }

    protected void setStream(StreamConnection stream) throws IOException {
        this.stream = stream;

        Platform.runLater(new Runnable() {
            @Override
            public void run() {
                searchButton.setText("Tilkoblet");
            }
        });

        // Begynn å lese meldinger fra bluetooth-enheten
        reader = new WarRoomBTReader(this, stream);
        new Thread(reader).start();
    }

    protected void closeStream() throws IOException {
        if(stream == null) {
            return;
        }

        stream.close();
        this.stream = null;

        // Stans bluetooth-leser-tråden
        if(reader.isRunning()) {
            reader.stop();
        }
        this.reader = null;

        searchButton.setDisable(false);
        searchButton.setText("Søk etter Tzuno");
    }

    @FXML
    void initialize() {
        assert searchButton != null : "fx:id=\"searchButton\" was not injected: check your FXML file 'app.fxml'.";

        commArea.setDisable(true);
    }
}
