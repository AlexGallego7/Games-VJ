using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AnimController : MonoBehaviour
{
    private Animator anim;

    // Start is called before the first frame update
    void Start()
    {
        anim = GetComponent<Animator>();
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKey(KeyCode.W) || Input.GetKey(KeyCode.UpArrow))
            anim.SetTrigger("walk");
        
        if (Input.GetKey(KeyCode.A) || Input.GetKey(KeyCode.LeftArrow))
            anim.SetTrigger("walk");

        if (Input.GetKey(KeyCode.S) || Input.GetKey(KeyCode.DownArrow))
            anim.SetTrigger("walk");

        if (Input.GetKey(KeyCode.D) || Input.GetKey(KeyCode.RightArrow))
            anim.SetTrigger("walk");
    }
}
