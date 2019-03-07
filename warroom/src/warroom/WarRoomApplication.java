package warroom;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

public class WarRoomApplication extends Application{

    @Override
    public void start(final Stage primaryStage) throws Exception {
        primaryStage.setTitle("Tzuno War Room");
        primaryStage.setScene(new Scene(FXMLLoader.load(WarRoomApplication.class.getResource("warroom.fxml"))));
        primaryStage.show();
    }

    public static void main(final String[] args) {
        WarRoomApplication.launch(args);
    }
}
