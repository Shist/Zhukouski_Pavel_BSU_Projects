package bel.mmkle.filter;

import bel.mmkle.bean.UserBean;

import javax.ejb.EJB;
import javax.servlet.*;
import javax.servlet.annotation.WebFilter;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;

/**
 * Фильтр для выбора меню по роли пользователя
 */

@WebFilter("/menu")
public class MenuFilter implements Filter {
    @EJB
    private UserBean userBean;

    @Override
    public void init(FilterConfig filterConfig) throws ServletException {

    }

    @Override
    public void doFilter(ServletRequest servletRequest, ServletResponse servletResponse, FilterChain filterChain) throws IOException, ServletException {
        HttpServletRequest req = (HttpServletRequest) servletRequest;
        HttpServletResponse res = (HttpServletResponse) servletResponse;
        HttpSession session = req.getSession();
        Long userId = (Long) session.getAttribute("userId");
        if (userId == null){
            res.sendRedirect("/lab6/index.xhtml");
            return;
        }
        Long roleId = userBean.getRole(userId);

        if (roleId == 1) {
            res.sendRedirect("/lab6/admin_menu.xhtml");
        } else if (roleId == 2) {
            res.sendRedirect("/lab6/officer_menu.xhtml");
        } else if (roleId == 3) {
            res.sendRedirect("/lab6/user_menu.xhtml");
        } else {
            res.sendRedirect("/lab6/index.xhtml");
        }
    }

    @Override
    public void destroy() {

    }
}
