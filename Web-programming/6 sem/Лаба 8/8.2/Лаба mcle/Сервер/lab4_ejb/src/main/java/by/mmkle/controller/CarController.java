package by.mmkle.controller;

import by.mmkle.bean.CarBean;
import by.mmkle.entity.Cars;

import javax.ejb.EJB;
import javax.ws.rs.*;
import java.util.List;

@Path("/car")
@Produces("application/json")
@Consumes("application/json")
public class CarController {

    @EJB
    private CarBean carBean;

    @GET
    @Path("/{id}")
    public Cars findById(@PathParam("id") Long id){
        return carBean.findCarById(id);
    }

    @PUT
    public void save(Cars car){
        carBean.save(car);
    }

    @GET
    @Path("/repair/list")
    public List<Cars> listCarsOnRapair(){
        return carBean.findCarsOnRepair();
    }

    @PUT
    @Path("/repair/{carId}")
    public void setOnRepair(@PathParam("carId") Long carId){
        carBean.setCarOnRepair(carId);
    }
}
