package runner;

import controller.Controller;
import exception.ParserException;
import exception.XMLValidatorException;
import model.ParsingModeEnum;
import model.iTunes.iTunes;
import model.iTunes.iTunesManager;
import model.song.Song;
import org.apache.log4j.LogManager;
import org.apache.log4j.Logger;

import java.util.List;
import java.util.Objects;

/**
 * Runner class which show work with parsers
 * @author Zhukouski Pavel
 * @version 1.0.0
 */
public class Runner {

    private static final String FILE_XML = "songs.xml";
    private static final String FILE_XSD = "xsd_schema.xsd";

    /**
     * logging via log4j
     */
    private static final Logger logger = LogManager.getLogger(Runner.class.getName());

    /**
     * The Client method
     *
     * @param args command line parameters
     */
    public static void main(String[] args) {
        logger.info("Start work");


        var controller = new Controller(new iTunes(new iTunesManager()));
        logger.info("Create iTunes");

        boolean result = false;
        try {
            result = controller.validate(FILE_XML, FILE_XSD);
        } catch (XMLValidatorException e) {
            logger.warn(e);
        }
        if (result) {
            logger.info("Valid xml");
        } else {
            logger.info("Failed to validate xml");
            return;
        }

        ParsingModeEnum mode = null;


        mode=ParsingModeEnum.SAX;
        List<Song> medicines;
        logger.info("Try to parse xml");
        try {
            medicines = controller.parseSongList(FILE_XML, mode);
        } catch (ParserException e) {
            logger.warn(e);
            return;
        }
        logger.info("Add parsed songs to itunes");
        for (Song medicine : Objects.requireNonNull(medicines)) {
            controller.addSong(medicine);
        }

        printSongsList("Just list of songs in itunes", controller.getItunesSongs());

        //controller.addSong(new Disco("new Disco", 2.00, "2002-09-24", "Jazz", "one", true ));
        controller.writeDOM(FILE_XML);
        printSongsList("Just list of songs in itunes after writing with DOM", controller.getItunesSongs());

        controller.writeStAX(FILE_XML);
        printSongsList("Just list of songs in itunes after writing with StAX", controller.getItunesSongs());
        logger.info("Finish work");
    }


    public static void printSongsList(String textBefore, List<Song> list) {
        logger.info("\n" + "-----------" + textBefore + "---------");
        if (list.size() > 0) {
            for (Song medicine : list) {
                logger.info("\n" + medicine);
            }
        } else {
            logger.info("No items");
        }
    }

}
