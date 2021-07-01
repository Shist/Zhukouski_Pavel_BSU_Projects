/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package controller.command;

import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.*;
import java.io.IOException;

/**
 *
 * @author Pavel Zhukovskiy
 */
public abstract class Command extends HttpServlet {

    public abstract String getPattern();
    @Override
    protected void service(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        super.service(req, resp);
        HttpSession session = req.getSession(true);
        Integer visitCount = new Integer(0);
        String visitCountKey = new String("visitCount");
        String userIDKey = new String("userID");
        String userID = new String("ABCD");

        if (session.isNew()) {
            session.setAttribute(userIDKey, userID);
        } else {
            visitCount = (Integer)session.getAttribute(visitCountKey);
            visitCount = visitCount + 1;
        }
        session.setAttribute(visitCountKey,  visitCount);
        Cookie cookie = new Cookie("cookie", visitCount + session.getLastAccessedTime() + "");
        resp.addCookie(cookie);
    }
    public abstract void doGet(HttpServletRequest request, HttpServletResponse response, ServletContext servletContext) throws ServletException, IOException ;

    public void doPost(HttpServletRequest request, HttpServletResponse response, ServletContext servletContext)
            throws ServletException, IOException{
        doGet(request, response, servletContext);
    }
}
