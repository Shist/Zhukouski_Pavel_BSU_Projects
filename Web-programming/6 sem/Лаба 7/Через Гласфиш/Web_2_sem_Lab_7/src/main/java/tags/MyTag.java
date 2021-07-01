package tags;

import javax.servlet.jsp.tagext.TagSupport;
import javax.servlet.jsp.*;
import java.io.IOException;


public class MyTag extends TagSupport {

    @Override
    public int doStartTag() throws JspException {

        int id = (int) pageContext.getAttribute("id", PageContext.REQUEST_SCOPE);
        int number_of_instances = (int) pageContext.getAttribute("number", PageContext.REQUEST_SCOPE);

        String result = "<table class=\"page-table\" " +
                "border=\"1\" cellpadding=\"5\" cellspacing=\"1\" style=\"border-collapse: collapse\">" +
                "<tr><th>ID</th><th>Number of instance</th>" +
                "<tr><td>" + id + "</td><td>" + number_of_instances + "</td></tr></table>";

        try {
            JspWriter out = pageContext.getOut();
            out.write(result);
        } catch (IOException e) {
            throw new JspException(e.getMessage());
        }
        return SKIP_BODY;
    }

}
