using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FrogLegs : Artefact
{
    public FrogLegs()
    {
        count = 1;
        Renewability = false;
    }


    void FrogLegsFunc(GameObject gameObject)
    {
        PlayerScript playerScript;

        playerScript = gameObject.GetComponent<PlayerScript>();

        playerScript.weakened = true;

    }

}