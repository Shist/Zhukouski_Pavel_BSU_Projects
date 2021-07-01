<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8">
        <title>Library</title>

        </head>
        <body>
        <header>
            <p> Reader menu
                <br> 1) Display information about all the books available in the library.
                <br> 2) Display information about all books of a certain author.
                <br> 3) Take the book for reading, indicating the ID of the book and the ID of the reader.
                <br> 4) Return the book to the library, specifying the ID of the book and the ID of the reader.
            </p>
        </header>
            <div class="main-page">
                <div class="menu">
                    <h1>MENU</h1>
                    <button type="button"><a href="${pageContext.request.contextPath}?command=showAllBooks">Show all books</a></button>
                    <button type="button"><a href="${pageContext.request.contextPath}?command=getBookByAuthorForm">Get book by author</a></button>
                    <button type="button"><a href="${pageContext.request.contextPath}?command=getBook">Get book</a></button>
                    <button type="button"><a href="${pageContext.request.contextPath}?command=returnBook">Return book</a></button>
                </div>
            </div>
    </body>
</html>