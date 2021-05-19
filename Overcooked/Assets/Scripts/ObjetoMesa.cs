using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ObjetoMesa : MonoBehaviour
{
    public bool hay_objeto = false;
    private bool ya_cocinado = false;

    public GameObject fire;
    public GameObject objeto;
    private GameObject nuevo_objeto;
    public GameObject hamburguesa_cocinada;

    public Transform ObjCoger;

    // Start is called before the first frame update
    void Start()
    {
        fire.gameObject.SetActive(false);
    }
    
    // Update is called once per frame
    void Update()
    {
        if (hay_objeto)
        {
            if(this.gameObject.tag == "sarten" && !ya_cocinado)
            {
                StartCoroutine("esperar2secs");
                ya_cocinado = true;
            }
        }
    }

    IEnumerator esperar2secs()
    {
        fire.gameObject.SetActive(true);
        yield return new WaitForSeconds (2);
        nuevo_objeto = Instantiate(hamburguesa_cocinada, new Vector3(0, 0, 0), Quaternion.identity);
        nuevo_objeto.GetComponent<CogerObjeto>().mesa = objeto.GetComponent<CogerObjeto>().mesa;
        nuevo_objeto.GetComponent<CogerObjeto>().cogido = false;
        nuevo_objeto.GetComponent<CogerObjeto>().mesa.GetComponent<ObjetoMesa>().hay_objeto = true;
        nuevo_objeto.transform.SetParent(ObjCoger);
        nuevo_objeto.transform.position = objeto.GetComponent<CogerObjeto>().mesa.transform.position;
        nuevo_objeto.transform.position += new Vector3(-1.65f, -0.3f, -2.0f);
        nuevo_objeto.transform.rotation = new Quaternion(0, 0, 0, 0);
        nuevo_objeto.GetComponent<Rigidbody>().useGravity = false;
        nuevo_objeto.GetComponent<Rigidbody>().isKinematic = true;
        Destroy(objeto);
        objeto = nuevo_objeto;
    }

}
