package Library;

/**
 * class that represent book entity
 * @author Zhukouski Pavel
 */
public class Book {
    private int ID;         // ID книги
    private String bName;   // Название книги
    private String bAuthor; // Автор книги
    private int bAmount;    // Количество имеющихся экземпляров книги

    public int getBookID(){
        return ID;
    }
    public void setBookID(int id){
        this.ID=id;
    }
    public String getBookName(){
        return bName;
    }
    public void setBookName(String book_name){
        this.bName=book_name;
    }
    public String getBookAuthor(){
        return bAuthor;
    }
    public void setBookAuthor(String book_author){
        this.bAuthor=book_author;
    }
    public int getBooksAmount(){
        return bAmount;
    }
    public void setBooksAmount(int books_amount){
        this.bAmount=books_amount;
    }

    public Book(int id, String book_name, String book_author, int books_amount) {
        setBookID(id);
        setBookName(book_name);
        setBookAuthor(book_author);
        setBooksAmount(books_amount);
    }
    @Override
    public String toString() {
        return "\n### BOOK INFORMATION ###\n" +
                "ID = " + getBookID() + "\n" +
                "Book's name: \"" + getBookName() + "\"\n" +
                "Book's author: \"" + getBookAuthor() + "\"\n" +
                "Books's amount left: " + getBooksAmount() + "\n";
    }
}
