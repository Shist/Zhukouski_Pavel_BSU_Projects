package View;

import Connector.Exceptions.JDBCConnectionException;
import DAO.BooksDAO;
import DAO.Exceptions.DAOException;
import DAO.ReadersDAO;
import Library.Book;
import Library.Reader;
import Library.Manager.Librarian;
import java.sql.Date;
import java.util.ArrayList;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) throws JDBCConnectionException, DAOException {

        Librarian L = new Librarian("Pavel");

        System.out.println(L.getStartMessage());
        System.out.println(L.getChoiceMessage());

        Scanner in = new Scanner(System.in);

        // Переменная для ответов читателя
        String answer = in.nextLine();
        // Переменная для хранения флажка о надобности выйти из библиотеки
        boolean exit_is_needed = false;

        while (!exit_is_needed)
        {
            switch (answer) {
                case "1" -> {
                    BooksDAO B = new BooksDAO();
                    ArrayList<Book> books = B.getAllBooks();
                    if (books.isEmpty())
                    {
                        System.out.println("We're sorry, but there are no any books at library");
                    }
                    else
                    {
                        for (Book b : books)
                            System.out.println(b.toString());
                    }
                    System.out.println("\n" + L.getChoiceMessage());
                    answer = in.nextLine();
                }
                case "2" -> {
                    BooksDAO B = new BooksDAO();
                    System.out.println("Please, enter book's name you are looking for:");
                    String needed_book_name = in.nextLine();
                    ArrayList<Book> books = B.getBooksWithSpecialName(needed_book_name);
                    if (books.isEmpty())
                    {
                        System.out.println("We're sorry, but there are no any books with such names");
                    }
                    else
                    {
                        for (Book b : books)
                            System.out.println(b.toString());
                    }
                    System.out.println("\n" + L.getChoiceMessage());
                    answer = in.nextLine();
                }
                case "3" -> {
                    BooksDAO B = new BooksDAO();
                    System.out.println("Please, enter author's name which book you are looking for:");
                    String needed_author_name = in.nextLine();
                    ArrayList<Book> books = B.getBooksWithSpecialAuthor(needed_author_name);
                    if (books.isEmpty())
                    {
                        System.out.println("We're sorry, but there are no any books with such authors");
                    }
                    else
                    {
                        for (Book b : books)
                            System.out.println(b.toString());
                    }
                    System.out.println("\n" + L.getChoiceMessage());
                    answer = in.nextLine();
                }
                case "4" -> {
                    BooksDAO B = new BooksDAO();
                    System.out.println("Please, enter ID of the book which you are looking for:");
                    int needed_book_ID = Integer.parseInt(in.nextLine());
                    Book b = B.getBookWithSpecialID(needed_book_ID);
                    if (b == null)
                    {
                        System.out.println("We're sorry, but there is no book with such an ID");
                    }
                    else
                    {
                        System.out.println(b.toString());
                    }
                    System.out.println("\n" + L.getChoiceMessage());
                    answer = in.nextLine();
                }
                case "5" -> {
                    ReadersDAO R = new ReadersDAO();
                    ArrayList<Reader> readers = R.getAllReaders();
                    if (readers.isEmpty())
                    {
                        System.out.println("We're sorry, but there are no any readers yet");
                    }
                    else
                    {
                        for (Reader r : readers)
                            System.out.println(r.toString());
                    }
                    System.out.println("\n" + L.getChoiceMessage());
                    answer = in.nextLine();
                }
                case "6" -> {
                    ReadersDAO R = new ReadersDAO();
                    System.out.println("Please, enter reader's name you are looking for:");
                    String needed_reader_name = in.nextLine();
                    ArrayList<Reader> readers = R.getReadersWithSpecialName(needed_reader_name);
                    if (readers.isEmpty())
                    {
                        System.out.println("We're sorry, but there are no any readers with such names");
                    }
                    else
                    {
                        for (Reader r : readers)
                            System.out.println(r.toString());
                    }
                    System.out.println("\n" + L.getChoiceMessage());
                    answer = in.nextLine();
                }
                case "7" -> {
                    ReadersDAO R = new ReadersDAO();
                    System.out.println("""
                            Please, enter date by which the readers you need borrowed books.
                            For example, you will enter 2020-09-15, so there will be all readers that borrowed books before this date.
                            So, enter date (format: YYYY-MM-DD):""");
                    Date needed_date;
                    needed_date = Date.valueOf(in.nextLine());
                    ArrayList<Reader> readers = R.getReadersWithSpecialDate(needed_date);
                    if (readers.isEmpty())
                    {
                        System.out.println("We're sorry, but there are no any readers that borrowed books before this date");
                    }
                    else
                    {
                        for (Reader r : readers)
                            System.out.println(r.toString());
                    }
                    System.out.println("\n" + L.getChoiceMessage());
                    answer = in.nextLine();
                }
                case "8" -> {
                    ReadersDAO R = new ReadersDAO();
                    System.out.println("Please, enter book's id which readers you are looking for:");
                    int needed_book_id = Integer.parseInt(in.nextLine());
                    ArrayList<Reader> readers = R.getReadersWithSpecialBookID(needed_book_id);
                    if (readers.isEmpty())
                    {
                        System.out.println("We're sorry, but there are no any readers that borrowed books with this ID");
                    }
                    else
                    {
                        for (Reader r : readers)
                            System.out.println(r.toString());
                    }
                    System.out.println("\n" + L.getChoiceMessage());
                    answer = in.nextLine();
                }
                case "9" -> {
                    ReadersDAO R = new ReadersDAO();
                    System.out.println("Please, enter ID of the reader which you are looking for:");
                    int needed_reader_id = Integer.parseInt(in.nextLine());
                    Reader r = R.getReaderWithSpecialID(needed_reader_id);
                    if (r == null)
                    {
                        System.out.println("We're sorry, but there is no reader with such an ID");
                    }
                    else
                    {
                        System.out.println(r.toString());
                    }
                    System.out.println("\n" + L.getChoiceMessage());
                    answer = in.nextLine();
                }
                case "10" -> {
                    BooksDAO B = new BooksDAO();
                    ReadersDAO R = new ReadersDAO();
                    System.out.println("Please, enter ID of the book you want to borrow:");
                    int needed_book_id = Integer.parseInt(in.nextLine());
                    Book b = B.getBookWithSpecialID(needed_book_id);
                    if (b == null)
                    {
                        System.out.println("We're sorry, but there is no book with such an ID");
                    }
                    else
                    {
                        System.out.println("So, you would like to borrow this book:");
                        System.out.println(b.toString());
                        int amount_of_such_books = B.getAmountOfBooksWithSpecialID(needed_book_id);
                        System.out.println("Number of copies of this book available: " + amount_of_such_books);
                        if (amount_of_such_books > 0)
                        {
                            System.out.println("Please, enter your name:");
                            String reader_name = in.nextLine();
                            B.borrowBookWithSpecialID(needed_book_id);
                            R.addReaderWithInfo(reader_name, needed_book_id);
                            System.out.println("You have successfully picked up the book!\n" +
                                    "We recommend you to check yourself in the lists of readers.");
                        }
                        else
                        {
                            System.out.println("We are sorry, but free copies of this book are currently not available.");
                        }
                    }
                    System.out.println("\n" + L.getChoiceMessage());
                    answer = in.nextLine();
                }
                case "11" -> {
                    BooksDAO B = new BooksDAO();
                    ReadersDAO R = new ReadersDAO();
                    System.out.println("Please, enter ID of the book you want to return:");
                    int needed_book_id = Integer.parseInt(in.nextLine());
                    Book b = B.getBookWithSpecialID(needed_book_id);
                    if (b == null)
                    {
                        System.out.println("We're sorry, but there is no book with such an ID");
                    }
                    else
                    {
                        System.out.println("So, you would like to return this book:");
                        System.out.println(b.toString());
                        System.out.println("""
                            Please, enter your reader's ID.
                            Note: if you don't know your reader's ID, you can use 6th query to find out ID by name.
                            So, enter reader's ID:""");
                        int needed_reader_id = Integer.parseInt(in.nextLine());
                        if (R.checkBorrowedBookByReader(needed_reader_id, needed_book_id) == 1)
                        {
                            B.returnBookWithSpecialID(needed_book_id);
                            R.deleteReaderByID(needed_reader_id);
                            System.out.println("You have successfully returned the book!\n" +
                                    "So, you were deleted from the lists of readers.");
                        }
                        else
                        {
                            System.out.println("We're sorry, but there is no borrowed book with such ID for this reader");
                        }
                    }
                    System.out.println("\n" + L.getChoiceMessage());
                    answer = in.nextLine();
                }
                case "exit" -> {
                    exit_is_needed = true;
                    System.out.println(L.getExitMessage());
                }
                default -> {
                    System.out.println(L.getMistakeMessage() + "\n" + L.getChoiceMessage());
                    answer = in.nextLine();
                }
            }
        }
    }
}
