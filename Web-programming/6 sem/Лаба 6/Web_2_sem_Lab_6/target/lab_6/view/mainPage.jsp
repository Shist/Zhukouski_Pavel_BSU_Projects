<! DOCTYPE html>
<html>
<head>
    <meta charset = "utf-16">
    <title> Library </title>

</head>
<body>
<header>
    <p> Library menu
        <br> 1) Display information about all the books available in the library.
        <br> 2) Display information about all readers who are flattered by the library.
        <br> 3) Display information about all books of a certain author.
        <br> 4) Take the book for reading, indicating the ID of the book and the ID of the reader.
        <br> 5) Return the book to the library, specifying the ID of the book and the ID of the reader.
        <br> 6) Display information about readers who did not return books on time.
    </p>
</header>
<div class = "main-page">
    <div class = "menu">
        <h1> MENU </h1>
        <button type = "button" onclick = "window.open ('${pageContext.request.contextPath}? command = showAllBooks')"> All Books </button>
        <button type = "button" onclick = "window.open ('${pageContext.request.contextPath}? command = showAllReaders')"> All Readers </button>
        <button type = "button" onclick = "window.open ('${pageContext.request.contextPath}? command = getBookByAuthorForm')"> Books by author </button>
        <button type = "button" onclick = "window.open ('${pageContext.request.contextPath}? command = getBook')"> Get Book </button>
        <button type = "button" onclick = "window.open ('${pageContext.request.contextPath}? command = returnBook')"> Return Book </button>
        <button type = "button" onclick = "window.open ('${pageContext.request.contextPath}? command = getDebtors')"> List of debtors </button>
    </div>
</div>
</body>
</html>