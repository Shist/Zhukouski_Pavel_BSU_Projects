<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8">
        <title>Library</title>

        </head>
        <body>
        <header>
            <p> Guest menu
                <br> 1) Display information about all the books available in the library.
                <br> 2) Display information about all books of a certain author.
            </p>
        </header>
            <div class="main-page">
                <div class="menu">
                    <h1>MENU</h1>
                    <button type="button"><a href="${pageContext.request.contextPath}?command=showAllBooks">Show all books</a></button>
                    <button type="button"><a href="${pageContext.request.contextPath}?command=getBookByAuthorForm">Get book by author</a></button>
                </div>
            </div>
    </body>
</html>