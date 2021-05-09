using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CogerObjeto : MonoBehaviour
{

    public bool cogido = false;

    
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
    }

    private void OnTriggerExit(Collider other)
    {
        if (other.tag == "handZone")
        {
            other.GetComponentInParent<ObjetoActual>().objetoParaCoger = null;
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
