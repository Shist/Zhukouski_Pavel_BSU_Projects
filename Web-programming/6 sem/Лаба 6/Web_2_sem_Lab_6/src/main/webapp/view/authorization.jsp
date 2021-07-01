<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
    <head>
        <meta charset="utf-8">
        <title>Library</title>
    </head>
    <body>
        <div class="page">
            <h3>LOG IN</h3>
            <form class="form" method="POST">
                Login: <input type = "text" size = "40" name = "login" placeholder = "Login"/>
                Password: <input type = "text" size = "40" name = "password" placeholder = "Password"/>
                <input type = "submit" value = "Login" />
                <input type = "hidden" name = "command" value = "authorization">
            </form>
        </div>
    </body>
</html>