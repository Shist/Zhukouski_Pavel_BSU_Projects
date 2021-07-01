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

public class GetBookCommand extends Command {

    final String urlPattern = "getBook";


    @Override
    public String getPattern() {
        return urlPattern;
    }

    @Override
    public void doGet(HttpServletRequest request, HttpServletResponse response, ServletContext servletContext)
            throws ServletException, IOException {
        RequestDispatcher dispatcher = request.getServletContext()
                .getRequestDispatcher("/WEB-INF/view/getBookPage.jsp");
        dispatcher.forward(request, response);
    }

    @Override
    public void doPost(HttpServletRequest request, HttpServletResponse response, ServletContext servletContext)
            throws ServletException, IOException {
        if(request.getParameter("command").equals("getBook")){
            int reader_id = Integer.parseInt(request.getParameter("reader_id"));
            int book_id = Integer.parseInt(request.getParameter("book_id"));
            try{
                (new DAOFormular()).updateReaderInfo(book_id, reader_id);
                (new DAOBook()).updateNumberOfInstanceGet(book_id);
            }catch (Exception e){
                e.printStackTrace();
            }
            request.getRequestDispatcher("/WEB-INF/view/mainPage.jsp").forward(request, response);
        }
    }
}
