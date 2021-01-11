public class RunnerAnonym {
    public static void main(String[] args) {
        TypeQuest unique = new TypeQuest() {
// ��������� ����� #1

            public void addNewType() {
// ����� ���������� ������
                System.out.println(
                        "�������� ������ �� ��������� �������");
            }
        };// ����� ���������� ���������� ������

        unique.addNewType();


        TypeQuest standard = new TypeQuest(35);
        standard.addNewType();
    }
}