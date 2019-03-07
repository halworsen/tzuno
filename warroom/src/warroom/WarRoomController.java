package warroom;

import java.io.InputStream;
import java.net.URL;
import java.util.ResourceBundle;

import javafx.application.Platform;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.Label;

public class WarRoomController {

    @FXML
    private ResourceBundle resources;

    @FXML
    private URL location;

    @FXML
    private Button searchButton;

    @FXML
    private Label readyLabel;

    private InputStream btIS;
    private BTSearcher searcher;
    private BTReader reader;

    @FXML
    void searchButtonPress(ActionEvent event) throws InterruptedException {
        searchButton.setDisable(true);
        searchButton.setText("Søker...");

        searcher = new BTSearcher(this);
        new Thread(searcher).start();

        // Vent til tråden har funnet bluetooth-enheten
        while(btIS == null) {
            Thread.sleep(500);
        }

        searchButton.setText("Tilkoblet");
        // Begynn å lese meldinger fra bluetooth-enheten
        reader = new BTReader(this, btIS);
        new Thread(reader).start(); // Gjør det på en annen tråd så vi kan oppdatere grensesnittet
    }

    protected void msgReceived(String msg) {
        // Oppdater tekst
        Platform.runLater(new Runnable() {
            @Override public void run() {
                System.out.println(msg);
                if(msg.equals("rdy")) {
                    readyLabel.setText("KLAR");
                }else if(msg.equals("nrdy")) {
                    readyLabel.setText("IKKE KLAR");
                }
            }
        });
    }

    protected void setInputStream(InputStream btIS) {
        this.btIS = btIS;
    }

    @FXML
    void initialize() {
        assert searchButton != null : "fx:id=\"searchButton\" was not injected: check your FXML file 'app.fxml'.";
        assert readyLabel != null : "fx:id=\"readyLabel\" was not injected: check your FXML file 'app.fxml'.";

        readyLabel.setText("IKKE KLAR");
    }
}
