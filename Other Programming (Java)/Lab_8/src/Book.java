import java.io.*;
import java.util.*;

public class Book implements Serializable {
    // class release version:
    private static final long serialVersionUID = 1L;
    // areas with prompts:
    String strISBN; 			
    static final String P_strISBN = "ISBN";
    String author;				
    static final String P_author = "Author";
    String name;				
    static final String P_name = "Name";
    int year;				
    static final String P_year = "Year";
    String publisher;			
    static final String P_publisher = "Publisher";
    String annotation;			
    static final String P_annotation = "Annotation";
    double price;				
    static final String P_price = "Price"; 
	
    // validation methods:
    static Boolean validISBN( String str ) {
        int i = 0, ndig = 0;
        for ( ; i < str.length(); i++ ) {
            char ch = str.charAt(i);
            if ( Character.isDigit(ch) ) {
                ndig++;
                continue;
            }
            if ( ch != '-' ) {
                return false;
            }				
        }
        return (ndig == 13 || ndig == 10 );
    }
	
    private static GregorianCalendar curCalendar = new GregorianCalendar();
    static Boolean validYear( int year ) {
        return year > 0 && year <= curCalendar.get( Calendar.YEAR );
    }
	
    public static Boolean nextRead( Scanner fin, PrintStream out ) {
        return nextRead( P_strISBN, fin, out );
    }
	
    static Boolean nextRead( final String prompt, Scanner fin, PrintStream out ) {
        out.print( prompt );
        out.print( ": " );
        return fin.hasNextLine();
    }

    public static final String authorDel = ",";

    public static Book read( Scanner fin, PrintStream out ) 
            throws IOException {
        String str;
        Book book = new Book();
        book.strISBN = fin.nextLine();
        if ( Book.validISBN( book.strISBN )== false ) {
            throw new IOException("");
        }
        if ( ! nextRead( P_author, fin, out ))           return null;
        book.author = fin.nextLine();
        if ( ! nextRead( P_name, fin, out ))             return null;
        book.name = fin.nextLine();
        if ( ! nextRead( P_year, fin, out ))             return null;
        str = fin.nextLine();
        book.year = Integer.parseInt(str);
        if ( Book.validYear(book.year) ==  false ) {
            throw new IOException("Invalid Book.year value");
        }
        if ( ! nextRead( P_publisher, fin, out ))        return null;
        book.publisher = fin.nextLine();
        if ( ! nextRead( P_annotation, fin, out ))       return null;
        book.annotation = fin.nextLine();
        if ( ! nextRead( P_price, fin, out ))            return null;
        str = fin.nextLine();
        book.price = Double.parseDouble(str);
        return book;
    }
		
    public Book() {
    }
	
    public static final String areaDel = "\n";

    public String toString() {
        return //new String (
            strISBN + areaDel +
            author + areaDel +
            name + areaDel +
            year + areaDel +
            publisher + areaDel +
            annotation + areaDel +
            price			
	//)
	;
    }
}
