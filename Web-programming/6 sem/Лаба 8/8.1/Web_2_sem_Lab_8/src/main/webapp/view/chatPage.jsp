<%@ page import="model.entity.User" %>
<%@ page language="java" contentType="text/html;charset=UTF-8"
         pageEncoding="UTF-8"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>
<%@ taglib prefix="fmt" uri="http://java.sun.com/jsp/jstl/fmt" %>
<fmt:requestEncoding value="UTF-8"/>
<fmt:setLocale value="${userLocale}"/>
<fmt:setBundle basename="locale"/>

<!DOCTYPE html>
    <html>
        <head>
            <meta charset="UTF-8">
            <title><fmt:message key="app.title"/></title>
            <script src="${pageContext.request.contextPath}/script/script.js"></script>
        </head>
        <body>
            <h1><fmt:message key="header.chat_with_librarian"/></h1>

            <%User user = (User)session.getAttribute("user"); %>
            <%String userType = (user == null ? "null" : user.getUser_type()); %>

            <input type="hidden" id="senderId" value="${senderId}">
            <div>
                <%if (userType.equals("L")) {%>
                    <p><fmt:message key="header.librarian_info"/></p>
                <%}%>
                <textArea id="chatWindow" rows="10" style="width: 44em;margin: 15px" readonly></textArea>
            </div>
            <div>
                <input type="text" id="chatInput" style="width: 40em;margin: 15px"/>
                <input id="sendBtn" type="button" class="btn btn-primary" value="<fmt:message key="input.send"/>"onclick="sendMessage()"/>
            </div>
        </body>
    </html>
