package by.bsu.zhukouski.view.gui.controllers;

import by.bsu.zhukouski.controller.Manager;
import by.bsu.zhukouski.model.entity.*;
import by.bsu.zhukouski.model.exception.InvalidDataException;
import javafx.fxml.FXML;
import javafx.scene.control.ComboBox;
import javafx.scene.control.Label;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.text.Font;

/**
 * Class CompositionController for controlling objects on javaFX form
 * @author Pavel Zhukouski, 3 course, 12 group
 * @version 2.3
 */

public class CompositionController {

    /**
     * Current chosen type of music composition
     */
    MusicType currType;

    /**
     * Combobox with all music types
     */
    @FXML
    private ComboBox<MusicType> compositionTypeComboBox;

    /**
     * TextField for the name of music composition
     */
    @FXML
    private TextField compositionNameTextField;

    /**
     * TextField for the author of music composition
     */
    @FXML
    private TextField compositionAuthorTextField;

    /**
     * TextField for the duration of music composition
     */
    @FXML
    private TextField compositionDurationTextField;

    /**
     * TextField for the name of music composition which user wants to find out
     */
    @FXML
    private TextField FindByNameTextField;

    /**
     * TextField for the author of music composition which user wants to find out
     */
    @FXML
    private TextField FindByAuthorTextField;

    /**
     * TextField for the duration of music composition which user wants to find out
     */
    @FXML
    private TextField FindByDurationTextField;

    /**
     * TextField for the first part of range of the name of music composition for finding
     */
    @FXML
    private TextField FindByNameRangeTextField1;

    /**
     * TextField for the second part of range of the name of music composition for finding
     */
    @FXML
    private TextField FindByNameRangeTextField2;

    /**
     * TextField for the first part of range of the author of music composition for finding
     */
    @FXML
    private TextField FindByAuthorRangeTextField1;

    /**
     * TextField for the second part of range of the author of music composition for finding
     */
    @FXML
    private TextField FindByAuthorRangeTextField2;

    /**
     * TextField for the first part of range of the duration of music composition for finding
     */
    @FXML
    private TextField FindByDurationRangeTextField1;

    /**
     * TextField for the second part of range of the duration of music composition for finding
     */
    @FXML
    private TextField FindByDurationRangeTextField2;

    /**
     * ComboBox for all genres of HipHop
     */
    @FXML
    private ComboBox<HipHop.HipHopGenre> HipHopGenreComboBox;

    /**
     * ComboBox for all genres of Pop
     */
    @FXML
    private ComboBox<Pop.PopGenre> PopGenreComboBox;

    /**
     * ComboBox for all genres of Rock
     */
    @FXML
    private ComboBox<Rock.RockGenre> RockGenreComboBox;

    /**
     * TextArea for all output of information
     */
    @FXML
    private TextArea compositionsTextArea;

    /**
     * Disc on which user will record compositions
     */
    private final Disc disc = new Disc();

    /**
     * Wrong data on TextField for some mistakes that can appear
     */
    @FXML
    private Label wrongDataLabel;

    /**
     * Function Init for initialising all objects on JavaFX window
     */
    public void init() {
        Disc.getInstance();

        compositionTypeComboBox.getItems().setAll(MusicType.values());
        compositionTypeComboBox.setValue(MusicType.HipHop);

        HipHopGenreComboBox.getItems().setAll(HipHop.HipHopGenre.values());
        HipHopGenreComboBox.setValue(HipHop.HipHopGenre.AlternativeHipHop);

        PopGenreComboBox.getItems().setAll(Pop.PopGenre.values());
        PopGenreComboBox.setValue(Pop.PopGenre.K_pop);

        RockGenreComboBox.getItems().setAll(Rock.RockGenre.values());
        RockGenreComboBox.setValue(Rock.RockGenre.Rock_n_roll);

        HipHopGenreComboBox.setVisible(false);
        PopGenreComboBox.setVisible(false);
        RockGenreComboBox.setVisible(false);

        compositionsTextArea.setWrapText(true);

        wrongDataLabel.setVisible(false);
        wrongDataLabel.setFont(new Font("Arial", 18));
    }

    /**
     * Function for confirming the type of music composition that we need to choose needed genre ComboBox
     */
    @FXML
    private void confirmType() {
        currType = compositionTypeComboBox.getValue();
        if (currType == MusicType.HipHop)
        {
            HipHopGenreComboBox.setVisible(true);
            PopGenreComboBox.setVisible(false);
            RockGenreComboBox.setVisible(false);
        }
        else if (currType == MusicType.Pop)
        {
            HipHopGenreComboBox.setVisible(false);
            PopGenreComboBox.setVisible(true);
            RockGenreComboBox.setVisible(false);
        }
        else if (currType == MusicType.Rock)
        {
            HipHopGenreComboBox.setVisible(false);
            PopGenreComboBox.setVisible(false);
            RockGenreComboBox.setVisible(true);
        }
    }

    /**
     * Function for recording the composition data on the disc
     */
    @FXML
    private void recordComposition() {
        wrongDataLabel.setVisible(false);
        try {
            if (currType == MusicType.HipHop)
            {
                HipHop temp = new HipHop(compositionNameTextField.getText(), compositionAuthorTextField.getText(),
                        Double.parseDouble(compositionDurationTextField.getText()), HipHopGenreComboBox.getValue());
                disc.addToDisc(temp);
            }
            else if (currType == MusicType.Pop)
            {
                Pop temp = new Pop(compositionNameTextField.getText(), compositionAuthorTextField.getText(),
                        Double.parseDouble(compositionDurationTextField.getText()), PopGenreComboBox.getValue());
                disc.addToDisc(temp);
            }
            else if (currType == MusicType.Rock)
            {
                Rock temp = new Rock(compositionNameTextField.getText(), compositionAuthorTextField.getText(),
                        Double.parseDouble(compositionDurationTextField.getText()), RockGenreComboBox.getValue());
                disc.addToDisc(temp);
            }

            compositionsTextArea.setText(disc.getDisc().toString() + "\n\n");
        } catch (InvalidDataException | NumberFormatException | NullPointerException ex) {
            compositionsTextArea.setText("");
            wrongDataLabel.setVisible(true);
            ex.printStackTrace();
        }
    }

    /**
     * Function for clearing the disc
     */
    @FXML
    private void clearDisc() {
        Manager mngr = new Manager();
        mngr.ClearDisc(disc);
        compositionsTextArea.setText(disc.getDisc().toString() + '\n');
    }

    /**
     * Function for printing all the music compositions on disc
     */
    @FXML
    private void printDiscInfo() {
        Manager mngr = new Manager();
        compositionsTextArea.setText("ALL DISK INFORMATION\n" + mngr.printDisc(disc));
    }

    /**
     * Function for counting the whole duration (in seconds) of all compositions of disc
     */
    @FXML
    private void countDuration() {
        Manager mngr = new Manager();
        compositionsTextArea.setText("Whole disk duration: " + mngr.printCountSum(disc) + " seconds.");
    }

    /**
     * Function for printing all the compositions but sorted by their names
     */
    @FXML
    private void printSortedNameInfo() {
        Manager mngr = new Manager();
        compositionsTextArea.setText("Disc' songs sorted by their name\n" + mngr.printSortName());
    }

    /**
     * Function for printing all the compositions but sorted by their authors
     */
    @FXML
    private void printSortedAuthorInfo() {
        Manager mngr = new Manager();
        compositionsTextArea.setText("Disc' songs sorted by their author\n" + mngr.printSortAuthor());
    }

    /**
     * Function for printing all the compositions but sorted by their durations
     */
    @FXML
    private void printSortedDurationInfo() {
        Manager mngr = new Manager();
        compositionsTextArea.setText("Disc' songs sorted by their duration\n" + mngr.printSortDuration());
    }

    /**
     * Function for printing all the compositions with Hip-Hop type
     */
    @FXML
    private void printAllHipHop() {
        Manager mngr = new Manager();
        compositionsTextArea.setText("All hip-hop songs from the disk\n" + mngr.printFindHipHop());
    }

    /**
     * Function for printing all the compositions with Pop type
     */
    @FXML
    private void printAllPop() {
        Manager mngr = new Manager();
        compositionsTextArea.setText("All pop songs from the disk\n" + mngr.printFindPop());
    }

    /**
     * Function for printing all the compositions with Rock type
     */
    @FXML
    private void printAllRock() {
        Manager mngr = new Manager();
        compositionsTextArea.setText("All rock songs from the disk\n" + mngr.printFindRock());
    }

    /**
     * Function for finding the composition with chosen name
     */
    @FXML
    private void findByName() {
        try {
            wrongDataLabel.setVisible(false);
            Manager mngr = new Manager();
            compositionsTextArea.setText("Disc' songs that names contain \"" + FindByNameTextField.getText() +
                    "\"\n" + mngr.printFindByName(FindByNameTextField.getText()));
        } catch (NumberFormatException | NullPointerException ex) {
            compositionsTextArea.setText("");
            wrongDataLabel.setVisible(true);
            ex.printStackTrace();
        }
    }

    /**
     * Function for finding the composition with chosen author
     */
    @FXML
    private void findByAuthor() {
        try {
            wrongDataLabel.setVisible(false);
            Manager mngr = new Manager();
            compositionsTextArea.setText("Disc' songs that authors contain \"" + FindByAuthorTextField.getText() +
                    "\"\n" + mngr.printFindByAuthorName(FindByAuthorTextField.getText()));
        } catch (NumberFormatException | NullPointerException ex) {
            compositionsTextArea.setText("");
            wrongDataLabel.setVisible(true);
            ex.printStackTrace();
        }
    }

    /**
     * Function for finding the composition with chosen duration
     */
    @FXML
    private void findByDuration() {
        try {
            wrongDataLabel.setVisible(false);
            Manager mngr = new Manager();
            compositionsTextArea.setText("Disc' songs that durations contain \"" + FindByDurationTextField.getText() +
                    "\"\n" + mngr.printFindByDuration(Double.parseDouble(FindByDurationTextField.getText())));
        } catch (NumberFormatException | NullPointerException ex) {
            compositionsTextArea.setText("");
            wrongDataLabel.setVisible(true);
            ex.printStackTrace();
        }
    }

    /**
     * Function for finding all the compositions which names start and end with chosen letters
     */
    @FXML
    private void findByNameRange() {
        try {
            wrongDataLabel.setVisible(false);
            Manager mngr = new Manager();
            compositionsTextArea.setText("Disc' songs that names start with \"" + FindByNameRangeTextField1.getText() +
                    "\" and end with \"" + FindByNameRangeTextField2.getText() + "\"\n" +
                    mngr.printFindByNameRange(FindByNameRangeTextField1.getText().charAt(0),
                    FindByNameRangeTextField2.getText().charAt(0)));
        } catch (NumberFormatException | NullPointerException ex) {
            compositionsTextArea.setText("");
            wrongDataLabel.setVisible(true);
            ex.printStackTrace();
        }
    }

    /**
     * Function for finding all the compositions which authors start and end with chosen letters
     */
    @FXML
    private void findByAuthorRange() {
        try {
            wrongDataLabel.setVisible(false);
            Manager mngr = new Manager();
            compositionsTextArea.setText("Disc' songs that authors start with \"" +
                    FindByAuthorRangeTextField1.getText() + "\" and end with \"" +
                    FindByAuthorRangeTextField2.getText() + "\"\n" +
                    mngr.printFindByAuthorNameRange(FindByAuthorRangeTextField1.getText().charAt(0),
                    FindByAuthorRangeTextField2.getText().charAt(0)));
        } catch (NumberFormatException | NullPointerException ex) {
            compositionsTextArea.setText("");
            wrongDataLabel.setVisible(true);
            ex.printStackTrace();
        }
    }

    /**
     * Function for finding all the compositions which durations start and end with chosen digits
     */
    @FXML
    private void findByDurationRange() {
        try {
            wrongDataLabel.setVisible(false);
            Manager mngr = new Manager();
            compositionsTextArea.setText("Disc' songs that durations start with \"" +
                    FindByDurationRangeTextField1.getText() + "\" and end with \"" +
                    FindByDurationRangeTextField2.getText() + "\"\n" +
                    mngr.printFindByDurationRange(Double.parseDouble(FindByDurationRangeTextField1.getText()),
                    Double.parseDouble(FindByDurationRangeTextField2.getText())));
        } catch (NumberFormatException | NullPointerException ex) {
            compositionsTextArea.setText("");
            wrongDataLabel.setVisible(true);
            ex.printStackTrace();
        }
    }
}