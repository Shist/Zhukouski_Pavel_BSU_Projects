package controller.command;

import model.dao.DAOUser;
import model.entity.User;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;
import java.util.Date;
import java.util.List;

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
        if(request.getParameter("command") == null ||
                request.getParameter("command").equals("authorization")){
            String login = request.getParameter("login");
            String password = request.getParameter("password");

            String errorString = "";

            try{
                DAOUser daoUser = new DAOUser();
                if(!daoUser.loginHandler(login)){
                    errorString = "Invalid login";
                    HttpSession session = request.getSession(true);
                    session.setAttribute("error", errorString);
                    request.getRequestDispatcher("/view/authorization.jsp").forward(request, response);
                }
                else {
                    User user = daoUser.login(login, password);
                    if(user != null){

                        HttpSession session = request.getSession(true);
                        session.setAttribute("user", user);
                        request.getRequestDispatcher("/view/mainPage.jsp").forward(request, response);

                    }
                    else {
                        errorString = "Invalid password";
                        HttpSession session = request.getSession(true);
                        session.setAttribute("error", errorString);
                        request.getRequestDispatcher("/view/authorization.jsp").forward(request, response);
                    }
                }
            }catch (Exception e){
                e.printStackTrace();
            }
        }
    }
}
