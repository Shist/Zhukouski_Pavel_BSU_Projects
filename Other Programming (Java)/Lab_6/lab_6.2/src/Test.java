import java.util.*;
import java.io.*;

public class Test {

    static Locale createLocale( String[] args )	{
        if ( args.length == 2 ) {
            return new Locale( args[0], args[1] );
        } else if( args.length == 4 ) {
            return new Locale( args[2], args[3] );
        }
        return null;
    }
    static void setupConsole(String[] args) {
        if ( args.length >= 2 ) {
            if ( args[0].compareTo("-encoding")== 0 ) {
                try {
                    System.setOut( new PrintStream( System.out, true, args[1] ));
                } catch ( UnsupportedEncodingException ex ) {
                    System.err.println( "Unsupported encoding: " + args[1] );
                    System.exit(1);
                }
            }
        }
    }
    public static void main(String[] args) {
        try {
            setupConsole( args );
            Locale loc = createLocale( args );
            if ( loc == null ) {
                System.err.println(
                        "Invalid argument(s)\n" +
                                "Syntax: [-encoding ENCODING_ID] language country\n" +
                                "Example: -encoding Cp855 be BY" );
                System.exit(1);
            }
            AppLocale.set( loc );
            Administrator admin = new Administrator(AppLocale.getString( AppLocale.admin1));
            System.out.println(AppLocale.getString( AppLocale.creation)+":");
            System.out.println(admin.creationDate);
            System.out.println(admin.name);
            String[] st1 = {AppLocale.getString( AppLocale.city1), AppLocale.getString( AppLocale.city2), AppLocale.getString( AppLocale.city3)};
            int[] pr1 = {0, 10, 15};
            Train tr1 = new Train(718, st1, st1[0], st1[2], pr1);
            String[] st2 = {AppLocale.getString( AppLocale.city1), AppLocale.getString( AppLocale.city2)};
            int[] pr2 = {0, 13};
            Train tr2 = new Train(709, st2, st2[0], st2[1], pr2);
            String[] st3 = {AppLocale.getString( AppLocale.city1), AppLocale.getString( AppLocale.town1), AppLocale.getString( AppLocale.town2), AppLocale.getString( AppLocale.town3), AppLocale.getString( AppLocale.city2)};
            int[] pr3 = {0, 3, 5, 7, 11};
            Train tr3 = new Train(720, st3, st3[0], st3[4], pr1);
            Administrator.addTrain(tr1);
            Administrator.addTrain(tr2);
            Administrator.addTrain(tr3);
            ConnectorAdmin conAdm = new ConnectorAdmin("adm.dat");
            conAdm.write(admin);
            Administrator newAdmin = conAdm.read();
            System.out.println(AppLocale.getString( AppLocale.creation)+":");
            System.out.println(newAdmin.creationDate);
            Passenger pass = new Passenger(AppLocale.getString( AppLocale.passenger1));
            Request req = pass.makeRequest(AppLocale.getString( AppLocale.city1), "12:15", "13.10.2018");
            newAdmin.showTrains(req);
            Check ch = admin.makeCheck(pass.chooseTrain(), req);
            ch.show();
        } catch (Exception e) {
            System.err.println(e);
        }
    }

}

