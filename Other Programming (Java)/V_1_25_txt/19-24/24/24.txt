// Вариант 24.
// Cоздать апплет со строкой, которая движется горизонтально,
// отражаясь от границ апплета и меняя при этом свой цвет на цвет.
// Строка вводится через параметры апплета.
import java.applet.Applet;
import java.awt.*;

public class Main extends Applet
{
    private static final long serialVersionUID = 1L;
    private boolean animationDone = false;

    boolean hittedEdge = false;
    String str;

    int windowWidth = this.getWidth();
    int windowHeight = this.getHeight();

    int ctr = 0;

    public void init() {
        str = getParameter("text");

        windowWidth = this.getWidth();
        windowHeight = this.getHeight();


        new Thread(() -> {
            while (!animationDone) {
                updateAnimation();
                repaint();
                delayAnimation();
            }
        }).start();
    }

    public void delayAnimation() {
        try {
            Thread.sleep(10);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    public void updateAnimation() {
        if(!hittedEdge)
            ctr++;
        else
            ctr--;
    }
    public void paint(Graphics g) {
        if (ctr+g.getFontMetrics().stringWidth(str)>windowWidth) {
            hittedEdge = !hittedEdge;
        }
        if (ctr==0) {
            hittedEdge = !hittedEdge;
        }
        if (hittedEdge) {
            g.setColor(Color.RED);
            g.drawString(str, ctr, windowHeight / 2);
        } else  {
            g.setColor(Color.BLACK);
            g.drawString(str, ctr, windowHeight / 2);
        }
    }
}
