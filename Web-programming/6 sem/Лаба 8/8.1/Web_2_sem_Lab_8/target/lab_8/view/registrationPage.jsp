<%@ page contentType="text/html;charset=UTF-8" language="java" %>

<%@ taglib prefix="fmt" uri="http://java.sun.com/jsp/jstl/fmt" %>
<fmt:requestEncoding value="UTF-8"/>
<fmt:setLocale value="${userLocale}"/>
<fmt:setBundle basename="locale"/>

<html>
<head>
    <meta charset="utf-8">
    <title><fmt:message key="app.title"/></title>
</head>
<body>
<div class="page">
    <h3><fmt:message key="header.create_account"/></h3>
    <form class="form" method="POST">
        <fmt:message key="label.login"/>: <input type = "text" size = "40" name = "login" placeholder = <fmt:message key="label.login"/>/>
        <fmt:message key="label.password"/>: <input type = "text" size = "40" name = "password" placeholder = <fmt:message key="label.password"/>/>
        <fmt:message key="label.confirm_password"/>: <input type = "text" size = "40" name = "confirm_password" placeholder = <fmt:message key="label.confirm_password"/>/>
        <fmt:message key="label.name"/>: <input type = "text" size = "40" name = "name" placeholder = <fmt:message key="label.name"/>/>
        <input type = "submit" value = <fmt:message key="input.login"/> />
    </form>
</div>
</body>
</html>