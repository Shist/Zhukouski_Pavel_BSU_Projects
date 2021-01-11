package util.xml.parser;

import exception.ParserException;

import model.song.Song;

import org.apache.log4j.LogManager;
import org.apache.log4j.Logger;
import util.itunes.builder.SongBuilder;
import util.itunes.director.MusicDirector;

import javax.xml.stream.XMLEventReader;
import javax.xml.stream.XMLInputFactory;
import javax.xml.stream.XMLStreamConstants;
import javax.xml.stream.XMLStreamException;
import javax.xml.stream.events.EndElement;
import javax.xml.stream.events.StartElement;
import javax.xml.stream.events.XMLEvent;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.Locale;

/**
 * StAX parser of XML
 *
 * @author Zhukouski Pavel
 * @version 1.0.0
 */

public class StAXParser implements SongParser {

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
        logger.info("Starting Stax parsing");
        List<Song> medicines = new ArrayList<>();
        MusicDirector director = new MusicDirector();
        SongBuilder builder = new SongBuilder();

        XMLInputFactory factory = XMLInputFactory.newInstance();
        XMLEventReader eventReader;
        try {
            eventReader = factory.createXMLEventReader(new FileReader(fileName));
        } catch (XMLStreamException | FileNotFoundException e) {
            throw new ParserException("Configuration StAX parser error", e);
        }
        String currentElement = "";
        boolean parsed;
        parsed = true;
        String name = "";
        String album = "";
        String genre = "";
        double time = 0;
        String ReleaseDate = null;
        boolean isFast = false;
        boolean isSlow = false;
        boolean isBlack = false;
        boolean isSingerBlack = false;
        boolean isThisCher = false;
        double electronicsPercent = 0;


        while (eventReader.hasNext()) {
            XMLEvent event = null;
            try {
                event = eventReader.nextEvent();
            } catch (XMLStreamException e) {
                throw new ParserException("Fail to get eventReader", e);
            }
            String qName = "";

            switch (event.getEventType()) {
                case XMLStreamConstants.START_ELEMENT:
                    StartElement startElement = event.asStartElement();
                    qName = startElement.getName().getLocalPart();
                    currentElement = qName;
                    if (qName.equals("name") ||
                            qName.equals("Genre") ||
                            qName.equals("Album") ||
                            qName.equals("time") ||
                            qName.equals("releaseDate") ||
                            qName.equals("isTheSingerBlack") ||
                            qName.equals("isTheSingerBlackAgain") ||
                            qName.equals("electronicsPercent") ||
                            qName.equals("isFast") ||
                            qName.equals("isSlow") ||
                            qName.equals("isThisCher")) {
                        parsed = false;
                    }
                    break;
                case XMLStreamConstants.CHARACTERS:
                    String value = event.asCharacters().getData();
                    if (!parsed) {
                        switch (currentElement) {
                            case "name":
                                name = value;
                                break;
                            case "Genre":
                                genre=value;
                                break;
                            case "releaseDate":
                                ReleaseDate =  value;
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
                    break;
                case XMLStreamConstants.END_ELEMENT:
                    EndElement endElement = event.asEndElement();
                    qName = endElement.getName().getLocalPart();
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
                    break;
            }
        }


        return medicines;
    }
}
