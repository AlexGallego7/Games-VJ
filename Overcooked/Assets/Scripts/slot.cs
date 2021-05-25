using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class slot : MonoBehaviour
{

    public GameObject receta;
    public int id;
    public Sprite image;

    public bool empty;
    public Transform imPanel;

    public void updateSlot()
    {
        this.GetComponent<Image>().sprite = image;
    }

    // Start is called before the first frame update
    void Start()
    {
        imPanel = transform.GetChild(0);
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
