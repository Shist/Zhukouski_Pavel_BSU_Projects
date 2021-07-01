package by.mmkle.servlet.journey;

import by.mmkle.bean.JourneyBean;
import by.mmkle.bean.RequestBean;
import by.mmkle.entity.Cars;
import by.mmkle.entity.Drivers;
import by.mmkle.entity.Journeys;
import com.google.gson.Gson;

import javax.ejb.EJB;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.math.BigDecimal;

import static by.mmkle.servlet.util.ServletUtil.getBody;
import static by.mmkle.servlet.util.ServletUtil.prepareResponse;

/**
 * Сервлет для обработки CRUD запросов для поездок, где type это тип запроса
 */

@WebServlet("/journeys")
public class JourneyServlet extends HttpServlet {
    private final Gson gson = new Gson();
    @EJB
    private JourneyBean journeyBean;

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {

        String type = req.getParameter("type");
        String json;
        switch (type) {
            case "request":
                Long requestId = Long.valueOf(req.getParameter("requestId"));
                json = gson.toJson(journeyBean.findJourneyIdByRequestId(requestId));
                break;
            case "driver":
                Long carId = Long.valueOf(req.getParameter("carId"));
                json = gson.toJson(journeyBean.findJourneysForDriver(carId));
                break;
            default:
                throw new IllegalStateException("Unexpected value: " + type);
        }

        prepareResponse(json, resp);
    }

    @Override
    protected void doPut(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String type = req.getParameter("type");
        String json = "";
        if (type == null){
            Journeys journey = gson.fromJson(getBody(req), Journeys.class);
            json = journeyBean.save(journey).toString();
        } else {
            Long journeyId = Long.valueOf(req.getParameter("journeyId"));
            switch (type) {
                case "finish":
                    BigDecimal carState = new BigDecimal(req.getParameter("carState"));
                    json = "Finish journey and set car state";
                    journeyBean.setJourneyIsFinishAndCarState(journeyId, carState);
                    break;
                case "car":
                    Cars car = gson.fromJson(req.getParameter("car"), Cars.class);
                    json = "Update car for journey";
                    journeyBean.updateCarForJourney(car, journeyId);
                    break;
                default:
                    throw new IllegalStateException("Unexpected value: " + type);
            }
        }

        prepareResponse(json, resp);
    }
}
