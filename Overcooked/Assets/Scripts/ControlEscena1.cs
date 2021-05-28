using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class ControlEscena1 : MonoBehaviour
{
    public NextLevelScreen nlScreen;

    private int numSlots;

    private int enableSlots;

    private bool enableRec;

    private GameObject[] slots;

    public GameObject recetas;

    public GameObject rec_ham_sola, rec_ham_lechuga, rec_ham_queso, rec_ham_lechuga_tomate;
    public GameObject rec_pasta_setas, rec_pasta_tomate;
    public GameObject rec_ensalada_tomate, rec_ensalada_pepino;

    private bool spawn_receta = true;

    public Slider s1, s2, s3, s4, s5;

    public Text tiempoTexto, puntostexto;
    private float tiempo;
    private int puntos;

    public bool se_puede_quemar = true;

    public static ControlEscena1 ins;
    public int scene;

    private void Awake()
    {
        if (ControlEscena1.ins == null)
        {
            ControlEscena1.ins = this;
            DontDestroyOnLoad(gameObject);

        }
        else
        {
            Destroy(gameObject);
        }
    }

    // Start is called before the first frame update
    void Start()
    {
        Time.timeScale = 1f;
        scene = SceneManager.GetActiveScene().buildIndex;
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
        
        //tiempo = 194.0f;
        
        tiempo = 2f;

        puntos = 0;
        puntostexto.text = puntos.ToString();

    }
    // Update is called once per frame
    void Update()
    {
        //godmode 
        if (Input.GetKeyDown(KeyCode.Q))
        {
            se_puede_quemar = !se_puede_quemar;
        }
        if (Input.GetKeyDown(KeyCode.Alpha1))
        {
            plato_correcto(slots[0].GetComponent<slot>().receta.GetComponent<receta>().tag);
        }
        else if (Input.GetKeyDown(KeyCode.Alpha2))
        {
            plato_correcto(slots[1].GetComponent<slot>().receta.GetComponent<receta>().tag);
        }
        else if (Input.GetKeyDown(KeyCode.Alpha3))
        {
            plato_correcto(slots[2].GetComponent<slot>().receta.GetComponent<receta>().tag);
        }
        else if (Input.GetKeyDown(KeyCode.Alpha4))
        {
            plato_correcto(slots[3].GetComponent<slot>().receta.GetComponent<receta>().tag);
        }
        else if (Input.GetKeyDown(KeyCode.Alpha5))
        {
            plato_correcto(slots[4].GetComponent<slot>().receta.GetComponent<receta>().tag);
        }
        if (Input.GetKeyDown(KeyCode.Y))
        {
            this.gameObject.GetComponent<ObjetoActual>().crear_plato(slots[0].GetComponent<slot>().receta.GetComponent<receta>().plato);
        }
        else if (Input.GetKeyDown(KeyCode.U))
        {
            this.gameObject.GetComponent<ObjetoActual>().crear_plato(slots[1].GetComponent<slot>().receta.GetComponent<receta>().plato);
        }
        else if (Input.GetKeyDown(KeyCode.I))
        {
            this.gameObject.GetComponent<ObjetoActual>().crear_plato(slots[2].GetComponent<slot>().receta.GetComponent<receta>().plato);
        }
        else if (Input.GetKeyDown(KeyCode.O))
        {
            this.gameObject.GetComponent<ObjetoActual>().crear_plato(slots[3].GetComponent<slot>().receta.GetComponent<receta>().plato);
        }
        else if (Input.GetKeyDown(KeyCode.P))
        {
            this.gameObject.GetComponent<ObjetoActual>().crear_plato(slots[4].GetComponent<slot>().receta.GetComponent<receta>().plato);
        }




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

        if (tiempo < 0)
            NextLevel();
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
        GameObject nueva_receta = null;
        if (scene == 1)
        {
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
        } else if (scene == 2)
        {
            switch (num)
            {
                case 0:
                    nueva_receta = rec_pasta_setas;
                    break;
                case 1:
                    nueva_receta = rec_pasta_tomate;
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
        } else if (scene == 3)
        {
            switch (num)
            {
                case 0:
                    nueva_receta = rec_ensalada_tomate;
                    break;
                case 1:
                    nueva_receta = rec_ensalada_pepino;
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
        } else if (scene == 4)
        {
            switch (num)
            {
                case 0:
                    nueva_receta = rec_ensalada_pepino;
                    break;
                case 1:
                    nueva_receta = rec_pasta_tomate;
                    break;
                case 2:
                    nueva_receta = rec_ham_lechuga_tomate;
                    break;
                case 3:
                    nueva_receta = rec_ham_queso;
                    break;
                default:
                    break;
            }
        } else if (scene == 5)
        {
            switch (num)
            {
                case 0:
                    nueva_receta = rec_ensalada_tomate;
                    break;
                case 1:
                    nueva_receta = rec_pasta_setas;
                    break;
                case 2:
                    nueva_receta = rec_pasta_tomate;
                    break;
                case 3:
                    nueva_receta = rec_ham_lechuga_tomate;
                    break;
                default:
                    break;
            }
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

    public void NextLevel()
    {
        nlScreen.Setup(puntos);
    }
}

