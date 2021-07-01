package controller.command;

import model.dao.DAOBook;
import model.entity.Book;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.List;

public class GetBookByAuthorCommand extends Command {

    final String urlPattern = "getBookByAuthor";

    @Override
    public String getPattern() {
        return urlPattern;
    }

    @Override
    public void doGet(HttpServletRequest request, HttpServletResponse response, ServletContext servletContext)
            throws ServletException, IOException {

        String errorString = null;

        List<Book> list = null;
        try {
            list = (new DAOBook()).getBookByAuthor("J.K.Rowling");
        } catch (Exception e) {
            e.printStackTrace();
            errorString = e.getMessage();
        }

        request.setAttribute("errorString", errorString);
        request.setAttribute("booksList", list);

        RequestDispatcher dispatcher = request.getServletContext()
                .getRequestDispatcher("/WEB-INF/view/getBookByAuthorPage.jsp");
        dispatcher.forward(request, response);
    }
}
