public class TestApplication
{
    public static void main(String[] args) {
        final String classname = "Sample";
        GraphSample[] examples = new GraphSample[1];
        try {
            Class exampleClass = Class.forName(classname);
            examples[0] = (GraphSample) exampleClass.newInstance();
        } catch (ClassNotFoundException e) {
            System.err.println("Couldn't find example: " + classname);
            System.exit(1);
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
        //f.print(examples[0]);
    }
}