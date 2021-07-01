package controller;

import controller.command.*;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;


@WebServlet(urlPatterns = {"/lab_7"})
public class MainServlet extends HttpServlet {

    private static final long serialVersionUID = 1L;
    public Map<String, Command> commands;

    public MainServlet() {
        super();
        this.commands = new HashMap<>();
    }

    @Override
    public void init() {
        System.out.println("main servlet init");

        Command[] commands = { new GetBookByAuthorCommand(), new GetBookCommand(),
                new GetDebtorsCommand(), new GetNumberOfInstanceCommand(), new MainCommand(), new ReturnBookCommand(),
                new ShowAllBooksCommand(), new ShowAllReadersCommand(), new AuthorizationCommand(),
                new LogOutCommand(), new AsAGuestCommand(), new RegistrationCommand()
        };
        for (Command c : commands) {
            this.commands.put(c.getPattern(), c);
        }
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String command = request.getParameter("command");
        if (command == null) {
            commands.get("main").doGet(request, response, this.getServletContext());
        } else if (commands.containsKey(command)) {
            commands.get(command).doGet(request, response, this.getServletContext());
        }
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String command = request.getParameter("command");
        if (command == null) {
            commands.get("main").doPost(request, response, this.getServletContext());
        } else if (commands.containsKey(command)) {
            commands.get(command).doPost(request, response, this.getServletContext());
        }
    }
}
