package controller.command;

import model.dao.DAOUser;
import model.entity.User;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;

public class RegistrationCommand extends Command{

    final String urlPattern = "registration";

    @Override
    public String getPattern() {
        return urlPattern;
    }

    @Override
    public void doGet(HttpServletRequest request, HttpServletResponse response, ServletContext servletContext)
            throws ServletException, IOException {

        RequestDispatcher dispatcher = request.getServletContext()
                .getRequestDispatcher("/view/registrationPage.jsp");
        dispatcher.forward(request, response);
    }

    @Override
    public void doPost(HttpServletRequest request, HttpServletResponse response, ServletContext servletContext) throws ServletException, IOException {
        if(request.getParameter("command").equals("registration")){
            String login = request.getParameter("login");
            String password = request.getParameter("password");
            String real_name = request.getParameter("name");

            String errorString = "";

            try{
                DAOUser daoUser = new DAOUser();
                if(daoUser.loginHandler(login)){
                    errorString = "User with this login already exists.";
                    request.getRequestDispatcher("/view/registrationPage.jsp").forward(request, response);
                }
                else {
                    User user = new User(login, password, "R", real_name);
                    daoUser.createAccount(user);

                    HttpSession session = request.getSession(true);
                    session.setAttribute("user", user);
                    session.setAttribute("error", errorString);

                    request.getRequestDispatcher("/view/mainPage.jsp").forward(request, response);
                }
            }catch (Exception e){
                e.printStackTrace();
            }
        }
    }
}

