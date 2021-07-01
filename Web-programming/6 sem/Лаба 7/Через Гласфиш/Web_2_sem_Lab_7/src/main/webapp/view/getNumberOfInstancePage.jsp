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
        <%@taglib uri="/WEB-INF/tag.tld"
        prefix="mytag" %>
    </head>
    <body>
        <div class="page">
            <mytag:MyTag/>
        </div>
    </body>
</html>