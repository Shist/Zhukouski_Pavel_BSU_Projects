import java.io.Serializable;
import java.util.Scanner;

public class Book implements Serializable {
    String strISBN;
    String author;
    String name;
    String year;
    String publisher;
    String annotation;
    String price;
	
    public static Book read( Scanner fin ) {
        Book book = new Book();
        book.strISBN = fin.nextLine();
        if ( ! fin.hasNextLine()) return null;
        book.author = fin.nextLine();
        if ( ! fin.hasNextLine()) return null;
        book.name = fin.nextLine();
        if ( ! fin.hasNextLine()) return null;
        book.year = fin.nextLine();
        if ( ! fin.hasNextLine()) return null;
        book.publisher = fin.nextLine();
        if ( ! fin.hasNextLine()) return null;
        book.annotation = fin.nextLine();
        if ( ! fin.hasNextLine()) return null;
        book.price = fin.nextLine(); 
        return book;
    }
	
    public Book() {
    }

    public String toString() {
        return new String (
            strISBN + "|" +
            author + "|" +
            name + "|" +
            year + "|" +
            publisher + "|" +
            annotation + "|" +
            price			
        );
    }
}
