import java.io.PrintStream;
import java.io.Serializable;
import java.util.Date;
import java.util.GregorianCalendar;
import java.util.Scanner;

public class Utilities implements Serializable {
    String HouseNum;
    private final static String P_HouseNum = "HouseNum";
    String FlatNum;
    private final static String P_FlatNum = "FlatNum";
    String Address;
    private final static String P_Address = "Address";
    String FIO;
    private final static String P_FIO = "FIO";
    String PaymentDate;
    private final static String P_PaymentDate = "PaymentDate";
    String PaymentAmount;
    private final static String P_PaymentAmount = "PaymentAmount";
    String PenaltyInterest;
    private final static String P_PenaltyInterest = "PenaltyInterest";
    String PaymentDelayedDays;
    private final static String P_PaymentDelayedDays = "PaymentDelayedDays";

    public static Boolean nextRead( Scanner fin, PrintStream out ) {
        return nextRead( P_FIO, fin, out );
    }

    static Boolean nextRead( final String prompt, Scanner fin, PrintStream out ) {
        out.print( prompt );
        out.print( ": " );
        return fin.hasNextLine();
    }

    public static Utilities readDetailed(Scanner fin, PrintStream out)
    {
        Utilities ut = new Utilities();
        String temp;
        temp = fin.nextLine();
        if(temp.isEmpty()) return null;
        ut.FIO = temp;
        System.out.print("Enter ");
        if ( ! nextRead( P_HouseNum, fin, out ) || (temp = fin.nextLine()).isEmpty())           return null;
        ut.HouseNum = temp;
        System.out.print("Enter ");
        if ( ! nextRead( P_FlatNum, fin, out ) || (temp = fin.nextLine()).isEmpty())           return null;
        ut.FlatNum = temp;
        System.out.print("Enter ");
        if ( ! nextRead( P_Address, fin, out ) || (temp = fin.nextLine()).isEmpty())           return null;
        ut.Address = temp;
        System.out.print("Enter ");
        if ( ! nextRead( P_PaymentDate, fin, out ) || (temp = fin.nextLine()).isEmpty())           return null;
        ut.PaymentDate = temp;
        System.out.print("Enter ");
        if ( ! nextRead( P_PaymentAmount, fin, out ) || (temp = fin.nextLine()).isEmpty())           return null;
        ut.PaymentAmount = temp;
        System.out.print("Enter ");
        if ( ! nextRead( P_PenaltyInterest, fin, out ) || (temp = fin.nextLine()).isEmpty())           return null;
        ut.PenaltyInterest = temp;
        System.out.print("Enter ");
        if ( ! nextRead( P_PaymentDelayedDays, fin, out ) || (temp = fin.nextLine()).isEmpty())           return null;
        ut.PaymentDelayedDays = temp;
        return ut;
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

    public Utilities()
    {
    }

    public String toString() {
        return new String("ФИО: " + FIO + "\n" +
                "Номер дома: " + HouseNum + "\n" +
                "Номер квартиры: " + FlatNum + "\n" +
                "Адрес: " + Address + "\n" +
                "Дата платежа: " + PaymentDate + "\n" +
                "Сумма платежа: " + PaymentAmount + "\n" +
                "Процент пени: " + PenaltyInterest + "\n" +
                "Количество просроченных дней: " + PaymentDelayedDays
        );
    }
}