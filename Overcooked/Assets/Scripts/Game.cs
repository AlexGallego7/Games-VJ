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

    public GameObject rec_ham_sola, rec_ham_lechuga, rec_ham_queso, rec_ham_lechuga_tomate;

    // Start is called before the first frame update
    void Start()
    {
        numSlots = recetas.transform.childCount;
        slots = new GameObject[numSlots];
        for (int i=0; i<numSlots; i++)
        {
            slots[i] = recetas.transform.GetChild(i).gameObject;
            if(slots[i].GetComponent<slot>().receta == null)
            {
                slots[i].GetComponent<slot>().empty = true;
            }
        }
        recetas.SetActive(true);
    }

    // Update is called once per frame
    void Update()
    {

        StartCoroutine("esperar10secs");
    }

    IEnumerator esperar10secs()
    {
        yield return new WaitForSeconds(2);//cambiar a 10 en el futuro
        
        addReceta(rec_ham_lechuga_tomate, rec_ham_lechuga_tomate.GetComponent<receta>().id, rec_ham_lechuga_tomate.GetComponent<receta>().image);
    }

    public void addReceta(GameObject rec, int id, Sprite image)
    {
        for (int i = 0; i < numSlots; i++)
        {
            if (slots[i].GetComponent<slot>().empty)
            {
                rec.GetComponent<receta>().activado = true;
                slots[i].GetComponent<slot>().receta = rec;
                slots[i].GetComponent<slot>().id = id;
                slots[i].GetComponent<slot>().image = image;

                rec.transform.position = slots[i].transform.GetChild(0).transform.position;
                slots[i].GetComponent<slot>().updateSlot();
                rec.SetActive(true);

                slots[i].GetComponent<slot>().empty = false;

            }
            return;
        }
    }
}
