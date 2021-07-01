package by.mmkle.controller;

import by.mmkle.bean.DriverBean;
import by.mmkle.entity.Cars;
import by.mmkle.entity.Drivers;

import javax.ejb.EJB;
import javax.ws.rs.*;

@Path("/driver")
@Produces("application/json")
@Consumes("application/json")
public class DriverController {
    @EJB
    private DriverBean driverBean;

    @PUT
    public void save(Drivers driver){
        driverBean.save(driver);
    }

    @GET
    @Path("/car/{driverId}")
    public Cars findCarbyDriverId(@PathParam("driverId") Long driverId){
        return driverBean.findCarByDriverId(driverId);
    }
}
