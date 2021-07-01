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

public class GetBookByAuthorResultCommand extends Command {

    final String urlPattern = "getBookByAuthorResult";

    public List<Book> bookList;

    @Override
    public String getPattern() {
        return urlPattern;
    }

    @Override
    public void doGet(HttpServletRequest request, HttpServletResponse response, ServletContext servletContext)
            throws ServletException, IOException {

        request.setAttribute("booksList", (new GetBookByAuthorFormCommand()).bookList);

        RequestDispatcher dispatcher = request.getServletContext()
                .getRequestDispatcher("/view/getBookByAuthorResultPage.jsp");
        dispatcher.forward(request, response);
    }
}
