using System.Collections;
using System.Collections.Generic;
using UnityEngine;



public class MoveChef : MonoBehaviour
{
    public float speed;
    Animator animator;


    // Start is called before the first frame update
    void Start()
    {
        animator = GetComponent<Animator>();       
    }

    // Update is called once per frame
    void Update()
    {
        Vector3 movement = Vector3.zero;
        if (Input.GetKey(KeyCode.W) || Input.GetKey(KeyCode.UpArrow))
        {
            movement.z = 1;
            animator.SetTrigger("walkTrigger");

        }
        if (Input.GetKey(KeyCode.A) || Input.GetKey(KeyCode.LeftArrow))
        {
            movement.x = -1;
            animator.SetTrigger("walkTrigger");

        }
        if (Input.GetKey(KeyCode.S) || Input.GetKey(KeyCode.DownArrow))
        {
            movement.z = -1;
            animator.SetTrigger("walkTrigger");

        }
        if (Input.GetKey(KeyCode.D) || Input.GetKey(KeyCode.RightArrow))
        {
            movement.x = 1;
            animator.SetTrigger("walkTrigger");
        }
        GetComponent<CharacterController>().Move(movement*speed*Time.deltaTime);
        GetComponent<CharacterController>().transform.LookAt(GetComponent<CharacterController>().transform.position + movement);

    }

}
