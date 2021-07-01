package by.mmkle.servlet.car;

import by.mmkle.bean.CarBean;
import by.mmkle.entity.Cars;
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

/**
 * Сервлет для отображения списка машин
 */

@WebServlet("/cars/list")
public class CarListServlet extends HttpServlet {
    @EJB
    private CarBean carBean;

    private Gson gson = new Gson();

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        List<Cars> list = carBean.getAll();

        String carListJson = gson.toJson(list);

        PrintWriter out = resp.getWriter();
        resp.setContentType("application/json");
        resp.setCharacterEncoding("UTF-8");
        out.print(carListJson);
        out.flush();
    }
}
