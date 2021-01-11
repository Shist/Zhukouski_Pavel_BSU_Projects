public class OrangeTree extends GardenTree {

    enum OrangeTreeType{
        Hamlin,
        Verna,
        Salustiana
    }

    OrangeTreeType t;

    OrangeTree()
    {
        name = "SomeOrangeTree_" + Integer.toString(tree_num);
        int random_num = 1 + (int) (Math.random() * 3);
        switch (random_num) {
            case 1:
                t = OrangeTreeType.Hamlin;
                break;
            case 2:
                t = OrangeTreeType.Verna;
                break;
            case 3:
                t = OrangeTreeType.Salustiana;
                break;
        }
        TypeInfo = "Fruit: Orange\nType: " + t;
    }

    OrangeTree(int _age, int _fruiting_level, int type_num)
    {
        age = _age;
        fruiting_level = _fruiting_level;
        switch (type_num) {
            case 1:
                t = OrangeTreeType.Hamlin;
                break;
            case 2:
                t = OrangeTreeType.Verna;
                break;
            case 3:
                t = OrangeTreeType.Salustiana;
                break;
            default:
                System.out.println("Something get wrong!");
                break;
        }
        TypeInfo = "Fruit: Orange\nType: " + t;
    }

    public void printOrangeTreeInfo() {
        printBasicInfo();
        System.out.println(TypeInfo);
    }
}
