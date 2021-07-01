package controller.command;

import model.dao.DAOBook;
import model.dao.DAOFormular;
import model.entity.Book;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.List;

public class ReturnBookCommand extends Command {

    final String urlPattern = "returnBook";


    @Override
    public String getPattern() {
        return urlPattern;
    }

    @Override
    public void doGet(HttpServletRequest request, HttpServletResponse response, ServletContext servletContext)
            throws ServletException, IOException {
        RequestDispatcher dispatcher = request.getServletContext()
                .getRequestDispatcher("/view/returnBookPage.jsp");
        dispatcher.forward(request, response);
    }

    @Override
    public void doPost(HttpServletRequest request, HttpServletResponse response, ServletContext servletContext)
            throws ServletException, IOException {
        if(request.getParameter("command").equals("returnBook")){
            int book_id = Integer.parseInt(request.getParameter("book_id"));
            try{
                (new DAOFormular()).returnBook(book_id);
                (new DAOBook()).updateNumberOfInstancePut(book_id);
            }catch (Exception e){
                e.printStackTrace();
            }
            request.getRequestDispatcher("/view/mainPage.jsp").forward(request, response);
        }
    }
}
