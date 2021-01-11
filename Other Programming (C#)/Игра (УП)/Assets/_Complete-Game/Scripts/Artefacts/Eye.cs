using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Eye : Artefact
{
    public Eye()
    {
        count = 1;
        Renewability = false;
    }

    void EyeFunc(GameObject gameObject)
    {
        PlayerScript playerScript;

        playerScript = gameObject.GetComponent<PlayerScript>();

        if (playerScript.dead == true)
        {

            playerScript.paralyzed = true;


        }

    }
}