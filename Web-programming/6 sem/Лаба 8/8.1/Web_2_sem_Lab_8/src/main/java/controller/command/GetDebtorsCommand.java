package controller.command;

import model.dao.DAOBook;
import model.dao.DAOFormular;
import model.dao.DAOReader;
import model.entity.Book;
import model.entity.Formular;
import model.entity.Reader;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.List;

public class GetDebtorsCommand extends Command {

    final String urlPattern = "getDebtors";

    @Override
    public String getPattern() {
        return urlPattern;
    }

    @Override
    public void doGet(HttpServletRequest request, HttpServletResponse response, ServletContext servletContext)
            throws ServletException, IOException {
        String errorString = null;

        List<Formular> list = null;
        try {
            list = (new DAOFormular()).getDebtors();
        } catch (Exception e) {
            e.printStackTrace();
            errorString = e.getMessage();
        }

        request.setAttribute("errorString", errorString);
        request.setAttribute("debtorsList", list);

        RequestDispatcher dispatcher = request.getServletContext()
                .getRequestDispatcher("/view/getDebtorsPage.jsp");
        dispatcher.forward(request, response);
    }
}
