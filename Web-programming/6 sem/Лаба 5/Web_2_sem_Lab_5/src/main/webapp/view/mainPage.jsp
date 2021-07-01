<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-16">
        <title>Library</title>

    </head>
    <body>
        <header>
                <p>Меню библиотеки
                    <br>1) Вывести информацию о всех книгах, имеющихся в библиотеке.
                    <br>2) Вывести информацию о всех читателях, польщующихся библиотекой.
                    <br>3) Вывести информацию о всех книгах определённого автора.
                    <br>4) Взять книгу на чтение, указав ID книги и ID читателя.
                    <br>5) Вернуть книгу в библиотеку, указав ID книги и ID читателя.
                    <br>6) Вывести информацию о читателях, которые не вернули книги в срок.
                </p>
        </header>
        <div class="main-page">
            <div class="menu">
                <h1>MENU</h1>
                <button type="button" onclick="window.open('${pageContext.request.contextPath}?command=showAllBooks')" >Все книги</button>
                <button type="button" onclick="window.open('${pageContext.request.contextPath}?command=showAllReaders')">Все читатели</button>
                <button type="button" onclick="window.open('${pageContext.request.contextPath}?command=getBookByAuthorForm')">Книги по автору</button>
                <button type="button" onclick="window.open('${pageContext.request.contextPath}?command=getBook')">Взять книгу</button>
                <button type="button" onclick="window.open('${pageContext.request.contextPath}?command=returnBook')">Вернуть книгу</button>
                <button type="button" onclick="window.open('${pageContext.request.contextPath}?command=getDebtors')">Список должников</button>
            </div>
        </div>
    </body>
</html>