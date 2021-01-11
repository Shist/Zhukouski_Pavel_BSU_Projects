package by.bsu.zhukouski.view;

import by.bsu.zhukouski.view.gui.controllers.CompositionController;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

/**
 * Class Main
 * @author Pavel Zhukouski, 3 course, 12 group
 * @version 2.3
 * Variant 5. Sound recording. Determine the hierarchy of musical compositions. Write the assembly to disk. Calculate the
 * duration. Carry out rearrangement of disc compositions based on one of the parameters. Find a composition that
 * matches a given range of parameters.
 */
public class Main extends Application {

    /**
     * Function for running whole programm
     * @param primaryStage - current stage for work of Application class
     */
    @Override
    public void start(Stage primaryStage) throws Exception {
        FXMLLoader CompLoader = new FXMLLoader(getClass().getResource("gui/views/composition.fxml"));

        Parent root = CompLoader.load();
        primaryStage.setTitle("Composition");
        primaryStage.setScene(new Scene(root, 1200, 800));

        primaryStage.show();

        CompositionController CompContr = CompLoader.getController();

        CompContr.init();
    }

    /**
     * Program entry point
     * @param args - arguments
     */
    public static void main(String[] args) {
        launch(args);
    }
}
