package controller.command;

import model.entity.User;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

public class ChatCommand extends Command {

    final String urlPattern = "chat";

    @Override
    public String getPattern() {
        return urlPattern;
    }

    @Override
    public void doGet(HttpServletRequest request, HttpServletResponse response, ServletContext servletContext) throws ServletException, IOException {
        User user = (User) request.getSession().getAttribute("user");
        request.setAttribute("senderId", user.getLogin());

        RequestDispatcher dispatcher = request.getServletContext()
                .getRequestDispatcher("/view/chatPage.jsp");
        dispatcher.forward(request, response);
    }
}
