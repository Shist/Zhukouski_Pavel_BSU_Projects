package util.itunes.director;

import model.song.Song;
import util.itunes.builder.Builder;

import java.util.Date;
import java.util.Random;

/**
 * director that help builder to build song items
 *
 * @author Zhukouski Pavel
 * @version 1.0.0
 */
public class MusicDirector {

    private Random random = new Random();

    /**
     * manufacture Disco
     *
     * @param builder     to build some song
     * @param name        name of song
     * @param genre  genre of the song
     * @param album album
     * @param isCher    is it Cher
     * @return configured track
     */
    public Song manufactureDisco(Builder builder, String name, String genre, String album, boolean isCher) {
        builder.setName(name);
        builder.setTime(3.27);
        builder.setReleaseDate(new Date().toString());
        builder.setGenre(genre);
        builder.setAlbum(album);
        builder.setIsCher(isCher);
        return builder.buildSongItem();
    }

    /**
     * manufacture Blues
     *
     * @param builder          to build some song
     * @param name             name of song
     * @param genre     genre
     * @param album album
     * @param isSingerBlack is singer black
     * @return configured track
     */
    public Song manufactureBlues(Builder builder, String name, String genre, String album, boolean isSingerBlack) {
        builder.setName(name);
        builder.setTime(3.20);
        builder.setReleaseDate(new Date().toString());
        builder.setGenre(genre);
        builder.setAlbum(album);
        builder.setIsSingerBlack(isSingerBlack);
        return builder.buildSongItem();
    }

    /**
     * manufacture Jazz
     *
     * @param builder     to build some song
     * @param name        name of song
     * @param genre genre
     * @param isBlack if the singer is black
     * @param album album
     * @return configured track
     */
    public Song manufactureJazz(Builder builder, String name, String genre, String album,  boolean isBlack) {
        builder.setName(name);
        builder.setTime(2.40);
        builder.setReleaseDate(new Date().toString());
        builder.setGenre(genre);
        builder.setAlbum(album);
        builder.setIsSingerBlackAgain(isBlack);
        return builder.buildSongItem();
    }

    /**
     * manufacture Rap
     *
     * @param builder         to build some song
     * @param name            name of song
     * @param electronicsPercent electronic sounds percentage
     * @param isFast       is it fast
     * @return configured track
     */
    public Song manufactureRap(Builder builder, String name, double electronicsPercent, boolean isFast) {
        builder.setName(name);
        builder.setTime(4.41);
        builder.setReleaseDate(new Date().toString());
        builder.setGenre("Rap");
        builder.setElectronicSoundsPercent(electronicsPercent);
        builder.isFast(isFast);
        return builder.buildSongItem();
    }

    /**
     * manufacture house
     *
     * @param builder         to build some song
     * @param name            name of song
     * @param electronicsPercent electronic sounds percentage
     * @param isSlow       is it slow
     * @return configured track
     */
    public Song manufactureHouse(Builder builder, String name, double electronicsPercent, boolean isSlow) {
        builder.setName(name);
        builder.setTime(5.05);
        builder.setReleaseDate(new Date().toString());
        builder.setGenre("House");
        builder.setElectronicSoundsPercent(electronicsPercent);
        builder.isSlow(isSlow);
        return builder.buildSongItem();
    }
}
