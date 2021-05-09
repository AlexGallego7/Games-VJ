using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ObjetoActual : MonoBehaviour
{
    public GameObject objetoActual;
    public GameObject objetoParaCoger;
    public Transform handZone;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        if (objetoParaCoger != null && objetoParaCoger.GetComponent<CogerObjeto>().se_puede_coger == true && objetoActual ==null)
        {
            if (Input.GetKeyDown(KeyCode.E)){
                objetoActual = objetoParaCoger;
                objetoActual.GetComponent<CogerObjeto>().se_puede_coger = false;
                objetoActual.transform.SetParent(handZone);
                objetoActual.transform.position = handZone.position;
                objetoActual.GetComponent<Rigidbody>().useGravity = false;
                objetoActual.GetComponent<Rigidbody>().isKinematic = true;
            }
        }
        else if(objetoActual != null)
        {
            if (Input.GetKeyDown(KeyCode.E))
            {
                objetoActual.GetComponent<CogerObjeto>().se_puede_coger = true;
                objetoActual.transform.SetParent(null);
                objetoActual.GetComponent<Rigidbody>().useGravity = true;
                objetoActual.GetComponent<Rigidbody>().isKinematic = false;
                objetoActual = null;
            }
        }
    }
}
