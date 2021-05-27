using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

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

    public Text tiempoTexto, puntostexto;
    private float tiempo;
    private int puntos;


    // Start is called before the first frame update
    void Start()
    {
        numSlots = recetas.transform.childCount;
        slots = new GameObject[numSlots];
        for (int i = 0; i < numSlots; i++)
        {
            slots[i] = recetas.transform.GetChild(i).gameObject;
            if (slots[i].GetComponent<slot>().receta == null)
            {
                slots[i].GetComponent<slot>().empty = true;
            }
        }
        recetas.SetActive(true);
        tiempo = 194.0f;
        puntos = 0;
        puntostexto.text = puntos.ToString();

    }
    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.F))
        {
            SceneManager.LoadScene("CredsScene");
            FindObjectOfType<AudioManager>().Play("Creds");
            FindObjectOfType<AudioManager>().Stop("Restaurant");

        }


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
        spawn_receta = false;
        tiempo = tiempo - 1* Time.deltaTime;
        string minutes = ((int)tiempo / 60).ToString();
        string seconds = (tiempo % 60).ToString("f0");
        if ((tiempo % 60) < 10 && seconds != "10") tiempoTexto.text = minutes + ":0" + seconds;
        else tiempoTexto.text = minutes + ":" + seconds;
        puntostexto.text = puntos.ToString();
    }

    private void rest_temporizadores(int i)
    {
            if (i == 0)
            {
                s1.value = s2.value;
                s2.value = s3.value;
                s3.value = s4.value;
                s4.value = s5.value;
                s5.value = 0;
            }
            else if (i == 1)
            {
                s2.value = s3.value;
                s3.value = s4.value;
                s4.value = s5.value;
                s5.value = 0;
            }
            else if (i  == 2)
            {
                s3.value = s4.value;
                s4.value = s5.value;
                s5.value = 0;
            }
            else if (i == 3)
            {
                s4.value = s5.value;
                s5.value = 0;
            }
            else if (i == 4)
            {
                s5.value = 0;
            }

    }

    public bool plato_correcto(string tag)
    {
        for(int i=0; i<numSlots; i++)
        {
            if (slots[i].GetComponent<slot>().receta.GetComponent<receta>().tag == tag)
            {
                puntos += 5;
                rest_temporizadores(i);
                GameObject rec = slots[i].GetComponent<slot>().receta;
                Destroy(rec);
                slots[i].GetComponent<slot>().empty = true;
                for (int j = i; j < numSlots-1; j++)
                {
                    if (!slots[j + 1].GetComponent<slot>().empty)
                    {
                        rec = slots[j+1].GetComponent<slot>().receta;
                        rec.transform.position = slots[j].transform.GetChild(0).transform.position;
                        rec.transform.rotation = slots[j].transform.GetChild(0).transform.rotation;
                        slots[j+1].GetComponent<slot>().empty = true;
                        slots[j].GetComponent<slot>().empty = false;
                        slots[j].GetComponent<slot>().receta = rec;
                        slots[j + 1].GetComponent<slot>().receta = null;
                        
                    }
                    else break;
                }
                return true;
            }
            if (slots[i].GetComponent<slot>().empty) break;
        }
        return false;
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
        yield return new WaitForSeconds(2);//cambiar a 10 en el futuro
        addReceta();
        StartCoroutine("esperar10secs");
    }

    public void addReceta()
    {
        for (int i = 0; i < numSlots; i++)
        {
           
            if (slots[i].GetComponent<slot>().empty)
            {
                GameObject rec = Instantiate(consigue_receta(Random.Range(0, 4)), new Vector3(0, 0, 0), Quaternion.identity);
                slots[i].GetComponent<slot>().receta = rec;

                rec.transform.position = slots[i].transform.GetChild(0).transform.position;
                rec.transform.rotation = slots[i].transform.GetChild(0).transform.rotation;

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

