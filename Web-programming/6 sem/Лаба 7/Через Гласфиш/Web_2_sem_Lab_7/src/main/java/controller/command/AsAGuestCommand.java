package controller.command;

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

public class AsAGuestCommand extends Command {
    final String urlPattern = "asGuest";

    @Override
    public String getPattern() {
        return urlPattern;
    }

    @Override
    public void doGet(HttpServletRequest request, HttpServletResponse response, ServletContext servletContext)
            throws ServletException, IOException {

        User user = new User("", "", "G", "");

        HttpSession session = request.getSession(true);
        session.setAttribute("user", user);

        RequestDispatcher dispatcher = request.getServletContext()
                .getRequestDispatcher("/view/mainPage.jsp");
        dispatcher.forward(request, response);
    }
}
