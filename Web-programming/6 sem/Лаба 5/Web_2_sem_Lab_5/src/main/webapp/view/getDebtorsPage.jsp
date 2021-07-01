<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8">
        <title>Debtors</title>
    </head>
    <body>
        <div class="page">
            <h3>Debtors of library</h3>

            <table border="1" cellpadding="5" cellspacing="1" style="border-collapse: collapse">
                   <tr>
                       <th>Information about readers that didn't return their books</th>
                   </tr>
                   <c:forEach items="${debtorsList}" var="debtor" >
                      <tr>
                         <td>${debtor.getReader()}</td>
                         <td>${book.getBook()}</td>
                      </tr>
                   </c:forEach>
                </table>
        </div>
    </body>
</html>