using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ObjetoActual : MonoBehaviour
{
    public GameObject objetoActual;
    public GameObject objetoParaCoger;
    public Transform handZone;
    public Transform ObjCoger;

    public GameObject pan_cortado;


    // Start is called before the first frame update
    void Start()
    {
        
    }

    private GameObject detectar_objeto()
    {
        GameObject nuevo_objeto = null;
        if (objetoActual.tag == "pan")
        {
            nuevo_objeto = pan_cortado;
        }

        return nuevo_objeto;
    }

    // Update is called once per frame
    void Update()
    {
        //de pan a pan cortado
        if (objetoActual != null && objetoActual.GetComponent<CogerObjeto>().en_mesa_de_cortar)
        {
            if (Input.GetKeyDown(KeyCode.E))
            {
                GameObject nuevo_objeto = detectar_objeto();
                if(nuevo_objeto != null)
                {
                    Destroy(objetoActual);
                    nuevo_objeto = Instantiate(nuevo_objeto, new Vector3(0, 0, 0), Quaternion.identity);
                    objetoActual = nuevo_objeto;
                    objetoActual.GetComponent<CogerObjeto>().cogido = true;
                    objetoActual.GetComponent<CogerObjeto>().inicializado = true;
                    if (objetoActual.GetComponent<CogerObjeto>().mesa != null) objetoActual.GetComponent<CogerObjeto>().mesa.GetComponent<ObjetoMesa>().hay_objeto = false;
                    objetoActual.transform.SetParent(handZone);
                    objetoActual.transform.position = handZone.position;
                    objetoActual.GetComponent<Rigidbody>().useGravity = false;
                    objetoActual.GetComponent<Rigidbody>().isKinematic = true;
                }
            }
        }
        //coger objeto
        else if (objetoParaCoger != null && !objetoParaCoger.GetComponent<CogerObjeto>().cogido && objetoActual == null)
        {
            if (Input.GetKeyDown(KeyCode.E)) {
                objetoActual = objetoParaCoger;
                objetoActual.GetComponent<CogerObjeto>().cogido = true;
                objetoActual.GetComponent<CogerObjeto>().inicializado = true;
                if (objetoActual.GetComponent<CogerObjeto>().mesa != null) objetoActual.GetComponent<CogerObjeto>().mesa.GetComponent<ObjetoMesa>().hay_objeto = false;
                objetoActual.transform.SetParent(handZone);
                objetoActual.transform.position = handZone.position;
                objetoActual.GetComponent<Rigidbody>().useGravity = false;
                objetoActual.GetComponent<Rigidbody>().isKinematic = true;
                
            }
        }
        //soltar objeto en mesa
        else if (objetoActual != null && objetoActual.GetComponent<CogerObjeto>().mesa != null && objetoActual.GetComponent<CogerObjeto>().mesa.GetComponent<ObjetoMesa>().hay_objeto == false)
        {
            if (Input.GetKeyDown(KeyCode.E))
            {
                objetoActual.GetComponent<CogerObjeto>().cogido = false;
                objetoActual.GetComponent<CogerObjeto>().mesa.GetComponent<ObjetoMesa>().hay_objeto = true;
                objetoActual.transform.SetParent(ObjCoger);
                objetoActual.transform.position = objetoActual.GetComponent<CogerObjeto>().mesa.transform.position;
                objetoActual.transform.position -= new Vector3(0,0.5f,0);
                objetoActual.transform.rotation = new Quaternion(0,0,0,0);
                objetoActual.GetComponent<Rigidbody>().useGravity = false;
                objetoActual.GetComponent<Rigidbody>().isKinematic = true;
                objetoActual = null;
            }
        }
        //soltar objeto en el suelo
        else if (objetoActual != null && objetoActual.GetComponent<CogerObjeto>().mesa == null)
        {
            if (Input.GetKeyDown(KeyCode.E))
            {
                objetoActual.GetComponent<CogerObjeto>().cogido = false;
                objetoActual.transform.SetParent(ObjCoger);
                objetoActual.GetComponent<Rigidbody>().useGravity = true;
                objetoActual.GetComponent<Rigidbody>().isKinematic = false;
                objetoActual = null;
            }
        }

    }


}
