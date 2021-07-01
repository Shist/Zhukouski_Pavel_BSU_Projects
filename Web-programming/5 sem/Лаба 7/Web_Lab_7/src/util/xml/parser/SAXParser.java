package util.xml.parser;

import exception.ParserException;

import model.song.Song;
import org.apache.log4j.LogManager;
import org.apache.log4j.Logger;
import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;
import util.itunes.builder.SongBuilder;
import util.itunes.director.MusicDirector;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParserFactory;
import java.io.File;
import java.io.IOException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.Locale;

/**
 * SAX parser of XML
 *
 * @author Zhukouski Pavel
 * @version 1.0.0
 */

public class SAXParser implements SongParser {

    private static final Logger logger = LogManager.getLogger("Parser");

    /**
     * Parse XML file to collective using DOM parser
     *
     * @param fileName name of the file that contains songs stored in XML format
     * @return parsed songs list
     * @throws ParserException if some error occurred while parsing XML file
     */
    @Override
    public List<Song> parse(String fileName) throws ParserException {
        logger.info("Starting SAX parsing");
        List<Song> medicines;

        try {
            File inputFile = new File(fileName);
            SAXParserFactory factory = SAXParserFactory.newInstance();
            javax.xml.parsers.SAXParser saxParser = factory.newSAXParser();
            Handler handler = new Handler();
            saxParser.parse(inputFile, handler);
            medicines = handler.getSongs();
        } catch (IOException | SAXException | ParserConfigurationException e) {
            throw new ParserException("Configuration SAX parser error", e);
        }

        logger.info("Finish SAX parsing");
        return medicines;
    }

    /**
     * Tags handler
     */
    private class Handler extends DefaultHandler {

        private MusicDirector director = new MusicDirector();

        private SongBuilder builder = new SongBuilder();

        private List<Song> medicines = new ArrayList<>();

        private boolean parsed = true;
        private String currentElement;

        private String name;
        private String genre;
        private String album;
        private double time;
        private String ReleaseDate;
        private boolean isBlack;
        private boolean isSingerBlack;
        private double electronicsPercent;
        private boolean isFast ;
        private boolean isSlow;
        private boolean isThisCher;

        @Override
        public void startElement(String uri, String localName, String qName, Attributes attributes) throws SAXException {
            currentElement = qName;
            if (qName.equals("name") ||
                    qName.equals("Genre") ||
                    qName.equals("Album") ||
                    qName.equals("time") ||
                    qName.equals("releaseDate") ||
                    qName.equals("isTheSingerBlack") ||
                    qName.equals("isTheSingerSingerBlack") ||
                    qName.equals("electronicsPercent") ||
                    qName.equals("isFast") ||
                    qName.equals("isSlow") ||
                    qName.equals("isThisCher")) {
                parsed = false;
            }
        }

        @Override
        public void endElement(String uri, String localName, String qName) throws SAXException {
            switch (qName) {
                case "Disco":
                    medicines.add(director.manufactureDisco(builder,
                            name,
                            genre,
                            album,
                            //manufactureDate,
                            isThisCher));
                    break;
                case "Jazz":
                    medicines.add(director.manufactureJazz(builder,
                            name,
                            genre,
                            album,
                            isBlack));
                    break;
                case "Blues":
                    medicines.add(director.manufactureBlues(builder,
                            name,
                            genre,
                            album,
                            isSingerBlack));
                    break;
                case "Rap":
                    medicines.add(director.manufactureRap(builder,
                            name,
                            electronicsPercent,
                            isFast));
                    break;
                case "House":
                    medicines.add(director.manufactureHouse(builder,
                            name,
                            electronicsPercent,
                            isSlow
                    ));
                    break;
            }
            builder.reset();
        }

        @Override
        public void characters(char[] ch, int start, int length) throws SAXException {
            String value = new String(ch, start, length);
            if (!parsed) {
                switch (currentElement) {
                    case "name":
                        name = value;
                        break;
                    case "Genre":
                        genre=value;
                        break;
                    case "releaseDate":
                        ReleaseDate = value;
                        break;
                    case "Album":
                        album = value;
                        break;
                    case "time":
                        time=Double.parseDouble(value);
                        break;
                    case "isFast":
                        isFast = Boolean.parseBoolean(value);
                        break;
                    case "electronicsPercent":
                        electronicsPercent = Double.parseDouble(value);
                        break;
                    case "isSlow":
                        isSlow = Boolean.parseBoolean(value);
                        break;
                    case "isTheSingerBlack":
                        isBlack = Boolean.parseBoolean(value);
                        break;
                    case "isTheSingerBlackAgain":
                        isSingerBlack = Boolean.parseBoolean(value);
                        break;
                    case "isThisCher":
                        isThisCher = Boolean.parseBoolean(value);
                        break;
                }

                parsed = true;
            }


        }


        public List<Song> getSongs() {
            return medicines;
        }
    }
}

