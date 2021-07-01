package filters;

import javax.servlet.*;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;
import java.io.IOException;
import java.util.Locale;

public class LanguageFilter implements Filter {
    @Override
    public void init(FilterConfig filterConfig) throws ServletException {

    }

    @Override
    public void doFilter(ServletRequest servletRequest, ServletResponse servletResponse, FilterChain filterChain) throws IOException, ServletException {
        HttpServletRequest httpServletRequest = (HttpServletRequest) servletRequest;
        HttpSession session = httpServletRequest.getSession();
        httpServletRequest.setCharacterEncoding("utf8");

        if (session.getAttribute("userLocale") == null) {
            System.out.println(httpServletRequest.getLocale());
            session.setAttribute("userLocale", new Locale("en"));
        }

        String lang = servletRequest.getParameter("lang");
        System.out.println(lang);
        if (lang != null) {
            Locale locale = new Locale(lang);
            session.setAttribute("userLocale", locale);
        }
        filterChain.doFilter(servletRequest, servletResponse);
    }

    @Override
    public void destroy() {

    }
}
