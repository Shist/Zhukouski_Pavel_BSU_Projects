<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8">
        <title>Books by author</title>
    </head>
    <body>
        <div class="page">
            <h3>Enter author name.</h3>

            <form class="form" method="POST">
                Author name: <input type = "text" size="40" name = "author_name" placeholder="Author\'s name">
                <button type="submit" onclick="window.open('${pageContext.request.contextPath}?command=getBookByAuthorResult')">Submit</button>
            </form>
        </div>
    </body>
</html>