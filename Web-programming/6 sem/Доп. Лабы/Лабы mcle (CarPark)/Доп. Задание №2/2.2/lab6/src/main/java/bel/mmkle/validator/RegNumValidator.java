package bel.mmkle.validator;

import javax.faces.application.FacesMessage;
import javax.faces.component.UIComponent;
import javax.faces.context.FacesContext;
import javax.faces.validator.FacesValidator;
import javax.faces.validator.Validator;
import javax.faces.validator.ValidatorException;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

@FacesValidator("RegNumValidator")
public class RegNumValidator implements Validator {

    private static final String REG_NUM_PATTERN = "[a-z]{1}[0-9]{7}";

    private Pattern pattern;

    public RegNumValidator() {
        pattern = Pattern.compile(REG_NUM_PATTERN);
    }

    @Override
    public void validate(FacesContext facesContext, UIComponent uiComponent, Object o) throws ValidatorException {
        Matcher matcher = pattern.matcher(o.toString());
        if (!matcher.matches()) {
            FacesMessage msg = new FacesMessage("Неверный формат рег номера");
            msg.setSeverity(FacesMessage.SEVERITY_ERROR);
            throw new ValidatorException(msg);
        }
    }
}
