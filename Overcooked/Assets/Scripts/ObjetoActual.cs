using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ObjetoActual : MonoBehaviour
{
    public GameObject objetoActual;
    public GameObject objetoParaCoger;
    public Transform handZone;
    public Transform ObjCoger;


    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        if (objetoParaCoger != null && !objetoParaCoger.GetComponent<CogerObjeto>().cogido && objetoActual == null && objetoParaCoger.GetComponent<CogerObjeto>().mesa == null)
        {
            if (Input.GetKeyDown(KeyCode.E)){
                objetoActual = objetoParaCoger;
                objetoActual.GetComponent<CogerObjeto>().cogido = true;
                objetoActual.transform.SetParent(handZone);
                objetoActual.transform.position = handZone.position;
                objetoActual.GetComponent<Rigidbody>().useGravity = false;
                objetoActual.GetComponent<Rigidbody>().isKinematic = true;
            }
        }
        else if (objetoParaCoger != null && !objetoParaCoger.GetComponent<CogerObjeto>().cogido && objetoActual == null && objetoParaCoger.GetComponent<CogerObjeto>().mesa != null)
        {
            if (Input.GetKeyDown(KeyCode.E))
            {
                objetoActual = objetoParaCoger;
                objetoActual.GetComponent<CogerObjeto>().cogido = true;
                objetoActual.transform.SetParent(handZone);
                objetoActual.transform.position = handZone.position;
                objetoActual.GetComponent<Rigidbody>().useGravity = false;
                objetoActual.GetComponent<Rigidbody>().isKinematic = true;
                objetoParaCoger.GetComponent<CogerObjeto>().mesa = null;
            }
        }
        else if (objetoActual != null && objetoActual.GetComponent<CogerObjeto>().mesa != null)
        {
            if (Input.GetKeyDown(KeyCode.E))
            {
                objetoActual.GetComponent<CogerObjeto>().cogido = false;
                objetoActual.transform.SetParent(ObjCoger);
                //calcular_posicion_mesa();
                objetoActual.transform.position = objetoActual.GetComponent<CogerObjeto>().mesa.transform.position;
                objetoActual.transform.position -= new Vector3(0,0.5f,0);
                objetoActual.transform.rotation = new Quaternion(0,0,0,0);
                objetoActual.GetComponent<Rigidbody>().useGravity = false;
                objetoActual.GetComponent<Rigidbody>().isKinematic = true;
                objetoActual = null;
            }
        }
        else if (objetoActual != null)
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
