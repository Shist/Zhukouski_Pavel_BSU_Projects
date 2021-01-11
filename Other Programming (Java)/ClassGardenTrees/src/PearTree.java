import java.lang.reflect.Type;

public class PearTree extends GardenTree {

    enum PearTreeType{
        August_dew,
        Bere_Giffard,
        Victoria
    }

    PearTreeType t;

    PearTree()
    {
        name = "SomePearTree_" + Integer.toString(tree_num);
        int random_num = 1 + (int) (Math.random() * 3);
        switch (random_num) {
            case 1:
                t = PearTreeType.August_dew;
                break;
            case 2:
                t = PearTreeType.Bere_Giffard;
                break;
            case 3:
                t = PearTreeType.Victoria;
                break;
        }
        TypeInfo = "Fruit: Pear\nType: " + t;
    }

    PearTree(int _age, int _fruiting_level, int type_num)
    {
        age = _age;
        fruiting_level = _fruiting_level;
        switch (type_num) {
            case 1:
                t = PearTreeType.August_dew;
                break;
            case 2:
                t = PearTreeType.Bere_Giffard;
                break;
            case 3:
                t = PearTreeType.Victoria;
                break;
            default:
                System.out.println("Something get wrong!");
                break;
        }
        TypeInfo = "Fruit: Pear\nType: " + t;
    }

    void printPearTreeInfo() {
        printBasicInfo();
        System.out.println(TypeInfo);
    }
}
