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

        Platform.runLater(new Runnable() {
            @Override
            public void run() {
                searchButton.setText("Tilkoblet");
            }
        });

        // Begynn å lese meldinger fra bluetooth-enheten
        reader = new WarRoomBTReader(this, btIS);
        new Thread(reader).start();
    }

    @FXML
    void initialize() {
        assert searchButton != null : "fx:id=\"searchButton\" was not injected: check your FXML file 'app.fxml'.";
        assert readyLabel != null : "fx:id=\"readyLabel\" was not injected: check your FXML file 'app.fxml'.";

        readyLabel.setText("IKKE KLAR");
    }
}
