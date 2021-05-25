using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ControlEscena1 : MonoBehaviour
{
    

    private int numSlots;

    private int enableSlots;

    private bool enableRec;

    private GameObject[] slots;

    public GameObject recetas;

    public GameObject rec_ham_sola, rec_ham_lechuga, rec_ham_queso, rec_ham_lechuga_tomate;

    private bool spawn_receta = true;

    public Slider s1, s2, s3, s4, s5;


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
        for (int i = 0; i < numSlots; i++)
        {
            if (!slots[i].GetComponent<slot>().empty)
            {

                if (i == 0) s1.value -= 1*Time.deltaTime;
                else if (i == 1) s2.value -= 1 * Time.deltaTime;
                else if (i == 2) s3.value -= 1 * Time.deltaTime;
                else if (i == 3) s4.value -= 1 * Time.deltaTime;
                else if (i == 4) s5.value -= 1 * Time.deltaTime;
            }
            else break;
        }
        if (spawn_receta) StartCoroutine("esperar10secs");
    }

    public GameObject consigue_receta(int num)
    {
        GameObject nueva_receta=null;
        switch (num)
        {
            case 0:
                nueva_receta = rec_ham_sola;
                break;
            case 1:
                nueva_receta = rec_ham_lechuga;
            break;
            case 2:
                nueva_receta = rec_ham_queso;
            break;
            case 3:
                nueva_receta = rec_ham_lechuga_tomate;
            break;
            default:
                break;
        }
        return nueva_receta;
    }

    IEnumerator esperar10secs()
    {
        spawn_receta = false;
        yield return new WaitForSeconds(2);//cambiar a 10 en el futuro
        addReceta();
    }

    public void addReceta()
    {
        for (int i = 0; i < numSlots; i++)
        {
           
            if (slots[i].GetComponent<slot>().empty)
            {
                GameObject rec = Instantiate(consigue_receta(Random.Range(0, 4)), new Vector3(0, 0, 0), Quaternion.identity);
                spawn_receta = true;
                rec.GetComponent<receta>().activado = true;
                slots[i].GetComponent<slot>().receta = rec;
                slots[i].GetComponent<slot>().id = rec.GetComponent<receta>().id;
                slots[i].GetComponent<slot>().image = rec.GetComponent<receta>().image;

                rec.transform.position = slots[i].transform.GetChild(0).transform.position;
                rec.transform.rotation = slots[i].transform.GetChild(0).transform.rotation;
                slots[i].GetComponent<slot>().updateSlot();
                rec.SetActive(true);
                if (i == 0) s1.value = 100;
                else if (i == 1) s2.value = 100;
                else if (i == 2) s3.value = 100;
                else if (i == 3) s4.value = 100;
                else if (i == 4) s5.value = 100;

                slots[i].GetComponent<slot>().empty = false;
                break;
            }
        }
    }
}
