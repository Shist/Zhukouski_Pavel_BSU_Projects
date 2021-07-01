package bel.pvzhu.filter;

import bel.pvzhu.bean.UserBean;

import javax.ejb.EJB;
import javax.servlet.*;
import javax.servlet.annotation.WebFilter;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

/**
 * Фильтр для проверки введеных данных пользователем при регистрации
 */

@WebFilter("/register")
public class RegisterFilter implements Filter {

    @EJB
    private UserBean userBean;

    @Override
    public void init(FilterConfig filterConfig) throws ServletException {

    }

    @Override
    public void doFilter(ServletRequest servletRequest, ServletResponse servletResponse, FilterChain filterChain) throws IOException, ServletException {
        HttpServletRequest req = (HttpServletRequest) servletRequest;
        HttpServletResponse resp = (HttpServletResponse) servletResponse;

        if (userBean.check(req.getParameter("login"))){
            filterChain.doFilter(servletRequest, servletResponse);
        } else {
            req.setAttribute("message", "Пользователь с таким логином уже существует");
            req.getRequestDispatcher("/register.jsp").forward(req, resp);
        }
    }

    @Override
    public void destroy() {

    }
}
