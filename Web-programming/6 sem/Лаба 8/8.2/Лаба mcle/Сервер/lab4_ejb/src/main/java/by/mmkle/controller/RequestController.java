package by.mmkle.controller;

import by.mmkle.bean.RequestBean;
import by.mmkle.entity.Requests;

import javax.ejb.EJB;
import javax.ws.rs.Consumes;
import javax.ws.rs.PUT;
import javax.ws.rs.Path;
import javax.ws.rs.Produces;

@Path("/request")
@Produces("application/json")
@Consumes("application/json")
public class RequestController {
    @EJB
    private RequestBean requestBean;

    @PUT
    public void save(Requests request){
        requestBean.save(request);
    }
}
