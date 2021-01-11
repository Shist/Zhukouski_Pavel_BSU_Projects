using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bolt : Artefact
{
    public Bolt()
    {
        count = 1;
        Renewability = true;
    }

    void BoltFunc(GameObject gameObject)
    {
        PlayerScript playerScript;

        playerScript = gameObject.GetComponent<PlayerScript>();

        playerScript.health -= 30;

        if (playerScript.health < 0)
        {
            playerScript.health = 0;
        }

        if (Mozhnost == 0)
        {
            Renewability = false;
        }
    }
}