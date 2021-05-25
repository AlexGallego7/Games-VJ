using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Collections;

public class ControlEscena1 : MonoBehaviour
{
    

    private int numSlots;

    private int enableSlots;

    private bool enableRec;

    private GameObject[] slots;

    public GameObject recetas;

    public GameObject rec_ham_sola, rec_ham_lechuga, rec_ham_queso, rec_ham_lechuga_tomate;

    private bool spawn_receta = true;

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
        
        if(spawn_receta) StartCoroutine("esperar10secs");
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
        GameObject nueva_receta = Instantiate(consigue_receta(Random.Range(0, 4)), new Vector3(0, 0, 0), Quaternion.identity);
        addReceta(nueva_receta, nueva_receta.GetComponent<receta>().id, nueva_receta.GetComponent<receta>().image);
        spawn_receta = true;
        
    }

    public void addReceta(GameObject rec, int id, Sprite image)
    {
        for (int i = 0; i < numSlots; i++)
        {
            Debug.Log(slots[i].GetComponent<slot>().empty);
            if (slots[i].GetComponent<slot>().empty)
            {
                rec.GetComponent<receta>().activado = true;
                slots[i].GetComponent<slot>().receta = rec;
                slots[i].GetComponent<slot>().id = id;
                slots[i].GetComponent<slot>().image = image;

                rec.transform.position = slots[i].transform.GetChild(0).transform.position;
                rec.transform.rotation = slots[i].transform.GetChild(0).transform.rotation;
                slots[i].GetComponent<slot>().updateSlot();
                rec.SetActive(true);

                slots[i].GetComponent<slot>().empty = false;
                break;
            }
        }
    }
}
