import java.awt.*;

public class TestApplication
{
    public static void main(String[] args)
    {
        final String classname = "Shapes";
        GraphSample[] examples = new GraphSample[1];

        // Try to instantiate the named GraphSample class
        try {
            Class exampleClass = Class.forName(classname);
            examples[0] = (GraphSample) exampleClass.newInstance();
            examples[0].SetW(Float.parseFloat(args[0]));
            examples[0].SetC_gr(Color.decode(args[1]));
            examples[0].SetMain_C(Color.decode(args[2]));
        }
        catch (ClassNotFoundException e) {  // unknown class
            System.err.println("Couldn't find example: "  + classname);
            System.exit(1);
        }
        catch (ClassCastException e) {      // wrong type of class
            System.err.println("Class " + classname +
                    " is not a GraphSample");
            System.exit(1);
        }
        catch (Exception e) {  // class doesn't have a public constructor
            // catch InstantiationException, IllegalAccessException
            System.err.println("Couldn't instantiate example: " +
                    classname);
            System.exit(1);
        }

        // Now create a window to display the examples in, and make it visible
        GraphSampleFrame f = new GraphSampleFrame(examples);
        f.pack();
        f.setVisible(true);
    }
}