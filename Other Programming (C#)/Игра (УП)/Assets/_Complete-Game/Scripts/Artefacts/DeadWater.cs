using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DeadWater : Artefact
{

    public DeadWater()
    {
        count = 1;
        Renewability = false;
    }

    void DeadWaterFunc()
    {
        PlayerScript playerScript;

        playerScript = GetComponent<PlayerScript>();

        playerScript.mana += 50;

    }
}