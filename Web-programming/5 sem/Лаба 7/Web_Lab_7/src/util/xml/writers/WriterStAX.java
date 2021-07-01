package util.xml.writers;
import model.song.Song;
import org.apache.log4j.LogManager;
import org.apache.log4j.Logger;

import javax.xml.stream.*;
import java.io.FileWriter;
import java.io.IOException;
import java.util.List;

/**
 * Class WriterStAX
 *
 * @author Zhukouski Pavel
 * @version 1.0.0
 */
public class WriterStAX {

    private static Logger LOGGER = LogManager.getLogger(WriterStAX.class);

    /**
     * The method write data to XML by StAX.
     * @param pathXml - path to XML
     * @param songs - list of TariffBonus objects
     */
    public void xmlWriterStAX(String pathXml, List<Song> songs) {
        try{
            XMLOutputFactory output = XMLOutputFactory.newInstance();
            XMLStreamWriter writer = output.createXMLStreamWriter(new FileWriter(pathXml));

            LOGGER.debug("Write data to XML by StAX.");
            writer.writeStartDocument("1.0");
            writer.writeStartElement("songs");

            for (Song s : songs) {
                writer.writeStartElement(s.getGenre());

                // costTariff
                writer.writeStartElement("name");
                writer.writeCharacters("" + s.getName());
                writer.writeEndElement();

                // costMinuteInNet
                writer.writeStartElement("Genre");
                writer.writeCharacters("" + s.getGenre());
                writer.writeEndElement();
                // costSms
                writer.writeStartElement("time");
                writer.writeCharacters("" + s.getTime());
                writer.writeEndElement();
                // costMegabyte
                writer.writeStartElement("releaseDate");
                writer.writeCharacters("" + s.getReleaseDate());
                writer.writeEndElement();

                if(s.getGenre().equals("Disco"))
                {
                    writer.writeStartElement("Album");
                    writer.writeCharacters("unknown");
                    writer.writeEndElement();
                    writer.writeStartElement("isThisCher");
                    writer.writeCharacters("true");
                    writer.writeEndElement();
                }
                else if(s.getGenre().equals("Jazz"))
                {
                    writer.writeStartElement("Album");
                    writer.writeCharacters("unknown");
                    writer.writeEndElement();
                    writer.writeStartElement("isTheSingerBlack");
                    writer.writeCharacters("true");
                    writer.writeEndElement();
                }
                else if(s.getGenre().equals("Blues"))
                {
                    writer.writeStartElement("Album");
                    writer.writeCharacters("unknown");
                    writer.writeEndElement();
                    writer.writeStartElement("isTheSingerBlackAgain");
                    writer.writeCharacters("true");
                    writer.writeEndElement();
                }
                else if(s.getGenre().equals("Rap"))
                {
                    writer.writeStartElement("electronicsPercent");
                    writer.writeCharacters("51");
                    writer.writeEndElement();
                    writer.writeStartElement("isFast");
                    writer.writeCharacters("true");
                    writer.writeEndElement();
                }
                else
                {
                    writer.writeStartElement("electronicsPercent");
                    writer.writeCharacters("10");
                    writer.writeEndElement();
                    writer.writeStartElement("isSlow");
                    writer.writeCharacters("true");
                    writer.writeEndElement();
                }

                writer.writeEndElement();
            }
            writer.writeEndElement();

            writer.writeEndDocument();
            writer.flush();
            writer.close();
        } catch(XMLStreamException | IOException e){
            e.printStackTrace();
        }
    }
}
