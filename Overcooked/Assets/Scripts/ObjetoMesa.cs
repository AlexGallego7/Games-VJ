using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ObjetoMesa : MonoBehaviour
{
    public bool hay_objeto = false;
    public bool sin_objeto = false;
    public bool ya_cocinando = false;
    public bool llamas = false;

    public GameObject fuego_normal, en_llamas, steam;
    public GameObject objeto;
    private GameObject nuevo_objeto;
    public GameObject filete_cocinado;
    public GameObject filete_quemado;
    public GameObject pasta_cocinada;

    public Transform ObjCoger;

    // Start is called before the first frame update
    void Start()
    {
        fuego_normal.gameObject.SetActive(false);
        en_llamas.gameObject.SetActive(false);
        steam.gameObject.SetActive(false);
    }
    
    // Update is called once per frame
    void Update()
    {
        if (hay_objeto && sin_objeto)
        {
            if (!ya_cocinando)
            {
                StartCoroutine("esperar18secs");
                ya_cocinando = true;
            }
        }
        if(llamas) en_llamas.gameObject.SetActive(true);
        else en_llamas.gameObject.SetActive(false);
    }

    private GameObject detectar_objeto()
    {
        GameObject nuevo_objeto = null;
        switch (objeto.tag)
        {
            case "filete_cortado":
                nuevo_objeto = filete_cocinado;
                break;
            case "filete_cocinado":
                nuevo_objeto = filete_quemado;
                break;
            case "pasta":
                nuevo_objeto = pasta_cocinada;
                break;
            default:
                break;
        }

        return nuevo_objeto;
    }

    IEnumerator esperar18secs()
    {
        fuego_normal.gameObject.SetActive(true);
        steam.gameObject.SetActive(true);
        yield return new WaitForSeconds(2);//cambiar a 18 en el futuro

        nuevo_objeto = Instantiate(detectar_objeto(), new Vector3(0, 0, 0), Quaternion.identity);
        nuevo_objeto.GetComponent<CogerObjeto>().mesa = objeto.GetComponent<CogerObjeto>().mesa;
        nuevo_objeto.GetComponent<CogerObjeto>().cogido = false;
        nuevo_objeto.GetComponent<CogerObjeto>().mesa.GetComponent<ObjetoMesa>().hay_objeto = true;

        nuevo_objeto.transform.SetParent(ObjCoger);
        nuevo_objeto.transform.position = objeto.GetComponent<CogerObjeto>().mesa.transform.position;
        nuevo_objeto.transform.position += new Vector3(-1.65f, -0.2f, -2.0f);
        nuevo_objeto.transform.rotation = new Quaternion(0, 0, 0, 0);
        nuevo_objeto.GetComponent<Rigidbody>().useGravity = false;
        nuevo_objeto.GetComponent<Rigidbody>().isKinematic = true;
        Destroy(objeto);
        objeto = nuevo_objeto;
        StartCoroutine("esperar12secs");
    }



    IEnumerator esperar12secs()
    {
        yield return new WaitForSeconds(2);//cambiar a 12 en el futuro
        steam.gameObject.SetActive(false);
        fuego_normal.gameObject.SetActive(false);
        llamas  = true;
        if (hay_objeto)
        {
            nuevo_objeto = Instantiate(detectar_objeto(), new Vector3(0, 0, 0), Quaternion.identity);
            nuevo_objeto.GetComponent<CogerObjeto>().mesa = objeto.GetComponent<CogerObjeto>().mesa;
            nuevo_objeto.GetComponent<CogerObjeto>().cogido = false;
            nuevo_objeto.GetComponent<CogerObjeto>().mesa.GetComponent<ObjetoMesa>().hay_objeto = true;
            nuevo_objeto.transform.SetParent(ObjCoger);
            nuevo_objeto.transform.position = objeto.GetComponent<CogerObjeto>().mesa.transform.position;
            nuevo_objeto.transform.position += new Vector3(-1.65f, -0.2f, -2.0f);
            nuevo_objeto.transform.rotation = new Quaternion(0, 0, 0, 0);
            nuevo_objeto.GetComponent<Rigidbody>().useGravity = false;
            nuevo_objeto.GetComponent<Rigidbody>().isKinematic = true;
            Destroy(objeto);
            objeto = nuevo_objeto;
        }
        else
            steam.gameObject.SetActive(false);

    }



}
