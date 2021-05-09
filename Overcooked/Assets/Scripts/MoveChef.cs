using System.Collections;
using System.Collections.Generic;
using UnityEngine;



public class MoveChef : MonoBehaviour
{
    public float speed;




    // Start is called before the first frame update
    void Start()
    {
       
    }

    // Update is called once per frame
    void Update()
    {
        Vector3 movement = Vector3.zero;
        if (Input.GetKey(KeyCode.W)) movement.z = 1;
        if (Input.GetKey(KeyCode.A)) movement.x = -1;
        if (Input.GetKey(KeyCode.S)) movement.z = -1;
        if (Input.GetKey(KeyCode.D)) movement.x = 1;
        GetComponent<CharacterController>().Move(movement*speed*Time.deltaTime);
        GetComponent<CharacterController>().transform.LookAt(GetComponent<CharacterController>().transform.position + movement);

    }

}
