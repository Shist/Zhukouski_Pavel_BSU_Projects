package controller.command;

import model.dao.DAOAuthorization;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

public class AuthorizationCommand extends Command {

    final String urlPattern = "authorization";

    @Override
    public String getPattern() {
        return urlPattern;
    }

    @Override
    public void doGet(HttpServletRequest request, HttpServletResponse response, ServletContext servletContext)
            throws ServletException, IOException {

        RequestDispatcher dispatcher = request.getServletContext()
                .getRequestDispatcher("/view/authorization.jsp");
        dispatcher.forward(request, response);
    }

    @Override
    public void doPost(HttpServletRequest request, HttpServletResponse response, ServletContext servletContext) throws ServletException, IOException {
        if(request.getParameter("command").equals("authorization")){
            String login = request.getParameter("login");
            String password = request.getParameter("password");
            String user_type = null;

            String errorString = "";

            try{
                user_type = (new DAOAuthorization()).login(login, password);
            }catch (Exception e){
                errorString = e.getMessage();
            }

            request.setAttribute("errorString", errorString);

            if (user_type != null) {
                if(user_type.equals("R")){
                    request.getRequestDispatcher("/view/readerMenuPage.jsp").forward(request, response);
                }else if(user_type.equals("L")){
                    request.getRequestDispatcher("/view/librarianMenuPage.jsp").forward(request, response);
                }else if(user_type.equals("G")){
                    request.getRequestDispatcher("/view/guestMenuPage.jsp").forward(request, response);
                }
            }
            else
            {
                request.getRequestDispatcher("/view/authorization.jsp").forward(request, response);
            }
        }
    }
}
