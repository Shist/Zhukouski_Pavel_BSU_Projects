<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>

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
            <h3><fmt:message key="header.readers"/></h3>

            <table border="1" cellpadding="5" cellspacing="1" style="border-collapse: collapse">
                   <tr>
                    <th><fmt:message key="table.th.id"/></th>
                    <th><fmt:message key="table.th.name"/></th>
                    <th><fmt:message key="table.th.birth_date"/></th>
                   </tr>
                   <c:forEach items="${readersList}" var="reader" >
                      <tr>
                         <td>${reader.getId()}</td>
                         <td>${reader.getName()}</td>
                         <td>${reader.getBirth_date()}</td>
                      </tr>
                   </c:forEach>
                </table>
        </div>
    </body>
</html>