import java.util.*;

public class AppLocale {
    private static final String strMsg = "Msg";
    private static Locale loc = Locale.getDefault();
    private static ResourceBundle res =
            ResourceBundle.getBundle( AppLocale.strMsg, AppLocale.loc );

    static Locale get() {
        return AppLocale.loc;
    }

    static void set( Locale loc ) {
        AppLocale.loc = loc;
        res = ResourceBundle.getBundle( AppLocale.strMsg, AppLocale.loc );
    }

    static ResourceBundle getBundle() {
        return AppLocale.res;
    }

    static String getString( String key ) {
        return AppLocale.res.getString(key);
    }

    // Resource keys:

    public static final String admin1="Galina_Petrovna_Obozova";
    public static final String city1="Minsk" ;
    public static final String city2="Gomel";
    public static final String city3="Adler";
    public static final String town1="Osipovichi";
    public static final String town2="Bobruisk";
    public static final String town3="Zhlobin";
    public static final String passenger1="Ishchanka_Mikita_Syarheevich";
    public static final String creation="creation";
}
