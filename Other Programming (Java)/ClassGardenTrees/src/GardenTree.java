public class GardenTree {
    String name;                    // Имя дерева
    int age;                        // Возраст Дерева
    int tree_num;                   // Номер дерева
    int fruiting_level;             // Уровень плодоношения (от 1 до 10)

    static int current_num = 1;     // Текущий номер дерева

    String TypeInfo;                // Строка с информацией о типе

    public GardenTree() {
        tree_num = current_num;
        current_num++;
        name = "SomeTree_" + Integer.toString(tree_num);
        age = 1 + (int) (Math.random() * 70);
        fruiting_level = 1 + (int) (Math.random() * 10);
        TypeInfo = "Fruit: Some fruit\nType: Some type";
    }

    void printBasicInfo() {
        System.out.println("\n▉▉▉▉▉ TREE INFORMATION ▉▉▉▉▉");
        System.out.println("Name: " + name);
        System.out.println("Number: " + tree_num);
        System.out.println("Age: " + age);
        System.out.println("Fruiting level: " + fruiting_level + "/10");
        System.out.println(TypeInfo);
    }
}
