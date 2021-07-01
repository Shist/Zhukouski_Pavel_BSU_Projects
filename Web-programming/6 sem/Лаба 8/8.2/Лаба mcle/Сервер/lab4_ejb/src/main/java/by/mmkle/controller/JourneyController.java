package by.mmkle.controller;

import by.mmkle.bean.JourneyBean;
import by.mmkle.entity.Journeys;

import javax.ejb.EJB;
import javax.ws.rs.*;
import java.math.BigDecimal;
import java.util.List;

@Path("/journey")
@Produces("application/json")
@Consumes("application/json")
public class JourneyController {

    @EJB
    private JourneyBean journeyBean;

    @GET
    @Path("/list")
    public List<Journeys> list(){
        return journeyBean.findAll();
    }

    @GET
    @Path("/list/{carId}")
    public List<Journeys> list(@PathParam("carId") Long carId){
        return journeyBean.findJourneysForDriver(carId);
    }

    @PUT
    public void save(Journeys journey){
        journeyBean.save(journey);
    }

    @PUT
    @Path("/finish/{id}/{state}")
    public void finishAndRate(@PathParam("id") Long id,
                              @PathParam("state") BigDecimal state){
        journeyBean.setJourneyIsFinishAndCarState(id, state);
    }
}
