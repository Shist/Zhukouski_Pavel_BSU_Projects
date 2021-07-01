<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8">
        <title>All readers</title>
    </head>
    <body>
        <div class="page">
            <h3>All readers of library</h3>

            <table border="1" cellpadding="5" cellspacing="1" style="border-collapse: collapse">
                   <tr>
                      <th>ID</th>
                      <th>Name</th>
                       <th>Birth date</th>
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