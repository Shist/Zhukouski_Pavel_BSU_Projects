package util.xml.parser;

import exception.ParserException;
import model.song.Song;

import java.util.List;

/**
 * Parsing interface
 *
 * @author Zhukouski Pavel
 * @version 1.0.0
 */

public interface SongParser {
    List<Song> parse(String fileName) throws ParserException;
}
