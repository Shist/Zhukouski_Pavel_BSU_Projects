import java.lang.reflect.Type;

public class AppleTree extends GardenTree {

    enum AppleTreeType{
        white_filling,
        papier,
        candy
    }

    AppleTreeType t;

    AppleTree()
    {
        name = "SomeAppleTree_" + Integer.toString(tree_num);
        int random_num = 1 + (int) (Math.random() * 3);
        switch (random_num) {
            case 1:
                t = AppleTreeType.white_filling;
                break;
            case 2:
                t = AppleTreeType.papier;
                break;
            case 3:
                t = AppleTreeType.candy;
                break;
        }
        TypeInfo = "Fruit: Apple\nType: " + t;
    }

    AppleTree(int _age, int _fruiting_level, int type_num)
    {
        age = _age;
        fruiting_level = _fruiting_level;
        switch (type_num) {
            case 1:
                t = AppleTreeType.white_filling;
                break;
            case 2:
                t = AppleTreeType.papier;
                break;
            case 3:
                t = AppleTreeType.candy;
                break;
            default:
                System.out.println("Something get wrong!");
                break;
        }
        TypeInfo = "Fruit: Apple\nType: " + t;
    }

    void printAppleTreeInfo() {
        printBasicInfo();
        System.out.println(TypeInfo);
    }
}
