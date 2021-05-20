using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ObjetoActual : MonoBehaviour
{
    public GameObject objetoActual;
    public GameObject objetoParaCoger, nuevo_objeto;
    public Transform handZone;
    public Transform ObjCoger;


    public GameObject pan_cortado, filete_cortado, lechuga_cortada, seta_cortada, tomate_cortado, queso_cortado, pepino_cortado;
    public GameObject ham_sola;
    public GameObject tomate, seta, pan, pasta, lechuga, filete, queso, pepino;
    public GameObject olla_agua;
    public GameObject ham_pan_carne, ham_carne_lechuga, ham_carne_lechuga_queso, ham_completa;
    public GameObject mac_solos, mac_tomate, mac_tomate_carne, mac_tomate_carne_queso, mac_queso_seta, mac_queso;
    public GameObject ensalada_sola, ensalada_tomate, ensalada_tomate_pepino;

    private new string tag;

    // Start is called before the first frame update
    void Start()
    {
    }

    private GameObject detectar_objeto_para_cortar()
    {
        GameObject nuevo_objeto = null;
        switch (objetoActual.tag)
        {
            case "pan":
                nuevo_objeto = pan_cortado;
                break;
            case "filete":
                nuevo_objeto = filete_cortado;
                break;
            case "lechuga":
                nuevo_objeto = lechuga_cortada;
                break;
            case "seta":
                nuevo_objeto = seta_cortada;
                break;
            case "tomate":
                nuevo_objeto = tomate_cortado;
                break;
            case "queso":
                nuevo_objeto = queso_cortado;
                break;
            case "pepino":
                nuevo_objeto = pepino_cortado;
                break;
            default:
                break;
        }

        return nuevo_objeto;
    }
    private GameObject detectar_objeto_para_sarten()
    {
        GameObject nuevo_objeto = null;
        switch (objetoActual.tag)
        {
            case "filete_cortado":
                nuevo_objeto = filete_cortado;
                break;
            default:
                break;
        }

        return nuevo_objeto;
    }

    private GameObject detectar_objeto_para_combinar()
    {
        GameObject nuevo_objeto = null;
        switch (objetoActual.tag)
        {
            case "pan_cortado":
                nuevo_objeto = ham_sola;
                break;

            case "pasta":
                nuevo_objeto = mac_solos;
                break;

            case "filete_cocinado":
                if (objetoParaCoger.tag == "plato_pan_cortado")
                {
                    nuevo_objeto = ham_pan_carne;
                } else if(objetoParaCoger.tag == "mac_tomate")
                {
                    nuevo_objeto = mac_tomate_carne;
                }
                break;

            case "lechuga_cortada":
                if(objetoParaCoger.tag == "ham_carne")
                {
                    nuevo_objeto = ham_carne_lechuga;
                } else
                {
                    nuevo_objeto = ensalada_sola;
                }
                break;

            case "queso_cortado":
                if (objetoParaCoger.tag == "ham_carne_lechuga")
                {
                    nuevo_objeto = ham_carne_lechuga_queso;
                } else if(objetoParaCoger.tag == "mac_tomate_carne")
                {
                    nuevo_objeto = mac_tomate_carne_queso;
                } else if (objetoParaCoger.tag == "mac_solos")
                {
                    nuevo_objeto = mac_queso;
                }
                break;

            case "tomate_cortado":
                if (objetoParaCoger.tag == "ham_carne_lechuga_queso")
                {
                    nuevo_objeto = ham_completa;
                } else if(objetoParaCoger.tag == "mac_solos")
                {
                    nuevo_objeto = mac_tomate;
                } else if(objetoParaCoger.tag == "ensalada_sola")
                {
                    nuevo_objeto = ensalada_tomate;
                }
                break;

            case "pepino_cortado":
                if(objetoParaCoger.tag == "ensalada_tomate")
                {
                    nuevo_objeto = ensalada_tomate_pepino;
                }
                break;

            case "seta_cortada":
                if(objetoParaCoger.tag == "mac_queso")
                {
                    nuevo_objeto = mac_queso_seta;
                }
                break;
            default:
                break; 
        }
        Debug.Log(nuevo_objeto.tag);

        return nuevo_objeto;
    }

    public void cambiar_objeto_para_coger(GameObject obj)
    {
        if (objetoParaCoger == null || objetoParaCoger == objetoActual) objetoParaCoger = obj;
        else
        {
            var distA = Vector3.Distance(this.gameObject.transform.position, obj.transform.position);
            var distB = Vector3.Distance(this.gameObject.transform.position, objetoParaCoger.transform.position);
            if (distA < distB) objetoParaCoger = obj;
        }
    }

    // Update is called once per frame
    void Update()
    {

        //usar muebles
        if (objetoActual != null && objetoParaCoger != null && objetoParaCoger != objetoActual)
        {
            if (Input.GetKeyDown(KeyCode.E))
            {
                if (objetoParaCoger.tag == "tabla_cortar")
                {
                    GameObject nuevo_objeto = detectar_objeto_para_cortar();
                    if (nuevo_objeto != null)
                    {
                        Destroy(objetoActual);
                        nuevo_objeto = Instantiate(nuevo_objeto, new Vector3(0, 0, 0), Quaternion.identity);
                        objetoActual = nuevo_objeto;
                        objetoActual.GetComponent<CogerObjeto>().cogido = true;
                        objetoActual.GetComponent<CogerObjeto>().inicializado = true;
                        if (objetoActual.GetComponent<CogerObjeto>().mesa != null)
                            objetoActual.GetComponent<CogerObjeto>().mesa.GetComponent<ObjetoMesa>().hay_objeto = false;

                        objetoActual.transform.SetParent(handZone);
                        objetoActual.transform.position = handZone.position;
                        objetoActual.GetComponent<Rigidbody>().useGravity = false;
                        objetoActual.GetComponent<Rigidbody>().isKinematic = true;
                    }
                }
                else if (objetoParaCoger.tag == "sarten")
                {
                    Debug.Log("debug");
                    GameObject nuevo_objeto = detectar_objeto_para_sarten();
                    if (nuevo_objeto != null)
                    {
                        GameObject mesa = objetoParaCoger.gameObject;
                        Destroy(objetoActual);
                        nuevo_objeto = Instantiate(nuevo_objeto, new Vector3(0, 0, 0), Quaternion.identity);
                        objetoActual = nuevo_objeto;
                        objetoActual.GetComponent<CogerObjeto>().mesa = mesa;
                        objetoActual.GetComponent<CogerObjeto>().cogido = false;
                        objetoActual.GetComponent<CogerObjeto>().mesa.GetComponent<ObjetoMesa>().hay_objeto = true;
                        objetoActual.GetComponent<CogerObjeto>().mesa.GetComponent<ObjetoMesa>().objeto = objetoActual;
                        objetoActual.transform.SetParent(ObjCoger);
                        objetoActual.transform.position = objetoActual.GetComponent<CogerObjeto>().mesa.transform.position;
                        objetoActual.transform.position += new Vector3(-1.65f, -0.3f, -2.0f);
                        objetoActual.transform.rotation = new Quaternion(0, 0, 0, 0);
                        objetoActual.GetComponent<Rigidbody>().useGravity = false;
                        objetoActual.GetComponent<Rigidbody>().isKinematic = true;
                        objetoActual = null;
                    }
                }
                else if (objetoParaCoger.tag == "basura")
                {
                    Destroy(objetoActual);
                }
                //todas las combinaciones
                else if (objetoParaCoger.tag == "plato")
                {
                    nuevo_objeto = detectar_objeto_para_combinar();
                    if (nuevo_objeto != null)
                    {
                        crear_combinacion();
                    }
                }
                else if (objetoParaCoger.tag == "plato_pan_cortado" && objetoActual.tag =="filete_cocinado")
                {
                    nuevo_objeto = detectar_objeto_para_combinar();
                    crear_combinacion();
                }
                else if (objetoParaCoger.tag == "ham_carne" && objetoActual.tag == "lechuga_cortada")
                {
                    nuevo_objeto = detectar_objeto_para_combinar();
                    crear_combinacion();
                }
                else if (objetoParaCoger.tag == "ham_carne_lechuga" && objetoActual.tag == "queso_cortado")
                {
                    nuevo_objeto = detectar_objeto_para_combinar();
                    crear_combinacion();
                }
                else if (objetoParaCoger.tag == "ham_carne_lechuga_queso" && objetoActual.tag == "tomate_cortado")
                {
                    nuevo_objeto = detectar_objeto_para_combinar();
                    crear_combinacion();
                }
                else if (objetoParaCoger.tag == "mac_solos" && objetoActual.tag == "tomate_cortado")
                {
                    nuevo_objeto = detectar_objeto_para_combinar();
                    crear_combinacion();
                }
                else if (objetoParaCoger.tag == "mac_solos" && objetoActual.tag == "queso_cortado")
                {
                    nuevo_objeto = detectar_objeto_para_combinar();
                    crear_combinacion();
                }
                else if (objetoParaCoger.tag == "mac_queso" && objetoActual.tag == "seta_cortada")
                {
                    nuevo_objeto = detectar_objeto_para_combinar();
                    crear_combinacion();
                }
                else if (objetoParaCoger.tag == "mac_tomate" && objetoActual.tag == "filete_cocinado")
                {
                    nuevo_objeto = detectar_objeto_para_combinar();
                    crear_combinacion();
                }
                else if (objetoParaCoger.tag == "mac_tomate_carne" && objetoActual.tag == "queso_cortado")
                {
                    nuevo_objeto = detectar_objeto_para_combinar();
                    crear_combinacion();
                }
                else if (objetoParaCoger.tag == "ensalada_sola" && objetoActual.tag == "tomate_cortado")
                {
                    nuevo_objeto = detectar_objeto_para_combinar();
                    crear_combinacion();
                }
                else if (objetoParaCoger.tag == "ensalada_tomate" && objetoActual.tag == "pepino_cortado")
                {
                    nuevo_objeto = detectar_objeto_para_combinar();
                    crear_combinacion();
                }
            }
        }
        //coger objeto
        else if (objetoParaCoger != null && !objetoParaCoger.GetComponent<CogerObjeto>().cogido && objetoActual == null)
        {
            if (Input.GetKeyDown(KeyCode.E))
            {
                objetoActual = objetoParaCoger;
                objetoActual.GetComponent<CogerObjeto>().cogido = true;
                objetoActual.GetComponent<CogerObjeto>().inicializado = true;
                if (objetoActual.GetComponent<CogerObjeto>().mesa != null)
                {
                    objetoActual.GetComponent<CogerObjeto>().mesa.GetComponent<ObjetoMesa>().hay_objeto = false;
                    objetoActual.GetComponent<CogerObjeto>().mesa.GetComponent<ObjetoMesa>().sin_objeto = true;
                    objetoActual.GetComponent<CogerObjeto>().mesa.GetComponent<ObjetoMesa>().ya_cocinado = false;

                    objetoActual.GetComponent<CogerObjeto>().mesa.GetComponent<ObjetoMesa>().fire.gameObject.SetActive(false);
                    objetoActual.GetComponent<CogerObjeto>().mesa = null;

                }
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
                objetoActual.transform.position -= new Vector3(0, 0.5f, 0);
                objetoActual.transform.rotation = new Quaternion(0, 0, 0, 0);
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
        //coger objeto box
        else if (objetoActual == null && objetoParaCoger != null)
        {
            if (Input.GetKeyDown(KeyCode.E))
            {
                GameObject nuevo_objeto = null;
                switch (objetoParaCoger.tag)
                {
                    case "box_tomate":
                        nuevo_objeto = Instantiate(tomate, new Vector3(0, 0, 0), Quaternion.identity);
                        objetoActual = nuevo_objeto;
                        objetoActual.GetComponent<CogerObjeto>().cogido = true;
                        objetoActual.GetComponent<CogerObjeto>().inicializado = true;
                        objetoActual.transform.SetParent(handZone);
                        objetoActual.transform.position = handZone.position;
                        objetoActual.GetComponent<Rigidbody>().useGravity = false;
                        objetoActual.GetComponent<Rigidbody>().isKinematic = true;
                        break;
                    case "box_seta":
                        nuevo_objeto = Instantiate(seta, new Vector3(0, 0, 0), Quaternion.identity);
                        objetoActual = nuevo_objeto;
                        objetoActual.GetComponent<CogerObjeto>().cogido = true;
                        objetoActual.GetComponent<CogerObjeto>().inicializado = true;
                        objetoActual.transform.SetParent(handZone);
                        objetoActual.transform.position = handZone.position;
                        objetoActual.GetComponent<Rigidbody>().useGravity = false;
                        objetoActual.GetComponent<Rigidbody>().isKinematic = true;
                        break;
                    case "box_filete":
                        nuevo_objeto = Instantiate(filete, new Vector3(0, 0, 0), Quaternion.identity);
                        objetoActual = nuevo_objeto;
                        objetoActual.GetComponent<CogerObjeto>().cogido = true;
                        objetoActual.GetComponent<CogerObjeto>().inicializado = true;
                        objetoActual.transform.SetParent(handZone);
                        objetoActual.transform.position = handZone.position;
                        objetoActual.GetComponent<Rigidbody>().useGravity = false;
                        objetoActual.GetComponent<Rigidbody>().isKinematic = true;
                        break;
                    case "box_lechuga":
                        nuevo_objeto = Instantiate(lechuga, new Vector3(0, 0, 0), Quaternion.identity);
                        objetoActual = nuevo_objeto;
                        objetoActual.GetComponent<CogerObjeto>().cogido = true;
                        objetoActual.GetComponent<CogerObjeto>().inicializado = true;
                        objetoActual.transform.SetParent(handZone);
                        objetoActual.transform.position = handZone.position;
                        objetoActual.GetComponent<Rigidbody>().useGravity = false;
                        objetoActual.GetComponent<Rigidbody>().isKinematic = true;
                        break;
                    case "box_pan":
                        nuevo_objeto = Instantiate(pan, new Vector3(0, 0, 0), Quaternion.identity);
                        objetoActual = nuevo_objeto;
                        objetoActual.GetComponent<CogerObjeto>().cogido = true;
                        objetoActual.GetComponent<CogerObjeto>().inicializado = true;
                        objetoActual.transform.SetParent(handZone);
                        objetoActual.transform.position = handZone.position;
                        objetoActual.GetComponent<Rigidbody>().useGravity = false;
                        objetoActual.GetComponent<Rigidbody>().isKinematic = true;
                        break;
                    case "box_queso":
                        nuevo_objeto = Instantiate(queso, new Vector3(0, 0, 0), Quaternion.identity);
                        objetoActual = nuevo_objeto;
                        objetoActual.GetComponent<CogerObjeto>().cogido = true;
                        objetoActual.GetComponent<CogerObjeto>().inicializado = true;
                        objetoActual.transform.SetParent(handZone);
                        objetoActual.transform.position = handZone.position;
                        objetoActual.GetComponent<Rigidbody>().useGravity = false;
                        objetoActual.GetComponent<Rigidbody>().isKinematic = true;
                        break;
                    case "box_pasta":
                        nuevo_objeto = Instantiate(pasta, new Vector3(0, 0, 0), Quaternion.identity);
                        objetoActual = nuevo_objeto;
                        objetoActual.GetComponent<CogerObjeto>().cogido = true;
                        objetoActual.GetComponent<CogerObjeto>().inicializado = true;
                        objetoActual.transform.SetParent(handZone);
                        objetoActual.transform.position = handZone.position;
                        objetoActual.GetComponent<Rigidbody>().useGravity = false;
                        objetoActual.GetComponent<Rigidbody>().isKinematic = true;
                        break;
                    case "box_pepino":
                        nuevo_objeto = Instantiate(pepino, new Vector3(0, 0, 0), Quaternion.identity);
                        objetoActual = nuevo_objeto;
                        objetoActual.GetComponent<CogerObjeto>().cogido = true;
                        objetoActual.GetComponent<CogerObjeto>().inicializado = true;
                        objetoActual.transform.SetParent(handZone);
                        objetoActual.transform.position = handZone.position;
                        objetoActual.GetComponent<Rigidbody>().useGravity = false;
                        objetoActual.GetComponent<Rigidbody>().isKinematic = true;
                        break;
                    default:
                        break;
                }

            }

        }
    }

    private void crear_combinacion()
    {
        GameObject mesa = objetoParaCoger.GetComponent<CogerObjeto>().mesa.gameObject;
        Destroy(objetoActual);
        Destroy(objetoParaCoger);
        objetoParaCoger = null;
        nuevo_objeto = Instantiate(nuevo_objeto, new Vector3(0, 0, 0), Quaternion.identity);
        objetoActual = nuevo_objeto;
        objetoActual.GetComponent<CogerObjeto>().mesa = mesa;
        objetoActual.GetComponent<CogerObjeto>().cogido = false;
        objetoActual.GetComponent<CogerObjeto>().mesa.GetComponent<ObjetoMesa>().hay_objeto = true;
        objetoActual.transform.SetParent(ObjCoger);
        objetoActual.transform.position = objetoActual.GetComponent<CogerObjeto>().mesa.transform.position;
        objetoActual.transform.position -= new Vector3(0, 0.5f, 0);
        objetoActual.transform.rotation = new Quaternion(0, 0, 0, 0);
        objetoActual.GetComponent<Rigidbody>().useGravity = false;
        objetoActual.GetComponent<Rigidbody>().isKinematic = true;
        objetoActual = null;
    }
}