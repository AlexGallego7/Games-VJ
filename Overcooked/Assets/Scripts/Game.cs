using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Game : MonoBehaviour
{


    private int numSlots;

    private int enableSlots;

    private bool enableRec;

    private GameObject[] slots;

    public GameObject recetas;

    // Start is called before the first frame update
    void Start()
    {
        numSlots = recetas.transform.childCount;
        slots = new GameObject[numSlots];
        for (int i=0; i<numSlots; i++)
        {
            slots[i] = recetas.transform.GetChild(i).gameObject;
        }
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.I))
        {
            enableRec = !enableRec;
        }
        if (enableRec) recetas.SetActive(true);
        else recetas.SetActive(false);
    }
}
