using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class HP : MagicSay
{
    public HP()
    {
        minMana = 0; 
    }

    public void AddHP(GameObject player)
    {
        PlayerScript playerScript;

        playerScript = player.GetComponent<PlayerScript>();

        playerScript.mana -= 2;

        playerScript.health += 30;
    }
}