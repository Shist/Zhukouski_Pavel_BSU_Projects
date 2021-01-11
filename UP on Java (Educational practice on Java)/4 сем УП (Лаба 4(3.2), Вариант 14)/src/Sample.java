import javax.swing.*;
import java.awt.*;
import java.io.*;
import java.awt.color.ColorSpace;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.awt.geom.AffineTransform;
import java.awt.geom.Point2D;
import java.awt.geom.Rectangle2D;
import java.awt.image.*;
import java.awt.print.*;
import java.util.Scanner;

public class Sample implements GraphSample {

    private static final int WIDTH = 1050, HEIGHT = 700;

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
        g.setColor(Color.BLACK);
        g.setFont(new Font("SansSerif", Font.ITALIC, 28));  // 28pt bold text
        g.drawString("Source code:", 20, 210);
        g.setFont(new Font("SansSerif", Font.ITALIC, 48));  // 48pt bold text
        g.drawString("Ordinary Cycloid", 690, 210);
        g.setFont(new Font("Times New Roman", Font.BOLD, 10));  // 48pt bold text
        try {
            Scanner scan_in = new Scanner(new FileReader("in.txt"));
            int curr_x = 10;
            int curr_y = 250;
            int k = 0;
            while (k < 124)
            {
                String str = scan_in.nextLine();
                g.drawString(str, curr_x, curr_y);
                curr_y += 10;
                k++;
                if (k % 45 == 0)
                {
                    curr_x += 350;
                    curr_y = 250;
                }
            }
            g.translate(10, 10);                              // Set some margins
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
    }
}

/* A demonstration of various image processing filters */
class ImageOps implements GraphSample {
    static final int WIDTH = 900, HEIGHT = 600;         // Size of our example
    public String getName() {return "Image Processing";}// From GraphSample
    public int getWidth() { return WIDTH; }             // From GraphSample
    public int getHeight() { return HEIGHT; }           // From GraphSample

    Image image;

    /* This constructor loads the image we will manipulate */
    public ImageOps() {
        java.net.URL imageurl = this.getClass().getResource("cover.gif");
        image = new javax.swing.ImageIcon(imageurl).getImage();
    }

    // These arrays of bytes are used by the LookupImageOp image filters below
    static byte[] brightenTable = new byte[256];
    static byte[] thresholdTable = new byte[256];
    static {  // Initialize the arrays
        for(int i = 0; i < 256; i++) {
            brightenTable[i] = (byte)(Math.sqrt(i/255.0)*255);
            thresholdTable[i] = (byte)((i < 225)?0:i);
        }
    }

    // This AffineTransform is used by one of the image filters below
    static AffineTransform mirrorTransform;
    static {  // Create and initialize the AffineTransform
        mirrorTransform = AffineTransform.getTranslateInstance(127, 0);
        mirrorTransform.scale(-1.0, 1.0);  // flip horizontally
    }

    // These are the labels we'll display for each of the filtered images
    static String filterName = new String ("Ordinary Cycloid");

    // The following BufferedImageOp image filter objects perform
    // different types of image processing operations.
    static BufferedImageOp filter = null;
   /* static BufferedImageOp[] filters = new BufferedImageOp[] {
            // 1) No filter here.  We'll display the original image
            null,
            // 2) Convert to Grayscale color space
            new ColorConvertOp(ColorSpace.getInstance(ColorSpace.CS_GRAY), null),
            // 3) Image negative.  Multiply each color value by -1.0 and add 255
            new RescaleOp(-1.0f, 255f, null),
            // 4) Brighten using a linear formula that increases all color values
            new RescaleOp(1.25f, 0, null),
            // 5) Brighten using the lookup table defined above
            new LookupOp(new ByteLookupTable(0, brightenTable), null),
            // 6) Threshold using the lookup table defined above
            new LookupOp(new ByteLookupTable(0, thresholdTable), null),
            // 7) Blur by "convolving" the image with a matrix
            new ConvolveOp(new Kernel(3, 3, new float[] {
                    .1111f,.1111f,.1111f,
                    .1111f,.1111f,.1111f,
                    .1111f,.1111f,.1111f,})),
            // 8) Sharpen by using a different matrix
            new ConvolveOp(new Kernel(3, 3, new float[] {
                    0.0f, -0.75f, 0.0f,
                    -0.75f, 4.0f, -0.75f,
                    0.0f, -0.75f, 0.0f})),
            // 9) Edge detect using yet another matrix
            new ConvolveOp(new Kernel(3, 3, new float[] {
                    0.0f,  -0.75f, 0.0f,
                    -0.75f, 3.0f, -0.75f,
                    0.0f,  -0.75f, 0.0f})),
            // 10) Compute a mirror image using the transform defined above
            new AffineTransformOp(mirrorTransform,AffineTransformOp.TYPE_BILINEAR),
            // 11) Rotate the image 180 degrees about its center point
            new AffineTransformOp(AffineTransform.getRotateInstance(Math.PI,64,95),
                    AffineTransformOp.TYPE_NEAREST_NEIGHBOR),
            // 12) Rotate the image 15 degrees about the bottom left
            new AffineTransformOp(AffineTransform.getRotateInstance(Math.PI/12,
                    0, 190),
                    AffineTransformOp.TYPE_NEAREST_NEIGHBOR),
    };*/

    /* Draw the example */
    public void draw(Graphics2D g, Component c) {
        // Create a BufferedImage big enough to hold the Image loaded
        // in the constructor.  Then copy that image into the new
        // BufferedImage object so that we can process it.
        BufferedImage bimage = new BufferedImage(image.getWidth(c),
                image.getHeight(c),
                BufferedImage.TYPE_INT_RGB);
        Graphics2D ig = bimage.createGraphics();
        ig.drawImage(image, 0, 0, c);  // copy the image

        // Set some default graphics attributes
        g.setFont(new Font("SansSerif", Font.BOLD, 12));  // 12pt bold text
        g.setColor(Color.BLACK);                          // Draw in green
        g.translate(10, 10);                              // Set some margins

        // Loop through the filters
        // If the filter is null, draw the original image, otherwise,
        // draw the image as processed by the filter
        //if (filter == null) g.drawImage(bimage, 0, 0, c);
        //else g.drawImage(filter.filter(bimage, null), 0, 0, c);
        //g.drawString(filterName, 400, 200);      // Label the image
        //g.translate(137, 0);                       // Move over
        //if (i % 4 == 3) g.translate(-137*4, 215);  // Move down after 4
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
        JMenuItem print = new JMenuItem("Print");  // Create a Print item
        fileMenu.add(print);                       // Add it to the menu
        JMenuItem quit = new JMenuItem("Quit");
        fileMenu.add(quit);

        // Tell the Print menu item what to do when selected
        print.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                // Get the currently displayed example, and call
                // the print method (defined below)
                print(examples[tpane.getSelectedIndex()]);
            }
        });

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

    /*
     * This inner class is a custom Swing component that displays
     * a GraphSample object.
     */
    public class GraphSamplePane extends JComponent {
        GraphSample example;  // The example to display
        Dimension size;           // How much space it requires

        public GraphSamplePane(GraphSample example) {
            this.example = example;
            size = new Dimension(example.getWidth(), example.getHeight());
        }

        /** Draw the component and the example it contains */
        public void paintComponent(Graphics g) {
            g.setColor(Color.white);                    // set the background
            g.fillRect(0, 0, size.width, size.height);  // to white
            g.setColor(Color.black);             // set a default drawing color
            example.draw((Graphics2D) g, this);  // ask example to draw itself
        }

        // These methods specify how big the component must be
        public Dimension getPreferredSize() { return size; }
        public Dimension getMinimumSize() { return size; }
    }

    /** This method is invoked by the Print menu item */
    public void print(final GraphSample example) {
        // Start off by getting a printer job to do the printing
        PrinterJob job = PrinterJob.getPrinterJob();
        PageFormat pf = new PageFormat();
        pf.setOrientation(0); // Меняем формат на АЛЬБОМНЫЙ
        job.defaultPage(pf);
        // Wrap the example in a Printable object (defined below)
        // and tell the PrinterJob that we want to print it
        job.setPrintable(new PrintableExample(example));

        // Display the print dialog to the user
        if (job.printDialog()) {
            // If they didn't cancel it, then tell the job to start printing
            try {
                job.print();
            }
            catch(PrinterException e) {
                System.out.println("Couldn't print: " + e.getMessage());
            }
        }
    }

    /*
     * This inner class implements the Printable interface in order to print
     * a GraphSample object.
     **/
    class PrintableExample implements Printable  {
        GraphSample example;  // The example to print

        // The constructor.  Just remember the example
        public PrintableExample(GraphSample example) {
            this.example = example;
        }

        /*
          This method is called by the PrinterJob to print the example
         */
        public int print(Graphics g, PageFormat pf, int pageIndex) {
            // Tell the PrinterJob that there is only one page
            if (pageIndex != 0) return NO_SUCH_PAGE;

            // The PrinterJob supplies us a Graphics object to draw with.
            // Anything drawn with this object will be sent to the printer.
            // The Graphics object can safely be cast to a Graphics2D object.
            Graphics2D g2 = (Graphics2D)g;

            // Translate to skip the left and top margins.
            g2.translate(pf.getImageableX(), pf.getImageableY());

            // Figure out how big the printable area is, and how big
            // the example is.
            double pageWidth = pf.getImageableWidth();
            double pageHeight = pf.getImageableHeight();
            double exampleWidth = example.getWidth();
            double exampleHeight = example.getHeight();

            // Scale the example if needed
            double scalex = 1.0, scaley = 1.0;
            if (exampleWidth > pageWidth) scalex = pageWidth/exampleWidth;
            if (exampleHeight > pageHeight) scaley = pageHeight/exampleHeight;
            double scalefactor = Math.min(scalex, scaley);
            if (scalefactor != 1) g2.scale(scalefactor, scalefactor);

            // Finally, call the draw() method of the example, passing in
            // the Graphics2D object for the printer
            example.draw(g2, GraphSampleFrame.this);

            // Tell the PrinterJob that we successfully printed the page
            return PAGE_EXISTS;
        }
    }
    /*quit.addActionListener(e -> System.exit(0));

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
    }*/
}

interface GraphSample {
    String getName();

    int getWidth();

    int getHeight();

    void draw(Graphics2D g, Component c);
}
