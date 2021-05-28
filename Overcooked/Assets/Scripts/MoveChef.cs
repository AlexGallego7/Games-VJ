using System.Collections;
using System.Collections.Generic;
using UnityEngine;



public class MoveChef : MonoBehaviour
{

    private Vector3 posDef;
    private Animator anim;


    public float speed;
    private Vector3 moveDirection;
    private Quaternion pos;

    private CharacterController controller;



    // Start is called before the first frame update
    void Start()
    {
        controller = GetComponent<CharacterController>();
        posDef = this.gameObject.transform.position;

        anim = this.GetComponent<Animator>();
    }

    // Update is called once per frame
    void Update()
    {
        Move();
        if (this.gameObject.transform.position.y != posDef.y)
        {
            //FindObjectOfType<AudioManager>().Play("PlayerWalking");

            float dif = this.gameObject.transform.position.y - posDef.y;
            GetComponent<CharacterController>().Move(new Vector3(0, -dif, 0));
        }
        else
        {
            FindObjectOfType<AudioManager>().Stop("PlayerWalking");
        }

    }
    public void cortar_on()
    {
        anim.SetBool("cortar", true);
    }

    public void cortar_off()
    {
        anim.SetBool("cortar", false);
    }


    private void Move()
    {
        if (!anim.GetBool("cortar"))
        {
            float x, y;
            x = Input.GetAxis("Horizontal");
            y = Input.GetAxis("Vertical");
            Vector3 movement = Vector3.zero;
            if (Input.GetKey(KeyCode.W) || Input.GetKey(KeyCode.UpArrow))
            {
                movement.z = 1;
                if (!FindObjectOfType<AudioManager>().isPlaying("PlayerWalking"))
                    FindObjectOfType<AudioManager>().Play("PlayerWalking");
            }
            if (Input.GetKey(KeyCode.A) || Input.GetKey(KeyCode.LeftArrow))
            {
                movement.x = -1;
                if (!FindObjectOfType<AudioManager>().isPlaying("PlayerWalking"))
                    FindObjectOfType<AudioManager>().Play("PlayerWalking");
            }
            if (Input.GetKey(KeyCode.S) || Input.GetKey(KeyCode.DownArrow))
            {
                movement.z = -1;
                if (!FindObjectOfType<AudioManager>().isPlaying("PlayerWalking"))
                    FindObjectOfType<AudioManager>().Play("PlayerWalking");
            }
            if (Input.GetKey(KeyCode.D) || Input.GetKey(KeyCode.RightArrow))
            {
                movement.x = 1;
                if (!FindObjectOfType<AudioManager>().isPlaying("PlayerWalking"))
                    FindObjectOfType<AudioManager>().Play("PlayerWalking");
            }
            if (movement.x > 0)
            {
                anim.SetFloat("derecha", movement.x);
                anim.SetFloat("izquierda", 0);
            }
            else
            {
                anim.SetFloat("derecha", 0);
                anim.SetFloat("izquierda", -movement.x);
            }
            if (movement.z > 0)
            {
                anim.SetFloat("arriba", movement.z);
                anim.SetFloat("abajo", 0);
            }
            else
            {
                anim.SetFloat("arriba", 0);
                anim.SetFloat("abajo", -movement.z);
            }


            GetComponent<CharacterController>().Move(movement * speed * Time.deltaTime);
            GetComponent<CharacterController>().transform.LookAt(GetComponent<CharacterController>().transform.position + movement);
            pos = this.transform.rotation;
        }
        else this.transform.rotation = pos;

    }

}