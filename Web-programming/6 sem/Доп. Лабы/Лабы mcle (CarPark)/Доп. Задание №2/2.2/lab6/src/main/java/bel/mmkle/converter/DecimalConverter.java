package bel.mmkle.converter;

import javax.faces.application.FacesMessage;
import javax.faces.component.UIComponent;
import javax.faces.context.FacesContext;
import javax.faces.convert.Converter;
import javax.faces.convert.ConverterException;
import javax.faces.convert.FacesConverter;
import java.math.BigDecimal;

@FacesConverter("DecimalConverter")
public class DecimalConverter implements Converter {
    @Override
    public Object getAsObject(FacesContext facesContext, UIComponent uiComponent, String value) {
        if (value.contains(",")){
            value = value.replace(',', '.');
        }

        BigDecimal obj = null;

        try{
            obj = new BigDecimal(value);
        } catch (Exception ex){
            FacesMessage msg = new FacesMessage ("Ошибка конвертации значения");
            msg.setSeverity(FacesMessage.SEVERITY_ERROR);
            throw new ConverterException(msg);
        }

        return obj;
    }

    @Override
    public String getAsString(FacesContext facesContext, UIComponent uiComponent, Object o) {
        return o.toString();
    }
}
