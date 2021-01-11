import java.io.Serializable;
import java.util.Scanner;

public class Utilities implements Serializable {
    String HouseNum;
    String FlatNum;
    String Address;
    String FIO;
    String PaymentDate;
    String PaymentAmount;
    String PenaltyInterest;
    String PaymentDelayedDays;

    public static Utilities read( Scanner fin ) {
        Utilities utilities = new Utilities();
        utilities.HouseNum = fin.nextLine();
        if ( ! fin.hasNextLine()) return null;
        utilities.FlatNum = fin.nextLine();
        if ( ! fin.hasNextLine()) return null;
        utilities.Address = fin.nextLine();
        if ( ! fin.hasNextLine()) return null;
        utilities.FIO = fin.nextLine();
        if ( ! fin.hasNextLine()) return null;
        utilities.PaymentDate = fin.nextLine();
        if ( ! fin.hasNextLine()) return null;
        utilities.PaymentAmount = fin.nextLine();
        if ( ! fin.hasNextLine()) return null;
        utilities.PenaltyInterest = fin.nextLine();
        if ( ! fin.hasNextLine()) return null;
        utilities.PaymentDelayedDays = fin.nextLine();
        return utilities;
    }

    public Utilities() {
    }

    public String toString() {
        return new String (
                HouseNum + "|" +
                        FlatNum + "|" +
                        Address + "|" +
                        FIO + "|" +
                        PaymentDate + "|" +
                        PaymentAmount + "|" +
                        PenaltyInterest + "|" +
                        PaymentDelayedDays
        );
    }
}