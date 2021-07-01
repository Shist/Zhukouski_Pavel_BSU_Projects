package controller;

import exception.ParserException;
import exception.XMLValidatorException;
import model.ParsingModeEnum;
import model.iTunes.iTunes;
import model.song.New.Rap;
import model.song.Old.Disco;
import model.song.Song;
import org.apache.log4j.LogManager;
import org.apache.log4j.Logger;
import util.xml.XMLValidator;
import util.xml.parser.DOMParser;
import util.xml.parser.SAXParser;
import util.xml.parser.StAXParser;
import util.xml.writers.WriterDOM;
import util.xml.writers.WriterStAX;

import java.util.List;

/**
 * Basic class demonstrates functions of classes
 *
 * @author Zhukouski Pavel
 * @version 1.0.0
 */
public class Controller {

    /**
     * logging via log4j
     */
    private static final Logger logger = LogManager.getLogger(Controller.class.getName());

    /**
     * itunes
     */
    private iTunes itunes;


    public iTunes getItunes() { return itunes;}



    /*
     * Constructor that create controller
     *
     * @param pharmacy pharmacy
     */
    public Controller(iTunes itunes) {
        this.itunes = itunes;
    }


    public List<Song> parseSongList(String file, ParsingModeEnum mode) throws ParserException {
        switch (mode) {
            case DOM:
                return (new DOMParser()).parse(file);
            case SAX:
                return (new SAXParser()).parse(file);
            case StAX:
                return (new StAXParser()).parse(file);
            default:
                return null;
        }
    }

    /**
     * Validates XML file with given schema
     * @param file XML file
     * @param schema XSD file
     * @return true if validation succeed, otherwise false
     */
    public boolean validate(String file, String schema) throws XMLValidatorException {
        boolean result = XMLValidator.validate(file, schema);
        if (result) {
            logger.info("Validation succeed");
        } else {
            logger.info("Validation failed");
        }
        return result;
    }

    /**
     * Method to add new song
     */
    public void addSong(Song s) {
        itunes.addSong(s);
    }

    /**
     * Method to demonstrate work with  classes
     *
     * @return some work result to show it on view
     */
    public List<Song> getItunesSongs() {
        return itunes.getSongs();
    }

    /**
     * Method to demonstrate work of sorting method by name
     *
     * @param isRevesed determinate order of sorted list
     * @return some work result to show it on view
     */
    public List<Song> getiTunesSongsSortedByName(boolean isRevesed) {
        return itunes.sortSongsByName(isRevesed);
    }

    /**
     * Method to demonstrate work of sorting method by time
     *
     * @param isRevesed determinate order of sorted list
     * @return some work result to show it on view
     */
    public List<Song> getiTunesSongsSortedByPrice(boolean isRevesed) {
        return itunes.sortSongsByTime(isRevesed);
    }

    /**
     * Method to demonstrate work of sorting method by release date
     *
     * @param isRevesed determinate order of sorted list
     * @return some work result to show it on view
     */
    public List<Song> getiTunesSongsSortedByManufactureDate(boolean isRevesed) {
        return itunes.sortSongsByReleaseDate(isRevesed);
    }

    /**
     * Method to demonstrate work of selecting method by name
     *
     * @param name determinate order of sorted list
     * @return some work result to show it on view
     */
    public List<Song> getiTunesSongsSelectedByName(String name) {
        return itunes.selectSongsByName(name);
    }

    /**
     * Method to demonstrate work of selecting method by range
     *
     * @param mint min  of range
     * @param maxt max  of range
     * @return some work result to show it on view
     */
    public List<Song> getiTunesSongsSelectedByPriceRange(double mint, double maxt) {
        return itunes.selectSongsByTimeRange(mint, maxt);
    }

    /**
     * Method to demonstrate work of selecting method by price
     *
     * @param t time
     * @return some work result to show it on view
     */
    public List<Song> getiTunesSongsSelectedByPrice(double t) {
        return itunes.selectSongsByTime(t);
    }

    public void writeDOM(String path){
        WriterDOM writerDOM = new WriterDOM();
        itunes.addSong(new Disco("new Disco", 2.00, "2002-09-24", "Jazz", "one", true ));
        writerDOM.xmlWriterDOM(path, this.getItunesSongs());
    }

    public void writeStAX(String path){
        WriterStAX writerStAX = new WriterStAX();
        itunes.addSong((new Rap("new Rap", 3.00, "2019-02-02", "Rap", 30, true)));

        writerStAX.xmlWriterStAX(path, this.getItunesSongs());
    }
}