import java.applet.*;
import java.awt.*;
import java.util.ArrayList;
import java.util.Random;

public class Cars extends Applet {

    ArrayList<String> carName;
    ArrayList<Double> voted;
    ArrayList<Color> colors;

    int Graph_offset = 20;
    int Graph_Diameter = 150;

    private void fillParams() {
        carName = new ArrayList<>();
        voted = new ArrayList<>();
        String par;
        for (int i = 1;; i++) {
            if((par = getParameter(String.format("param_%d", i))) == null)
                break;
            String[] parSplitted = par.split(" ");
            voted.add(Double.parseDouble(parSplitted[0]));
            carName.add(parSplitted[1]);
        }
        int totalVotes = 0;
        for (double a : voted) {
            totalVotes += a;
        }
        for (int i = 0; i < voted.size(); i++) {
            voted.set(i, (1.0 * voted.get(i) / totalVotes) * 100);
        }
    }

    private Color getRandomColor() {
        Random rand = new Random();
        return new Color(rand.nextInt(256), rand.nextInt(256),rand.nextInt(256));
    }

    public void init() {
        fillParams();
        colors = new ArrayList<>();
        for(int i = 0; i < voted.size(); i++) {
            colors.add(getRandomColor());
        }
    }

    public void paint(Graphics g) {
        double start_angle, pie_size;
        double sub_total = 0;
        start_angle = 0;
        for (int i = 0; i < carName.size(); i++) {
            sub_total += voted.get(i);
            pie_size = sub_total * 360 / 100 - start_angle;
            g.setColor(colors.get(i));
            g.fillArc(Graph_offset, Graph_offset, Graph_Diameter,
                    Graph_Diameter, (int)Math.ceil(start_angle), (int)Math.ceil(pie_size));

            start_angle += pie_size;
            g.fillRect(Graph_offset + Graph_Diameter + 10,
                    Graph_offset + i * 20, 15, 15);
            g.setColor(Color.black);
            g.drawString(carName.get(i), Graph_offset +
                            Graph_Diameter + 10 + 20,
                    Graph_offset + i * 20 + 15);
        }
    }
}
