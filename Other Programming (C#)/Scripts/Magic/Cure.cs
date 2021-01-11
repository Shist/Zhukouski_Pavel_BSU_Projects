using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Cure : MagicSay
{
    public Cure()
    {
        minMana = 0;
    }

    void CureFriend(GameObject player)
    {
        PlayerScript playerScript;
        PlayerScript friendScript;

        friendScript = player.GetComponent<PlayerScript>();
        playerScript = GetComponent<PlayerScript>();
        playerScript.mana -= 20;

        friendScript.normal = true;
    }
}