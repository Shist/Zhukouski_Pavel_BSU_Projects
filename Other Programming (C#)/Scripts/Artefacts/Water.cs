using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Water : Artefact
{

    public Water()
    {
        count = 1;
        Renewability = false;
    }

    void WaterArt()
    {

        PlayerScript playerScript;

        playerScript = GetComponent<PlayerScript>();

        playerScript.mana += 50;

    }
}