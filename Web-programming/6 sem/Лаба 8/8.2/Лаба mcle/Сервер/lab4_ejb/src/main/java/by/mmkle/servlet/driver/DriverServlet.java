package by.mmkle.servlet.driver;

import by.mmkle.bean.DriverBean;
import by.mmkle.entity.Drivers;
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
 * Сервлет для обработки CRUD запросов для водителя, где type это тип запроса
 */

@WebServlet("/drivers")
public class DriverServlet extends HttpServlet {
    @EJB
    private DriverBean driverBean;

    private final Gson gson = new Gson();

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String type = req.getParameter("type");
        String json;
        switch (type) {
            case "carId":
                Long driverId = Long.valueOf(req.getParameter("driverId"));
                json = gson.toJson(driverBean.findCarByDriverId(driverId));
                break;
            case "driverId":
                String regNum = req.getParameter("regNum");
                json = gson.toJson(driverBean.findDriverIdByRegNum(regNum));
                break;
            default:
                throw new IllegalStateException("Unexpected value: " + type);
        }

        prepareResponse(json, resp);
    }

    @Override
    protected void doPut(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        Drivers driver = gson.fromJson(getBody(req), Drivers.class);
        String json = driverBean.save(driver).toString();
        prepareResponse(json, resp);
    }
}
