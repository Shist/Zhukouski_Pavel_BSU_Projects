package controller;

public class Librarian {

    public String name; // Имя библиотекаря (менеджера библиотеки)

    public Librarian(String l_name)
    {
        name = l_name;
    }

    public String getStartMessage()
    {
        return "Hello, my name is " + name + ". I will help you figure out this library.";
    }

    public String getChoiceMessage()
    {
        return """
                Enter the number of query you need to make:
                "1" - Select all books at library and their information
                "2" - Select all books with special name
                "3" - Select all books with special author
                "4" - Select the book by its ID
                "5" - Select information about all current readers
                "6" - Select information about all readers with special name
                "7" - Select information about all readers from special date
                "8" - Select all readers of book with special ID
                "9" - Select the reader by his ID
                "10" - Borrow some book by its ID
                "11" - Return some book by its ID and reader's ID
                Or enter "exit" to exit the library""";
    }

    public String getMistakeMessage()
    {
        return "Your answer is incorrect. Please, try again.";
    }

    public String getExitMessage()
    {
        return "Thanks for visiting our library, goodbye!";
    }
}
