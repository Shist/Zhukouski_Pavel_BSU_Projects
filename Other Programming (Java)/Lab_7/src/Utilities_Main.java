import java.io.*;
import java.util.*;

public class Utilities_Main {

    public static void main(String[] args) {
        try {
            if ( args.length >= 1 ) {
                if ( args[0].compareTo( "-a" )== 0 ) {
                    // Append file with new object from System.in
                    append_file();
                }
                else if ( args[0].compareTo( "-p" )== 0 ) {
                    // Prints data file
                    print_file();
                }
                else if ( args[0].compareTo( "-d" )== 0 ) {
                    // Delete data file
                    delete_file();
                }
                else {
                    System.err.println( "Option is not realised: " + args[0] );
                    System.exit(1);
                }
            }
            else {
                System.err.println( "Utilities: Nothing to do!" );
            }
        }
        catch ( Exception e ) {
            System.err.println( "Run/time error: " + e );
            System.exit(1);
        }
        System.out.println( "Utilities finished..." );
	System.exit(0);
    }

    static final String filename = "Utilities.dat";
	
    private static Scanner fin = new Scanner( System.in );

    static Utilities read_utilities() {
        if ( fin.hasNextLine()) {
            return Utilities.read(fin);
        }
        return null;
    }
	
    static void delete_file() {
        File f = new File( filename );
        f.delete();
    }
	
    static void append_file() throws FileNotFoundException, IOException {
        Utilities utilities;
        System.out.println( "Enter utilities data: " );
        try ( RandomAccessFile raf = new RandomAccessFile( filename, "rw" )) {
            while (( utilities = read_utilities())!= null ) {
                Buffer.writeObject( raf, utilities );
	    }
        }
    }

    static void print_file() 
            throws FileNotFoundException, IOException, ClassNotFoundException {
        try ( RandomAccessFile raf = new RandomAccessFile( filename, "rw" )) {
            long pos;
            while (( pos = raf.getFilePointer()) < raf.length() ) {
                Utilities utilities = (Utilities) Buffer.readObject( raf, pos );
                System.out.println( pos + ": " + utilities );
            }
        }		
    }
}
