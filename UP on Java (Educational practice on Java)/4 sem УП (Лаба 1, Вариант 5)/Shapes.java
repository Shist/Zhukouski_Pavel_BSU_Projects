import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.awt.geom.*;

// В теме письма указать "2 курс, УП"

public class Shapes implements GraphSample
{
	AffineTransform transform;
	public double coordinateX;
	public double coordinateY;
	double angle;
	Thread t;
	public static float W;
	public void SetW(float aW) {W = aW;}
	public static Color C_Gr;
	public void SetC_gr(Color aC_Gr) {C_Gr = aC_Gr;}
	public static Color Main_C;
	public void SetMain_C(Color aC) {Main_C = aC;}

	static final int WIDTH = 800, HEIGHT = 600;    // Size of our example
	public String getName() {return "Variant 5";}     // From GraphSample
	public int getWidth() { return WIDTH; }        // From GraphSample
	public int getHeight() { return HEIGHT; }      // From GraphSample

	public void draw(Graphics2D g, Component c)
	{
		g.setFont(new Font("SansSerif", Font.PLAIN, 12));
		g.setStroke(new BasicStroke(W));
		g.setColor(C_Gr);

		int NPoints = 4;
		int Xp1 = 250;
		int Xp2 = 310;
		int Xp3 = 440;
		int Xp4 = 530;
		int Yp1 = 370;
		int Yp2 = 190;
		int Yp3 = 260;
		int Yp4 = 410;
		int XCenter = (Xp1 + Xp2 + Xp3 + Xp4) / 4;
		int YCenter = (Yp1 + Yp2 + Yp3 + Yp4) / 4;
		int[] XPoints = {Xp1, Xp2, Xp3, Xp4};
		int[] YPoints = {Yp1, Yp2, Yp3, Yp4};

		Polygon Q = new Polygon(XPoints, YPoints, NPoints);

		transform = AffineTransform.getRotateInstance(angle * Math.PI / 16, XCenter , YCenter);
		g.transform(transform);

		g.draw(Q);
		g.setColor(Main_C);
		g.fill(Q);
	}


	public void repaintComponent(Graphics g, Component c){
		angle += 0.05;
		c.repaint();
	}
}

class GraphSampleFrame extends  JFrame
{

	public GraphSampleFrame(final GraphSample[] examples) {
		super("GraphSampleFrame");

		Container cpane = getContentPane();   // Set up the frame
		cpane.setLayout(new BorderLayout());
		final JTabbedPane tpane = new JTabbedPane(); // And the tabbed pane
		cpane.add(tpane, BorderLayout.CENTER);

		// Add a menubar
		JMenuBar menubar = new JMenuBar();         // Create the menubar
		this.setJMenuBar(menubar);                 // Add it to the frame
		JMenu filemenu = new JMenu("File");        // Create a File menu
		menubar.add(filemenu);                     // Add to the menubar
		JMenuItem quit = new JMenuItem("Quit");    // Create a Quit item
		filemenu.add(quit);                        // Add it to the menu

		// Tell the Quit menu item what to do when selected
		quit.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) { System.exit(0); }
		});

		// In addition to the Quit menu item, also handle window close events
		this.addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent e) { System.exit(0); }
		});

		// Insert each of the example objects into the tabbed pane
		for(int i = 0; i < examples.length; i++) {
			GraphSample e = examples[i];
			tpane.addTab(e.getName(), new GraphSamplePane(e));
		}
	}

	public class GraphSamplePane extends JComponent
	{
		GraphSample example;  // The example to display
		Dimension size;           // How much space it requires

		public GraphSamplePane(GraphSample example) {
			this.example = example;
			size = new Dimension(example.getWidth(), example.getHeight());
			setMaximumSize(size);
		}

		public void paintComponent(Graphics g) {
			g.setColor(Color.white);                    // set the background
			g.fillRect(0, 0, size.width, size.height);  // to white
			g.setColor(Color.black);             // set a default drawing color
			example.draw((Graphics2D) g, this);  // ask example to draw itself
			example.repaintComponent(g, this);
		}

		public Dimension getPreferredSize() { return size; }
		public Dimension getMinimumSize() { return size; }
	}
}

interface GraphSample {
	public String getName();                      // Return the example name
	public int getWidth();                        // Return its width
	public int getHeight();                       // Return its height
	public void SetW(float aW);
	public void SetC_gr(Color aC_Gr);
	public void SetMain_C(Color aC);
	public void draw(Graphics2D g, Component c);  // Draw the example
	public void repaintComponent(Graphics g, Component c);
}