using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Artefact : MonoBehaviour
{
    public int count;
    public int Mozhnost = 0;
    public bool Renewability;
    public Artefact ()
    {
        Mozhnost = -1; // Для обозначения нулевого артефакта
    }
}
