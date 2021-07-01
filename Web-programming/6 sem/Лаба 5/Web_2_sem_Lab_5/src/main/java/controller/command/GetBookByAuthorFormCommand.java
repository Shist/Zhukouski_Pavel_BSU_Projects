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

public class GetBookByAuthorFormCommand extends Command {

    final String urlPattern = "getBookByAuthorForm";

    public List<Book> bookList;

    @Override
    public String getPattern() {
        return urlPattern;
    }

    @Override
    public void doGet(HttpServletRequest request, HttpServletResponse response, ServletContext servletContext)
            throws ServletException, IOException {
        RequestDispatcher dispatcher = request.getServletContext()
                .getRequestDispatcher("/view/getBookByAuthorFormPage.jsp");
        dispatcher.forward(request, response);
    }

    @Override
    public void doPost(HttpServletRequest request, HttpServletResponse response, ServletContext servletContext)
            throws ServletException, IOException {
        if(request.getParameter("command").equals("getBookByAuthorResult")){
            String author_name = request.getParameter("author_name");
            try{
                bookList = (new DAOBook()).getBookByAuthor(author_name);
            }catch (Exception e){
                e.printStackTrace();
            }
            request.getRequestDispatcher("/view/getBookByAuthorResultPage.jsp").forward(request, response);
        }
    }
}
