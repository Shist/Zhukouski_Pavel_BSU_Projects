using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Paralized : MagicSay
{
    public Paralized()
    {
        minMana = 0;
    }

    void CureFriend(GameObject player)
    {
        PlayerScript playerScript;
        PlayerScript friendScript;

        friendScript = player.GetComponent<PlayerScript>();
        playerScript = GetComponent<PlayerScript>();
        playerScript.mana -= 85; // Предусмотреть, не выйдет ли мана меньше, чем за ноль...

        friendScript.normal = true;
        friendScript.health = 1;
    }
}