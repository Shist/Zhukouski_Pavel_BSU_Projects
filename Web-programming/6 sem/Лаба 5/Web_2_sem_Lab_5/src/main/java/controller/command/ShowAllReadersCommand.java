package controller.command;

import model.dao.DAOReader;
import model.entity.Reader;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.List;

public class ShowAllReadersCommand extends Command {

    final String urlPattern = "showAllReaders";

    @Override
    public String getPattern() {
        return urlPattern;
    }

    @Override
    public void doGet(HttpServletRequest request, HttpServletResponse response, ServletContext servletContext)
            throws ServletException, IOException {
        String errorString = null;

        List<Reader> list = null;
        try {
            list = (new DAOReader()).printAllReaders();
        } catch (Exception e) {
            e.printStackTrace();
            errorString = e.getMessage();
        }

        request.setAttribute("errorString", errorString);
        request.setAttribute("readersList", list);

        RequestDispatcher dispatcher = request.getServletContext()
                .getRequestDispatcher("/view/showAllReadersPage.jsp");
        dispatcher.forward(request, response);
    }
}
