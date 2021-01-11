using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerScript : MonoBehaviour
{
    public int id; // уникальный числовой идентификатор
    public string name; // имя персонажа
    // state
    public bool normal; // состояние нормальное
    public bool weakened; // ослаблен
    public bool sick; // болен
    public bool poison; // отравлен
    public bool paralyzed; // парализован
    public bool dead; // мертв
    public bool move; // возможность двигаться в текущий момент времени
    public bool speak; // возможность разговаривать в ткущий момент времени (*)
    // race
    public bool human; // человек
    public bool gnome; // гном
    public bool elf; // эльф
    public bool ork; // орк
    public bool goblin; // гоблин
    // about character
    public bool male; // мужчина
    public bool female; // женщина
    public int age; // возраст
    public int health; // текущее здоровье
    public int max_health; // максимальное здоровье (*)
    public int exp; // опыт
    public int mana; // мана
    public int max_mana; // максимальная мана (*)
    public bool godMode; // (*)

    private void Start()
    {
        normal = true;
    }

    void PlayersExp(GameObject enemy)
    {
        PlayerScript playerScript;
        playerScript = enemy.GetComponent<PlayerScript>();
        int difference = exp - playerScript.exp;

        if (difference > 0)
        {
            //TODO in Unity

        }
        else
        {

            //TODO in Unity

        }


    }
    public GameObject player;
    public const int Inv_AMOUNT = 15;
    List<Artefact> inventory = new List<Artefact>();
    List<MagicSay> spells = new List<MagicSay>();
    // Здесь будем хранить инвентарь
    public GameObject personaj, personaj_2, eleksir;
    // Update is called once per frame
    public static int index = 0;
    void Update()
    {
        if (health <= health * 0.1)
        {

            weakened = true;

        }
        else
        {
            weakened = false;
            normal = true;

        }

        if (health == 0)
        {

            dead = true;

        }
        // Когда подходим на какую-то позицию, то делаем следующее:
        if (personaj.transform.position == eleksir.transform.position) // Метод "Подобрать артефакт и пополнить мешок"
        {
            bool have = false;
      
            // Artifakt DW = eleksir.GetComponent<eleksir>().type;
            DeadWater DW = new DeadWater(); // В скрипте в Unity описать конкретный объект
            for (int i = 0; i < inventory.Count; i++)
            {
                if (inventory[0].GetType() == DW.GetType())
                {
                    have = true;
                    index = i;
                    break;
                }
            }
            if (!have) // Если еще нету такого артефакта, то добавить его
                inventory.Add(DW);
            else
            {
                if (inventory[index].count < Inv_AMOUNT)
                    inventory[index].count++; // Если же он есть, то просто повышаем счетчик его количества
            }
        }
        if (Input.GetKeyUp(KeyCode.T)) // Метод "Выбросить артефакт"
        {
            bool have = false;
            DeadWater DW = new DeadWater(); // В скрипте в Unity описать конкретный объект
            for (int i = 0; i < inventory.Count; i++)
            {
                if (inventory[0].GetType() == DW.GetType()) // Если мы нашли такой артефакт, то...
                {
                    have = true;
                    break;
                }
            }
            if (have)
            {
                inventory.Remove(DW); // Выбрасываем из инвентаря артефакт
            }
        }
        if (Input.GetKeyUp(KeyCode.H)) // Метод "Передать артефакт" (для дальнейших разработок)
        {
            bool have = false;
            DeadWater DW = new DeadWater(); // В скрипте в Unity описать конкретный объект
            for (int i = 0; i < inventory.Count; i++)
            {
                if (inventory[0].GetType() == DW.GetType()) // Если мы нашли такой артефакт, то...
                {
                    have = true;
                    break;
                }
            }
            if (have)
            {
                if (personaj.transform.position == personaj_2.transform.position) // Если персонажи имеют одну и ту же позицию, то можно передать артефакт
                {
                    inventory.Remove(DW); // Выбрасываем из инвентаря артефакт рядом другого персонажа
                }
            }
        }
        if (Input.GetKeyUp(KeyCode.Alpha1)) // Метод "Использовать артефакт"
        {
            bool have = false;
            DeadWater dw = new DeadWater();
            for (int i = 0; i < inventory.Count; i++)
            {
                if (inventory[0].GetType() == dw.GetType())
                {
                    have = true;
                    break;
                }
            }
            if (have)
                inventory[index].count--;
            if (inventory[index].count == 0)
            {
                inventory.RemoveAt(0);
            }
        }
        int find(ref bool have, HP hp)
        {
            int index = 0;
            for (int i = 0; i < spells.Count; i++)
            {
                if (spells[0].GetType() == hp.GetType())
                {
                    have = true;
                    index = i;
                    break;
                }
            }
            return index;
        }

        if (Input.GetKeyUp(KeyCode.Q)) // Метод "выучить заклинание"
        {
            bool have = false;
            int index = 0;
            HP hp = new HP();
            index = find(ref have, hp);
            if (!have)
                spells.Add(hp);
        }

        if (Input.GetKeyUp(KeyCode.W)) // Метод "произнести заклинание"
        {
            bool have = false;
            int index = 0;
            HP hp = new HP();
            index = find(ref have, hp);
            if (have)
                (spells[index] as HP).AddHP(player);
        }

        if (Input.GetKeyUp(KeyCode.E)) // Метод "забыть заклинание"
        {
            bool have = false;
            int index = 0;
            HP hp = new HP();
            index = find(ref have, hp);
            if (have)
                spells.RemoveAt(index);
        }
    }

}