import java.io.Serializable;
import java.util.ArrayList;
import java.text.DateFormat;
import java.util.Date;
public class Administrator implements Serializable{
    private static final long serialVersionUID = 1L;
    public final Date creationDate = new Date();
    public String getCreationDate() {
        DateFormat dateFormatter = DateFormat.getDateTimeInstance(
                DateFormat.DEFAULT, DateFormat.DEFAULT, AppLocale.get());
        String dateOut = dateFormatter.format(creationDate);
        return dateOut;
    }
    String name;
    static ArrayList<Train> trains = new ArrayList<Train>();

    public Administrator(String n) {
        this.name = n;
    }

    public static void addTrain(Train tr) {
        Administrator.trains.add(tr);
    }

    public Check makeCheck(int num, Request req) {
        Train tr = new Train();
        boolean flag =false;
        for (int i = 0; i < Administrator.trains.size(); i++) {
            if (Administrator.trains.get(i).number == num) {
                tr = Administrator.trains.get(i);
                flag=true;
                break;
            }
        }
        if(flag)
        {
            int prIndex = -1;
            for (int i = 0; i < tr.prices.length; i++) {
                if (req.destination == tr.stations[i]) {
                    prIndex = i;
                    break;
                }
            }
            if (prIndex == -1) {
                Check ch = new Check(req, tr.prices[prIndex]);
                return ch;
            } else {
                Check ch = new Check(req, -1);
                return ch;
            }
        }
        else
        {
            Check ch = new Check(req, -1);
            return ch;
        }

    }

    public void showTrains(Request req) {
        boolean flag = false;
        for (int i = 0; i < Administrator.trains.size(); i++) {
            for (int j = 0; j < Administrator.trains.get(i).stations.length; j++) {
                if (req.destination == Administrator.trains.get(i).stations[j]) {
                    flag = true;
                    System.out.println("Number of the train:" + Administrator.trains.get(i).number + ", name of the train" + Administrator.trains.get(i).initialStation + "-" + Administrator.trains.get(i).endStation + ".");
                    break;
                }
            }

        }
        if (!flag) {
            System.out.println("Sorry, we can't find train with such parameters");
        } else {
            System.out.println("Make your choice, please");
        }
    }
}
