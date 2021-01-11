import java.util.ArrayList;

public class Main {
    public static void main(String[] args)
    {
        int N = 12;
        GardenTree[] trees = new GardenTree[N];
        trees[0] = new AppleTree();
        trees[1] = new AppleTree();
        trees[2] = new AppleTree(25, 6, 2);
        trees[3] = new PearTree();
        trees[4] = new PearTree();
        trees[5] = new PearTree(52, 7, 3);
        trees[6] = new CherryTree();
        trees[7] = new CherryTree();
        trees[8] = new CherryTree(41, 4, 1);
        trees[9] = new OrangeTree();
        trees[10] = new OrangeTree();
        trees[11] = new OrangeTree(28, 9, 2);

        ArrayList<GardenTree> TooOldTrees = new ArrayList<>();
        ArrayList<GardenTree> NotFruitingTrees = new ArrayList<>();

        for (GardenTree tree : trees)
        {
            tree.printBasicInfo();
            if (tree.age > 50)
                TooOldTrees.add(tree);
            if (tree.fruiting_level < 5)
                NotFruitingTrees.add(tree);
        }

        // Слишком старые деревья
        System.out.println("\n▉▉▉▉▉▉▉▉▉▉ OLD TREES ▉▉▉▉▉▉▉▉▉▉");
        for (GardenTree tree : TooOldTrees)
            tree.printBasicInfo();
        if (TooOldTrees.size() == 0)
            System.out.println("There are no any old trees...");

        // Слишком не плодоносные деревья
        System.out.println("\n▉▉▉▉▉▉▉▉▉▉ NOT FRUITING TREES ▉▉▉▉▉▉▉▉▉▉");
        for (GardenTree tree : NotFruitingTrees)
            tree.printBasicInfo();
        if (NotFruitingTrees.size() == 0)
            System.out.println("There are no any not fruiting trees...");
    }
}
