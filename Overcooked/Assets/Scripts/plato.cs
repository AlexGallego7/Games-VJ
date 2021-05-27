using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class plato : MonoBehaviour
{


    public new string tag;
    public GameObject timer;
    private bool c = false, q = false;
    // Start is called before the first frame update
    void Start()
    {
        timer.SetActive(false);
        timer.GetComponent<Slider>().value = 12;
    }

    // Update is called once per frame
    void Update()
    {

        if (c)
        {
            if(timer.GetComponent<Slider>().value==12) timer.SetActive(true);
            timer.GetComponent<Slider>().value -= 1 * Time.deltaTime;
            
            if (timer.GetComponent<Slider>().value <= 0)
            {
                c = false;
                timer.GetComponent<Slider>().value = 12;
                timer.SetActive(false);
            }
        }
        else if (q)
        {
            
            if (timer.GetComponent<Slider>().value == 12){
                Debug.Log(timer.GetComponent<Slider>().value);
                timer.SetActive(true);
            }
            timer.GetComponent<Slider>().value -= 1 * Time.deltaTime;
            if (timer.GetComponent<Slider>().value <=0 )
            {
                q = false;
                timer.GetComponent<Slider>().value = 12;
            }
        }

    }

    public void cocinando()
    {
        c = true;
    }
    public void quemando()
    {
        q = true;
    }
}
