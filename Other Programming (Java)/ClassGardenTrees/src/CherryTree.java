public class CherryTree extends GardenTree {

    enum CherryTreeType{
        chocolate_maker,
        miracle_cherry,
        Kharitonovskaya
    }

    CherryTreeType t;

    CherryTree()
    {
        name = "SomeCherryTree_" + Integer.toString(tree_num);
        int random_num = 1 + (int) (Math.random() * 3);
        switch (random_num) {
            case 1:
                t = CherryTreeType.chocolate_maker;
                break;
            case 2:
                t = CherryTreeType.miracle_cherry;
                break;
            case 3:
                t = CherryTreeType.Kharitonovskaya;
                break;
        }
        TypeInfo = "Fruit: Cherry\nType: " + t;
    }

    CherryTree(int _age, int _fruiting_level, int type_num)
    {
        age = _age;
        fruiting_level = _fruiting_level;
        switch (type_num) {
            case 1:
                t = CherryTreeType.chocolate_maker;
                break;
            case 2:
                t = CherryTreeType.miracle_cherry;
                break;
            case 3:
                t = CherryTreeType.Kharitonovskaya;
                break;
            default:
                System.out.println("Something get wrong!");
                break;
        }
        TypeInfo = "Fruit: Cherry\nType: " + t;
    }

    void printCherryTreeInfo() {
        printBasicInfo();
        System.out.println(TypeInfo);
    }
}
