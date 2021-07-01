package util.xml.parser;

import exception.ParserException;
import model.song.Song;
//import org.apache.logging.log4j.LogManager;
//import org.apache.logging.log4j.Logger;
import org.apache.log4j.LogManager;
import org.apache.log4j.Logger;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;
import util.itunes.builder.SongBuilder;
import util.itunes.director.MusicDirector;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import java.io.File;
import java.io.IOException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.Locale;


/**
 * DOM parser of XML
 *
 * @author Zhukouski Pavel
 * @version 1.0.0
 */

public class DOMParser implements SongParser {

    private static final Logger logger = LogManager.getLogger("Parser");

    /**
     * Parse XML file to collective using DOM parser
     *
     * @param fileName name of the file that contains medicines stored in XML format
     * @return parsed medicines list
     * @throws ParserException if some error occurred while parsing XML file
     */
    @Override
    public List<Song> parse(String fileName) throws ParserException {
        logger.info("Starting DOM parsing");
        List<Song> medicines = new ArrayList<>();
        MusicDirector director = new MusicDirector();
        SongBuilder builder = new SongBuilder();

        File inputFile = new File(fileName);
        DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
        DocumentBuilder dBuilder = null;
        Document doc = null;
        try {
            dBuilder = dbFactory.newDocumentBuilder();
            doc = dBuilder.parse(inputFile);
        } catch (SAXException | IOException | ParserConfigurationException e) {
            throw new ParserException("Configuration DOM parser error", e);
        }
        doc.getDocumentElement().normalize();


        NodeList discoNodes = doc.getElementsByTagName("Disco");
        NodeList jazzNodes = doc.getElementsByTagName("Jazz");
        NodeList bluesNodes = doc.getElementsByTagName("Blues");
        NodeList rapNodes = doc.getElementsByTagName("Rap");
        NodeList houseNodes = doc.getElementsByTagName("House");


        for (int i = 0; i < discoNodes.getLength(); ++i) {
            Node node = discoNodes.item(i);
            if (node.getNodeType() == Node.ELEMENT_NODE) {
                Element element = (Element) node;

                String name = element.getElementsByTagName("name").item(0).getTextContent();
                String genre = element.getElementsByTagName("Genre").item(0).getTextContent();
                String album = element.getElementsByTagName("Album").item(0).getTextContent();

                boolean isThisCher = Boolean.parseBoolean(element.getElementsByTagName("isThisCher").item(0).getTextContent());

                medicines.add(director.manufactureDisco(builder,
                        name,
                        genre,
                        album,
                        //manufactureDate,
                        isThisCher));
                builder.reset();
            }
        }

        for (int i = 0; i < jazzNodes.getLength(); ++i) {
            Node node = jazzNodes.item(i);
            if (node.getNodeType() == Node.ELEMENT_NODE) {
                Element element = (Element) node;

                String name = element.getElementsByTagName("name").item(0).getTextContent();
                String genre = element.getElementsByTagName("Genre").item(0).getTextContent();
                String album = element.getElementsByTagName("Album").item(0).getTextContent();


                boolean isBlack= Boolean.parseBoolean(element.getElementsByTagName("isTheSingerBlack").item(0).getTextContent());
                //double maxDailyDoseInMg = Double.parseDouble(element.getElementsByTagName("maxDailyDoseInMg").item(0).getTextContent());


                medicines.add(director.manufactureJazz(builder,
                        name,
                        genre,
                        album,
                        isBlack));
                builder.reset();
            }
        }

        for (int i = 0; i < bluesNodes.getLength(); ++i) {
            Node node = bluesNodes.item(i);
            if (node.getNodeType() == Node.ELEMENT_NODE) {
                Element element = (Element) node;

                String name = element.getElementsByTagName("name").item(0).getTextContent();
                String genre = element.getElementsByTagName("Genre").item(0).getTextContent();
                String album = element.getElementsByTagName("Album").item(0).getTextContent();
                Date manufactureDate = null;


                boolean isSingerBlack = Boolean.parseBoolean(element.getElementsByTagName("isTheSingerBlackAgain").item(0).getTextContent());
                //double fluidityPercent = Double.parseDouble(element.getElementsByTagName("fluidityPercent").item(0).getTextContent());


                medicines.add(director.manufactureBlues(builder,
                        name,
                        genre,
                        album,
                        isSingerBlack));
                builder.reset();
            }
        }

        for (int i = 0; i < rapNodes.getLength(); ++i) {
            Node node = rapNodes.item(i);
            if (node.getNodeType() == Node.ELEMENT_NODE) {
                Element element = (Element) node;

                String name = element.getElementsByTagName("name").item(0).getTextContent();

                double electronicsPercent = Double.parseDouble(element.getElementsByTagName("electronicsPercent").item(0).getTextContent());
                boolean isFast = Boolean.parseBoolean(element.getElementsByTagName("isFast").item(0).getTextContent());

                medicines.add(director.manufactureRap(builder,
                        name,
                        electronicsPercent,
                        isFast
                ));
                builder.reset();
            }
        }

        for (int i = 0; i < houseNodes.getLength(); ++i) {
            Node node = houseNodes.item(i);
            if (node.getNodeType() == Node.ELEMENT_NODE) {
                Element element = (Element) node;

                String name = element.getElementsByTagName("name").item(0).getTextContent();
                double electronicsPercent = Double.parseDouble(element.getElementsByTagName("electronicsPercent").item(0).getTextContent());
                boolean isSlow = Boolean.parseBoolean(element.getElementsByTagName("isSlow").item(0).getTextContent());


                medicines.add(director.manufactureHouse(builder,
                        name,
                        electronicsPercent,
                        isSlow
                ));
                builder.reset();
            }
        }

        logger.info("Finish DOM parsing");
        return medicines;
    }

}
