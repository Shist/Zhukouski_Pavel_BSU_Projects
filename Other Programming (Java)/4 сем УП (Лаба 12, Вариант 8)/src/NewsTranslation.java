import java.io.*;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/NewsTranslation")
public class NewsTranslation extends HttpServlet {
    private String qestionPath = "C:\\Users\\user\\IdeaProjects\\4 сем УП (Лаба 12, Вариант 8)\\qestons\\";
    private static final long serialVersionUID = 1L;

    public NewsTranslation() {
        super();
        News();
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setCharacterEncoding("utf-8");
        String command = request.getParameter("enter");
        String voterName = request.getParameter("voterName");
        String result;
        if (command.equals("Begin")){
            progress.put(voterName , 1);
            result = getNextQestion(voterName);
        } else if(command.equals("Next")){
            result = getNextQestion(voterName);
        }else{
            int answer = Integer.parseInt(command);
            result = getResults(voterName, answer);
        }
        response.setContentType("text/html; charset=utf-8");
        response.setStatus(HttpServletResponse.SC_OK);
        PrintWriter out = response.getWriter();
        out.write(result);
        out.flush();
        out.close();
    }

    protected void News(){
        System.out.print("Идёт подключение к серверу...\n");
        System.out.print("Подключение к серверу прошло успешно...\n");
        System.out.print("Введите exit для выхода...\n");
        System.out.print("Выберите дату, новость которой хотите просмотреть:\n");
        System.out.print("\n1) 19.05.2020\n2) 18.05.2020\n3) 17.05.2020\n4) 16.05.2020\n5) 15.05.2020\n6) 14.05.2020\n7) 13.05.2020\n");
        Scanner sc = new Scanner(System.in);
        char[] symb = sc.nextLine().toCharArray();
        while(!(symb[0] == 'e' && symb[1] == 'x' && symb[2] == 'i' && symb[3] == 't'))
        {
            if (symb[0] == '1')
            {
                System.out.print("Первое место по количеству зараженных прочно закрепилось за США. Там зарегистрировано\n более 1,66 млн заболевших, более 98 тысяч человек умерли, поправились более 379 тысяч человек.\n" +
                        "Читать полностью:  https://news.tut.by/world/685995.html\n");
            }
            else if (symb[0] == '2')
            {
                System.out.print("На втором месте в мире по масштабам заражения населения — Бразилия. К настоящему моменту\n в стране насчитывается более 374 тысяч заразившихся и более 23 тысяч летальных исходов,\n поправились более 153 тысяч человек. Президент Бразилии Жаир Болсонару выступал против\n введения карантинных мер и называл болезнь «гриппиком» вплоть до конца апреля. И после этого риторика\n Болсонару сильно не изменилась, а опросы общественного мнения в Бразилии показывают, что почти половина\n населения выступает за импичмент.\n" +
                        "Читать полностью:  https://news.tut.by/world/685995.html\n");
            }
            else if (symb[0] == '3')
            {
                System.out.print("На третьем месте по количеству зараженных — Россия. Там зафиксировано более 353 тысяч\n зараженных, из них 3633 — с летальным исходом, выздоровели более 118 тысяч человек. Только\n в Москве за последние сутки скончались 76 человек.\n" +
                        "Читать полностью:  https://news.tut.by/world/685995.html\n");
            }
            else if (symb[0] == '4')
            {
                System.out.print("В Великобритании (4-е место в мире: более 262 тысяч зараженных/почти 37 тысяч жертв и\n более тысячи выздоровевших — такое небольшое количество выздоровевших объясняется тем, что\n зараженные в стране лечатся дома и в госпиталь попадают только в случае серьезного ухудшения,\n чаще всего сразу в интенсивную терапию, а статистика учитывает только выписанных из больниц пациентов),\n темпы заражения падают уже четвертый день. За последние сутки коронавирусом заразились более\n 1,6 тысячи человек (днем ранее — 2,4 тысячи человек, еще ранее — 3,0 тысячи, еще ранее — 3,3 тысячи человек). Для сравнения,\n на пике фиксировалось более 8,7 тысячи человек в день.\n" +
                        "Читать полностью:  https://news.tut.by/world/685995.html\n");
            }
            else if (symb[0] == '5')
            {
                System.out.print("Европа тем временем отходит от пандемии коронавируса. Во многих странах смягчают карантин,\n вводят послабления. Например, Греция открыла острова (но туристов на них пока не ждут),\n Испания ждет туристов с 1 июля, а Черногория готова впустить туристов из некоторых стран уже\n с 1 июня (но белорусов пока в списке нет).\n" +
                        "Читать полностью:  https://news.tut.by/world/685995.html\n");
            }
            else if (symb[0] == '6')
            {
                System.out.print("У нашей страны-соседки Польши зафиксирован 21 631 случай заражения, умерли 1007 человека,\n поправились — 9276. За последние сутки выявили 305 случаев заражения коронавирусом и не\n зафиксировано ни одного летального исхода.\n" +
                        "Читать полностью:  https://news.tut.by/world/685995.html\n");
            }
            else if (symb[0] == '7')
            {
                System.out.print("В Украине (21 245 зараженных / 623 жертвы / 7234 человек выздоровели), по словам министра\n здравоохранения страны Максима Степанова, около 20% заразившихся — 4112 человек — медики.\n По его словам, такая ситуация сложилась из-за того, что украинские больницы не были готовы к\n пандемии коронавируса: не было ни средств индивидуальной защиты, ни респираторов, ни масок, не были\n просчитаны маршруты доставки больных.\n" +
                        "Читать полностью:  https://news.tut.by/world/685995.html\n");
            }
            else
            {
                System.out.print("Incorrect choice");
            }
            symb = sc.nextLine().toCharArray();
        }
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doGet(request, response);
    }

    Map<String, Integer> progress = new HashMap<String, Integer>();

    protected String getNextQestion(String voterName){
        int pr = progress.get(voterName);
        String qestion[] = getQestion(pr);
        String code = "<html>\n" +
                "<head>\n" +
                "    <meta charset=\"UTF-8\">\n" +
                "    <title>" + (pr + 1) + "</title>\n" +
                "</head>\n" +
                "<body>\n";
        if (qestion == null) {
            code += "<html>\n" +
                    "<head>\n" +
                    "    <meta charset=\"UTF-8\">\n" +
                    "    <title>" + (pr + 1) + "</title>\n" +
                    "</head>\n" +
                    "<body>\n" +
                    "<h1><strong>The questions were over: (</strong></h1>\n" +
                    "<h1><a title=\"Try again\" href=\"/index.jsp\">Home</a></h1>\n" +
                    "</body>\n" +
                    "</html>";
        }else {
            code +=          "<html>\n" +
                            "<head>\n" +
                            "    <meta charset=\"UTF-8\">\n" +
                            "    <title>" + (pr + 1) + "</title>\n" +
                            "</head>\n" +
                            "<body>\n" +
                            "<h1><strong>Qestion " + pr + "</strong></h1>\n" +
                            "<h1><strong>" + qestion[0] + "</strong></h1>\n" +
                            "<br>\n" +
                            "<br>\n" +
                            "<form action=\"NewsTranslation\" method=\"GET\">\n" +
                            "     <input type=\"hidden\" name=\"voterName\" value=\"" + voterName + "\" /> \n";
            for (int i = 1; i < qestion.length; ++i)
                code += "     <input type=\"submit\" value=\"" + i + "\" name=\"enter\"/> " + qestion[i] + " <br><br> \n";
            code += "</form>\n" +
                    "</body>\n" +
                    "</html>";
            progress.put(voterName, pr + 1);
        }
        return  code;
    }

    protected String getResults(String voterName, int answer){
        int pr = progress.get(voterName) - 1;
        String qestion[] = getQestion(pr);
        Integer results[] = getResults(pr, answer);
        String code =
                "<html>\n" +
                        "<head>\n" +
                        "    <meta charset=\"UTF-8\">\n" +
                        "    <title>"+(pr+1)+"</title>\n" +
                        "</head>\n" +
                        "<body>\n" +
                        "<h1><strong>Qestion "+pr +"</strong></h1>\n" +
                        "<h1><strong>"+qestion[0]+"</strong></h1>\n" +
                        "<br>\n";
        for (int i = 0; i < results.length; ++i)
            code += "<p> (" +results[i] + "%) - " + qestion[i+1] + "</p>\n";
        code +=         "<br>\n"+
                        "<form action=\"NewsTranslation\" method=\"GET\">\n" +
                        "     <input type=\"hidden\" name=\"voterName\" value=\""+voterName+"\" /> \n"+
                        "     <input type=\"submit\" value=\"Next\" name=\"enter\"/> \n"+
                        "</form>\n" +
                        "</body>\n" +
                        "</html>";
        return  code;
    }

    protected Integer[] getResults(int pr, int answer){
        System.out.println("Results for :" + pr);
        System.out.println("Ansew: " + answer);
        ArrayList<Integer> result = new ArrayList<>();
        int total = 1;
        try {
            Scanner sc = new Scanner(new File(qestionPath + pr + ".res"));
            while (sc.hasNextLine())
                result.add(Integer.parseInt(sc.nextLine()));
            for (int v : result)
                total+= v;
        } catch (FileNotFoundException e) {
            String[] buf = getQestion(pr);
            for (int i = 0; i < buf.length-1; ++i)
                result.add (0);
        } finally {
            try {
                result.set(answer-1, result.get(answer-1) + 1);
                FileWriter writer = new FileWriter(qestionPath + pr + ".res");
                for (int r:result)
                    writer.write(r+"\n");
                writer.close();
            } catch (IOException e) {
                return null;
            }

        }
        for(int i = 0; i < result.size(); ++i)
            result.set(i, result.get(i)*100/total);
        return result.toArray(new Integer[result.size()]);
    }

    protected String[] getQestion(int pr){
        ArrayList<String> qestion = new ArrayList<>();
        try {
            Scanner sc = new Scanner(new File(qestionPath + pr + ".txt"));
            while (sc.hasNextLine()){
                qestion.add(sc.nextLine());
            }
        } catch (FileNotFoundException e) {
            return null;
        }
        return qestion.toArray(new String[qestion.size()]);

    }
}
