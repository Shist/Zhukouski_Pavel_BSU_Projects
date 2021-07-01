package by.mmkle.servlet.request;

import by.mmkle.bean.RequestBean;
import by.mmkle.entity.Journeys;
import by.mmkle.entity.Requests;
import com.google.gson.Gson;

import javax.ejb.EJB;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

import static by.mmkle.servlet.util.ServletUtil.getBody;
import static by.mmkle.servlet.util.ServletUtil.prepareResponse;

/**
 * Сервлет для обработки CRUD запросов для заявок, где type это тип запроса
 */

@WebServlet("/requests")
public class RequestServlet extends HttpServlet {
    @EJB
    private RequestBean requestBean;

    private final Gson gson = new Gson();

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {

        Long requestId = Long.valueOf(req.getParameter("requestId"));
        String json = gson.toJson(requestBean.findRequestById(requestId));

        prepareResponse(json, resp);
    }

    @Override
    protected void doDelete(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        Long requestId = Long.valueOf(req.getParameter("requestId"));
        String json = gson.toJson("Delete request");
        requestBean.deleteRequestById(requestId);

        prepareResponse(json, resp);
    }

    @Override
    protected void doPut(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        Requests request = gson.fromJson(getBody(req), Requests.class);
        String json = requestBean.save(request).toString();
        prepareResponse(json, resp);
    }
}
