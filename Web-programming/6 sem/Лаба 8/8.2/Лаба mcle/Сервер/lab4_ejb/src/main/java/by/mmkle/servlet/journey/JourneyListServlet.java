package by.mmkle.servlet.journey;

import by.mmkle.bean.JourneyBean;
import by.mmkle.entity.Journeys;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.google.gson.*;

import javax.ejb.EJB;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.lang.reflect.Type;
import java.util.List;

import static by.mmkle.servlet.util.ServletUtil.prepareResponse;

/**
 * Сервлет для отображения списка поездок
 */

@WebServlet("/journeys/list")
public class JourneyListServlet extends HttpServlet {
    @EJB
    private JourneyBean journeyBean;

    private ObjectMapper mapper = new ObjectMapper();

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        List<Journeys> list = journeyBean.findAll();

        String json = mapper.writeValueAsString(list);

        prepareResponse(json, resp);
    }
}
