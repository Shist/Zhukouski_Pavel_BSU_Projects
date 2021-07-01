<%@ page language="java" contentType="text/html;charset=UTF-8"
         pageEncoding="UTF-8"%>

<%@ taglib prefix="fmt" uri="http://java.sun.com/jsp/jstl/fmt" %>
<fmt:requestEncoding value="UTF-8"/>
<fmt:setLocale value="${userLocale}"/>
<fmt:setBundle basename="locale"/>

<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8">
        <title><fmt:message key="app.title"/></title>
    </head>
    <body>
        <div class="page">
            <form class="form" method="POST">
                <fmt:message key="label.your_id"/>: <input type = "number" size="40" name = "reader_id" placeholder=<fmt:message key="label.your_id"/>>
                <fmt:message key="label.book_id"/>: <input type = "number" size="40" name = "book_id" placeholder=<fmt:message key="label.book_id"/>>
                <input type = "submit" value = <fmt:message key="input.submit"/> />
            </form>
        </div>
    </body>
</html>