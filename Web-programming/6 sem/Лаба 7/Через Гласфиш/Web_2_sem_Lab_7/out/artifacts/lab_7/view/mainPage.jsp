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
            <meta charset="utf-8">
            <title><fmt:message key="app.title"/></title>
        </head>
        <body>
            <ul class="nav justify-content-end">
                <li class="nav-item">
                    <div class="page-form">
                        <form>
                            <div class="form-group">
                                <select class="form-control" name='lang' onchange='this.form.submit()'>
                                    <c:choose>
                                    <c:when test="${userLocale.language == 'ru'}">
                                    <option value='ru' selected>Русский
                                    <option value='en'>English
                                        </c:when>
                                        <c:otherwise>
                                    <option value='ru'>Русский
                                    <option value='en' selected>English
                                        </c:otherwise>
                                        </c:choose>
                                </select>
                            </div>
                        </form>
                    </div>
                </li>
            </ul>
            <%User user = (User)session.getAttribute("user"); %>
            <%String userType = (user == null ? "null" : user.getUser_type()); %>
            <%if (userType.equals("null")) {%>
                <h2><fmt:message key="header.main_page"/></h2>
            <%} else if (userType.equals("R")) { %>
                <h2><fmt:message key="header.reader_page"/></h2>
            <%} else if (userType.equals("L")) { %>
                <h2><fmt:message key="header.librarian_page"/></h2>
            <%} else if (userType.equals("G")) { %>
                <h2><fmt:message key="header.guest_page"/></h2>
            <%}%>

            <div class="main-page">
                <div class="menu">
                <h1><fmt:message key="header.menu"/></h1>
                <%if (userType.equals("R")) {%>
                    <button type="button"><a href="${pageContext.request.contextPath}?command=showAllBooks"><fmt:message key="button.show_all_books"/></a></button>
                    <button type="button"><a href="${pageContext.request.contextPath}?command=getBookByAuthor"><fmt:message key="button.get_book_by_author"/></a></button>
                    <button type="button"><a href="${pageContext.request.contextPath}?command=getNumberOfInstance"><fmt:message key="button.get_number_of_instance"/></a></button>
                    <button type="button"><a href="${pageContext.request.contextPath}?command=getBook"><fmt:message key="button.get_book"/></a></button>
                    <button type="button"><a href="${pageContext.request.contextPath}?command=returnBook"><fmt:message key="button.return_book"/></a></button>
                <%}%>
                <%if (userType.equals("L")) {%>
                    <button type="button"><a href="${pageContext.request.contextPath}?command=showAllReaders"><fmt:message key="button.show_all_readers"/></a></button>
                    <button type="button"><a href="${pageContext.request.contextPath}?command=showAllBooks"><fmt:message key="button.show_all_books"/></a></button>
                    <button type="button"><a href="${pageContext.request.contextPath}?command=getBookByAuthor"><fmt:message key="button.get_book_by_author"/></a></button>
                    <button type="button"><a href="${pageContext.request.contextPath}?command=getNumberOfInstance"><fmt:message key="button.get_number_of_instance"/></a></button>
                    <button type="button"><a href="${pageContext.request.contextPath}?command=getBook"><fmt:message key="button.get_book"/></a></button>
                    <button type="button"><a href="${pageContext.request.contextPath}?command=returnBook"><fmt:message key="button.return_book"/></a></button>
                    <button type="button"><a href="${pageContext.request.contextPath}?command=getDebtors"><fmt:message key="button.get_debtors"/></a></button>
                <%}%>
                <%if (userType.equals("G")) {%>
                    <button type="button"><a href="${pageContext.request.contextPath}?command=showAllBooks"><fmt:message key="button.show_all_books"/></a></button>
                    <button type="button"><a href="${pageContext.request.contextPath}?command=getBookByAuthor"><fmt:message key="button.get_book_by_author"/></a></button>
                    <button type="button"><a href="${pageContext.request.contextPath}?command=getNumberOfInstance"><fmt:message key="button.get_number_of_instance"/></a></button>
                <%}%>
                </div>
            </div>

            <div >
                <%if (userType.equals("null")) {%>
                    <button type="button"><a href="${pageContext.request.contextPath}?command=authorization"><fmt:message key="button.login"/></a></button>
                    <button type="button"><a href="${pageContext.request.contextPath}?command=registration"><fmt:message key="button.registration"/></a></button>
                    <button type="button"><a href="${pageContext.request.contextPath}?command=asGuest"><fmt:message key="button.as_a_guest"/></a></button>
                <%} else {%>
                    <button type="button"><a href="${pageContext.request.contextPath}?command=logOut"><fmt:message key="button.logout"/></button>

                <%}%>
            </div>
        </body>
</html>