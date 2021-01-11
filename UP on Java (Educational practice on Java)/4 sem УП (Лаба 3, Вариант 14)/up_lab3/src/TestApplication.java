public class TestApplication
{
    public static void main(String[] args) {
        final String classname = "Sample";
        GraphSample[] examples = new GraphSample[1];
        try {
            examples[0] = new Sample();
        } catch (ClassCastException e) {
            System.err.println("Class " + classname +
                    " is not a GraphSample");
            System.exit(1);
        } catch (Exception e) {
            System.err.println("Couldn't instantiate example: " + classname);
            System.exit(1);
        }
        GraphSampleFrame f = new GraphSampleFrame(examples);
        f.pack();
        f.setVisible(true);
    }
}