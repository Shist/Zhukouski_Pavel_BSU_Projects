import java.io.PrintStream;
import java.io.Serializable;
import java.util.Date;
import java.util.GregorianCalendar;
import java.util.Scanner;

public class SportUser implements Serializable {
    String FIO;
    private final static String P_FIO = "FIO";
    String sectionID;
    private final static String P_sectionID = "sectionID";
    String sectionInfo;
    private final static String P_sectionInfo = "sectionInfo";
    String trainerFIO;
    private final static String P_trainerFIO = "trainerFIO";
    Date startDateTime;
    private final static String P_startDateTime = "date of the start (in \"dd.mm.yyyy\" format)";
    int minutesNum;
    private final static String P_minutesNum = "number of minutes";
    double rate;
    private final static String P_rate = "rate";

    public static Boolean nextRead( Scanner fin, PrintStream out ) {
        return nextRead( P_FIO, fin, out );
    }

    static Boolean nextRead( final String prompt, Scanner fin, PrintStream out ) {
        out.print( prompt );
        out.print( ": " );
        return fin.hasNextLine();
    }

    public static SportUser readDetailed(Scanner fin, PrintStream out)
    {
        SportUser su = new SportUser();
        String temp;
        temp = fin.nextLine();
        if(temp.isEmpty()) return null;
        su.FIO = temp;
        System.out.print("Enter ");
        if ( ! nextRead( P_sectionID, fin, out ) || (temp = fin.nextLine()).isEmpty())           return null;
        su.sectionID = temp;
        System.out.print("Enter ");
        if ( ! nextRead( P_sectionInfo, fin, out ) || (temp = fin.nextLine()).isEmpty())           return null;
        su.sectionInfo = temp;
        System.out.print("Enter ");
        if ( ! nextRead( P_trainerFIO, fin, out ) || (temp = fin.nextLine()).isEmpty())           return null;
        su.trainerFIO = temp;
        System.out.print("Enter ");
        if ( ! nextRead( P_startDateTime, fin, out ) || (temp = fin.nextLine()).isEmpty())           return null;
        Date date;
        if( (date = strToDate(temp)) != null)
            su.startDateTime = date;
        else return null;
        System.out.print("Enter ");
        if ( ! nextRead( P_minutesNum, fin, out ) || (temp = fin.nextLine()).isEmpty())           return null;
        su.minutesNum = Integer.parseInt(temp);
        System.out.print("Enter ");
        if ( ! nextRead( P_rate, fin, out ) || (temp = fin.nextLine()).isEmpty())           return null;
        try{
            double d = Double.parseDouble(temp);
            su.rate = d;
        }
        catch (Exception e)
        {
            System.out.println(e.getMessage());
        }
        return su;
    }

    private static GregorianCalendar curCalendar = new GregorianCalendar();

    static Date strToDate( String dateStr ) {
        String[] strArr = dateStr.split("\\.");
        if (strArr.length != 3) {
            System.out.println("Wrong number of args!");
            return null;
        }
        int day = Integer.parseInt(strArr[0]), month = Integer.parseInt(strArr[1]), year = Integer.parseInt(strArr[2]);
        if (day < 0 || month < 0 || year < 0)
            return null;
        if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
            if(day >31) return null;
        } else {
            if (month == 2)
                if (curCalendar.isLeapYear(year)) {
                    if (day > 29)
                        return null;
                }
                else if(day > 28) return null;
            if(day > 30) return null;
        }
        return new Date(day, month, year);
    }

    public SportUser()
    {
    }

    public String toString() {
        return new String("\nUser FIO: " + FIO +
                "\nSection ID: " + sectionID +
                "\nSection information: " + sectionInfo +
                "\nTrainer's FIO: " + trainerFIO +
                "\nStart date: " + startDateTime +
                "\nNumber of minutes: " + minutesNum +
                "\nRate: " + rate
        );
    }
}
