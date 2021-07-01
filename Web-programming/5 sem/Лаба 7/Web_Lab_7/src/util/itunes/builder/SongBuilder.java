package util.itunes.builder;


import model.song.New.House;
import model.song.New.Rap;
import model.song.Old.Blues;
import model.song.Old.Disco;
import model.song.Old.Jazz;
import model.song.Song;

import java.util.Date;

/**
 * medicine builder
 *
 * @author Zhukouski Pavel
 * @version 1.0.0
 */
public class SongBuilder implements Builder {

    /**
     * name of song
     */
    private String name;

    /**
     * time of song
     */
    private Double time;

    /**
     * release date of song
     */
    private String relaseeDate;

    /**
     * genre of song
     */
    private String genre;

    /**
     * electronic sound percentage
     */
    private Double electronicSoundsPercent;

    /**
     * album
     */
    private String album;

    /**
     * is fast
     */
    private Boolean isFast;

    /**
     * is slow
     */
    private Boolean isSlow;

    /**
     * is this Cher's song
     */
    private Boolean isCher;

    /**
     * is this Singer Black Again
     */
    private Boolean isSingerBlackAgain;

    /**
     * is this singer black
     */
    private Boolean isSingerBlack;

    /**
     * set name
     */
    @Override
    public void setName(String name) {
        this.name = name;
    }

    /**
     * set time
     */
    @Override
    public void setTime(double time) {
        this.time = time;
    }

    /**
     * set release date
     */
    @Override
    public void setReleaseDate(String date) {
        this.relaseeDate = date;
    }

    /**
     * set genre
     */
    @Override
    public void setGenre(String g) {
        genre = g;
    }

    /**
     * set  percent
     */
    @Override
    public void setElectronicSoundsPercent(double percent) {
        electronicSoundsPercent = percent;
    }

    /**
     * set album
     */
    @Override
    public void setAlbum(String alb) {
        album = alb;
    }

    /**
     * set if is fast
     */
    @Override
    public void isFast(boolean isF) {
        this.isFast = isF;
    }

    /**
     * set if is slow
     */
    @Override
    public void isSlow(boolean isSl) {
        this.isSlow = isSl;
    }

    /**
     * set if its Cher
     */
    @Override
    public void setIsCher(boolean cher) {
        isCher = cher;
    }

    /**
     * set isSingerBlackAgain
     */
    @Override
    public void setIsSingerBlackAgain(boolean singerBlackAgain) {
        this.isSingerBlackAgain = singerBlackAgain;
    }

    /**
     * set isSingerBlack
     */
    @Override
    public void setIsSingerBlack(boolean isSingerBlack) {
        this.isSingerBlack = isSingerBlack;
    }

    /**
     * make all fields as null
     */
    @Override
    public void reset() {
        name = null;
        time = null;
        relaseeDate = null;
        genre = null;
        electronicSoundsPercent = null;
        album = null;
        isFast = null;
        isSlow = null;
        isCher = null;
        isSingerBlackAgain = null;
        isSingerBlack = null;
    }

    /**
     * configure Song item
     *
     * @return song item with configured fields
     * @throws IllegalArgumentException if some fields doesn`t set
     */
    public Song buildSongItem() {
        if (name == null
                || time == null
                || relaseeDate == null
                || genre == null) {
            throw new IllegalArgumentException();
        }
        if (electronicSoundsPercent != null) {
            if (isFast != null) {
                return new Rap(name,
                        time,
                        relaseeDate,
                        genre,
                        electronicSoundsPercent,
                        isFast);
            } else if (isSlow != null) {
                return new House(name,
                        time,
                        relaseeDate,
                        genre,
                        electronicSoundsPercent,
                        isSlow);
            } else {
                throw new IllegalArgumentException();
            }
        } else if (album != null) {
            if (isCher != null) {
                return new Disco(name,
                        time,
                        relaseeDate,
                        genre,
                        album,
                        isCher);
            } else if (isSingerBlackAgain != null) {
                return new Blues(name,
                        time,
                        relaseeDate,
                        genre,
                        album,
                        isSingerBlackAgain);
            } else if (isSingerBlack != null) {
                return new Jazz(name,
                        time,
                        relaseeDate,
                        genre,
                        album,
                        isSingerBlack);
            } else {
                throw new IllegalArgumentException();
            }
        }
        throw new IllegalArgumentException();
    }

}
