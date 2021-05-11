using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CogerObjeto : MonoBehaviour
{

    public bool cogido = false;
    public GameObject mesa;

    private bool inicializado = false;

    
    // Start is called before the first frame update
    void Start()
    {

        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    private void OnTriggerEnter(Collider other)
    {
        if(other.tag == "handZone")
        {
            other.GetComponentInParent<ObjetoActual>().objetoParaCoger= this.gameObject;
        }
        if (other.tag == "table")
        {
            mesa = other.gameObject;
            if (!inicializado)
            {
                inicializado = true;
                mesa.GetComponent<ObjetoMesa>().hay_objeto = true;
                this.gameObject.transform.position = mesa.transform.position;
                this.gameObject.transform.position -= new Vector3(0, 0.5f, 0);
                this.gameObject.transform.rotation = new Quaternion(0, 0, 0, 0);
                this.gameObject.GetComponent<Rigidbody>().useGravity = false;
                this.gameObject.GetComponent<Rigidbody>().isKinematic = true;
            }
        }
    }

    private void OnTriggerExit(Collider other)
    {
        if (other.tag == "handZone")
        {
            other.GetComponentInParent<ObjetoActual>().objetoParaCoger = null;
        }
        if (other.tag == "table")
        {
            mesa = null;
        }
    }

    /*
    private void OnTriggerStay(Collider other)
    {
        if (other.gameObject.CompareTag("Objeto"))
        {
            if(Input.GetKey("e") && objecto_actual==null){
                other.GetComponent<Rigidbody>().useGravity = false;
                other.GetComponent<Rigidbody>().isKinematic = true;
                other.transform.position = mano.transform.position;
                other.gameObject.transform.SetParent(mano.gameObject.transform);
                objecto_actual = other.gameObject;
            }
        }

    }
    */


}
