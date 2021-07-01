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
                      <th><fmt:message key="table.th.reader_id"/></th>
                      <th><fmt:message key="table.th.book_id"/></th>
                   </tr>
                   <c:forEach items="${debtorsList}" var="debtor" >
                      <tr>
                         <td>${debtor.getReader().getId()}</td>
                         <td>${debtor.getBook().getId()}</td>
                      </tr>
                   </c:forEach>
                </table>
        </div>
    </body>
</html>