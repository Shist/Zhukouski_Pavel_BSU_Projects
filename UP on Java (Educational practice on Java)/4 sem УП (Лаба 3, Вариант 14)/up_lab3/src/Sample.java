import javax.swing.*;
import java.awt.*;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

public class Sample implements GraphSample {

    private static final int WIDTH = 800, HEIGHT = 200;

    public String getName() { return "Line: Ordinary Cycloid (variant 14)";}

    public int getWidth() {
        return WIDTH;
    }

    public int getHeight() {
        return HEIGHT;
    }

    public void draw(Graphics2D g, Component c) {
        Shape shape = new MyShape(400,100,75);
        Stroke stroke = new MyStroke(4);
        g.setStroke(stroke);
        g.setPaint(Color.black);
        g.draw(shape);
    }
}

class GraphSampleFrame extends JFrame {
    GraphSampleFrame(final GraphSample[] examples) {
        super("Line: Ordinary Cycloid (variant 14), made by Zhukovskiy Pavel");
        Container cpane = getContentPane();
        cpane.setLayout(new BorderLayout());
        final JTabbedPane tpane = new JTabbedPane();
        cpane.add(tpane, BorderLayout.CENTER);

        JMenuBar menubar = new JMenuBar();
        this.setJMenuBar(menubar);
        JMenu fileMenu = new JMenu("File");
        menubar.add(fileMenu);
        JMenuItem quit = new JMenuItem("Quit");
        fileMenu.add(quit);

        quit.addActionListener(e -> System.exit(0));

        this.addWindowListener(new WindowAdapter() {
            public void windowClosing(WindowEvent e) {
                System.exit(0);
            }
        });

        for (GraphSample e : examples) {
            tpane.addTab(e.getName(), new GraphSamplePane(e));
        }
    }

    public class GraphSamplePane extends JComponent {
        GraphSample example;
        Dimension size;

        GraphSamplePane(GraphSample example) {
            this.example = example;
            size = new Dimension(example.getWidth(), example.getHeight());
            setMaximumSize(size);
        }

       public void paintComponent(Graphics g) {
            g.setColor(Color.white);
            g.fillRect(0, 0, 4*size.width, 4*size.height);
            g.setColor(Color.black);
            example.draw((Graphics2D) g, this);
        }

        public Dimension getPreferredSize() {
            return size;
        }

        public Dimension getMinimumSize() {
            return size;
        }
    }
}

interface GraphSample {
    String getName();

    int getWidth();

    int getHeight();

    void draw(Graphics2D g, Component c);
}
