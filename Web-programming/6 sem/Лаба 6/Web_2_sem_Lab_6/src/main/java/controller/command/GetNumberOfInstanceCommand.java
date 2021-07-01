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

public class GetNumberOfInstanceCommand extends Command {

    final String urlPattern = "getNumberOfInstance";

    public List<Book> bookList;

    @Override
    public String getPattern() {
        return urlPattern;
    }

    @Override
    public void doGet(HttpServletRequest request, HttpServletResponse response, ServletContext servletContext)
            throws ServletException, IOException {

        String errorString = null;
        int number = 0;
        try {
            number = (new DAOBook()).getNumberOfInstance(5);
        } catch (Exception e) {
            e.printStackTrace();
            errorString = e.getMessage();
        }

        request.setAttribute("errorString", errorString);
        request.setAttribute("number", number);
        request.setAttribute("id", 5);

        RequestDispatcher dispatcher = request.getServletContext()
                .getRequestDispatcher("/view/getNumberOfInstancePage.jsp");
        dispatcher.forward(request, response);
    }
}
