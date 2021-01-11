using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Alive : MagicSay
{
    public Alive()
    {
        minMana = 0;
    }

    void CureFriend(GameObject player)
    {
        PlayerScript playerScript;
        PlayerScript friendScript;

        friendScript = player.GetComponent<PlayerScript>();
        playerScript = GetComponent<PlayerScript>();
        playerScript.mana -= 150;

        friendScript.health = 1;
    }
}