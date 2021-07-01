package by.mmkle.servlet.car;

import by.mmkle.bean.CarBean;
import by.mmkle.entity.Cars;
import by.mmkle.entity.Drivers;
import by.mmkle.entity.Requests;
import by.mmkle.servlet.util.ServletUtil;
import com.google.gson.Gson;

import javax.ejb.EJB;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.List;

import static by.mmkle.servlet.util.ServletUtil.getBody;
import static by.mmkle.servlet.util.ServletUtil.prepareResponse;

/**
 * Сервлет для обработки CRUD запросов для машины, где type это тип запроса
 */
@WebServlet("/cars")
public class CarServlet  extends HttpServlet {
    @EJB
    private CarBean carBean;

    private Gson gson = new Gson();

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String type = req.getParameter("type");
        String json;
        switch (type) {
            case "id":
                Long carId = Long.valueOf(req.getParameter("carId"));
                json = gson.toJson(carBean.findCarById(carId));
                break;
            case "regNum":
                String regNum = req.getParameter("regNum");
                json = gson.toJson(carBean.findCarIdByRegNum(regNum));
                break;
            case "onRepair":
                json = gson.toJson(carBean.findCarsOnRepair());
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
        if (type != null) {
            switch (type) {
                case "onRepair" :
                    Long carId = Long.valueOf(req.getParameter("carId"));
                    json = "Setting car on repair";
                    carBean.setCarOnRepair(carId);
                    break;
                case "freeCar":
                    Requests request = gson.fromJson(getBody(req), Requests.class);
                    json = gson.toJson(carBean.findCarForRequest(request));
                    break;
            }

        } else {
            Cars car = gson.fromJson(getBody(req), Cars.class);
            json = carBean.save(car).toString();
        }

        prepareResponse(json, resp);
    }
}
