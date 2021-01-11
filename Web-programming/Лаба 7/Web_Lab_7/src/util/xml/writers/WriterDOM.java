package util.xml.writers;

import model.song.Song;
import org.apache.log4j.LogManager;
import org.apache.log4j.Logger;
import org.w3c.dom.Document;
import org.w3c.dom.Element;

import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerConfigurationException;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.util.List;

/**
 * Class WriterDOM
 *
 * @author Zhukouski Pavel
 * @version 1.0.0
 */
public class WriterDOM {

    private static Logger LOGGER = LogManager.getLogger(WriterDOM.class);

    /**
     * The method write data to XML by DOM.
     * @param pathXml - path to XML
     * @param songs - list of TariffBonus objects
     */
    public void xmlWriterDOM(String pathXml, List<Song> songs) {
        try {
            Document document = DocumentBuilderFactory.newInstance().newDocumentBuilder().newDocument();

            LOGGER.debug("The method write data to XML by DOM.");

            Element tariffs = document.createElement("songs");
            document.appendChild(tariffs);

            for (Song s : songs) {
                Element tb = document.createElement(s.getGenre());
                tariffs.appendChild(tb);

                Element costTariff = document.createElement("name");
                costTariff.setTextContent(""+s.getName());
                tb.appendChild(costTariff);

                Element costMinuteInNet = document.createElement("Genre");
                costMinuteInNet.setTextContent(""+s.getGenre());
                tb.appendChild(costMinuteInNet);

                Element costSms = document.createElement("time");
                costSms.setTextContent(""+s.getTime());
                tb.appendChild(costSms);

                Element costMegabyte = document.createElement("releaseDate");
                costMegabyte.setTextContent(""+s.getReleaseDate());
                tb.appendChild(costMegabyte);

                if(s.getGenre().equals("Disco")) {
                    Element cost = document.createElement("Album");
                    cost.setTextContent("unknown") ;
                    tb.appendChild(cost);
                    Element cost1 = document.createElement("isThisCher");
                    cost1.setTextContent("true") ;
                    tb.appendChild(cost1);
                }
                else if(s.getGenre().equals("Jazz")) {
                    Element cost = document.createElement("Album");
                    cost.setTextContent("unknown") ;
                    tb.appendChild(cost);
                    Element cost1 = document.createElement("isTheSingerBlack");
                    cost1.setTextContent("true") ;
                    tb.appendChild(cost1);
                }
                else if(s.getGenre().equals("Blues")) {
                    Element cost = document.createElement("Album");
                    cost.setTextContent("unknown") ;
                    tb.appendChild(cost);
                    Element cost1 = document.createElement("isTheSingerBlackAgain");
                    cost1.setTextContent("true") ;
                    tb.appendChild(cost1);
                }
                else if(s.getGenre().equals("Rap")) {
                    Element cost = document.createElement("electronicsPercent");
                    cost.setTextContent("0.0") ;
                    tb.appendChild(cost);
                    Element cost1 = document.createElement("isFast");
                    cost1.setTextContent("true") ;
                    tb.appendChild(cost1);
                }
                else  {
                    Element cost = document.createElement("electronicsPercent");
                    cost.setTextContent("0.0") ;
                    tb.appendChild(cost);
                    Element cost1 = document.createElement("isSlow");
                    cost1.setTextContent("true") ;
                    tb.appendChild(cost1);
                }
            }

            Transformer t=TransformerFactory.newInstance().newTransformer();
            t.transform(new DOMSource(document), new StreamResult(new FileOutputStream(pathXml)));

            System.out.println("Write completed.");

        } catch (ParserConfigurationException | TransformerException | FileNotFoundException e) {
            e.printStackTrace();
        }
    }
}
