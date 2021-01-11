import com.sun.org.apache.xalan.internal.xsltc.compiler.Parser;

import java.rmi.AlreadyBoundException;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.Scanner;

public class Client2 {

    public static void News() {
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

    public static void main(String[] argv) {
        CommandClient c;
        try {
            c = new CommandClient();
        } catch (RemoteException e) {
            System.out.print("Server is not available now!!! Power on CommandServerMain first!\n\n");
            return;
            //e.printStackTrace();
        } catch (NotBoundException e) {
            e.printStackTrace();
            return;
        }
        News();

        try {
            CommandServer cs = new CommandServer();
            RunCommand stub = (RunCommand) UnicastRemoteObject.exportObject(cs, 0);
            Registry reg = LocateRegistry.createRegistry(12345);
            reg.bind("CommandServer", stub);
        } catch (RemoteException e) {
            e.printStackTrace();
        } catch (AlreadyBoundException e) {
            e.printStackTrace();
        }
    }
}
