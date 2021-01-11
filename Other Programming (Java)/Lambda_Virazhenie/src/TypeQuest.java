@FunctionalInterface
interface ITypeQuest {
    void addNewType();
}

public class TypeQuest implements ITypeQuest {
    private int id = 1;

    public TypeQuest() {
    }

    public TypeQuest(int id) {
        this.id = id;
    }

    @Override
    public void addNewType() {
        System.out.println("Добавлен вопрос на соответствие");
    }
}