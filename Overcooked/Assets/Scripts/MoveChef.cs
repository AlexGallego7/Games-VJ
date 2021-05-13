using System.Collections;
using System.Collections.Generic;
using UnityEngine;



public class MoveChef : MonoBehaviour
{
    public float speed;

    private Vector3 posDef;


    // Start is called before the first frame update
    void Start()
    {
        posDef = this.gameObject.transform.position;
    }

    // Update is called once per frame
    void Update()
    {
        if (this.gameObject.transform.position.y != posDef.y)
        {
            float dif = this.gameObject.transform.position.y - posDef.y;
            GetComponent<CharacterController>().Move(new Vector3(0, -dif, 0));
        }
        Vector3 movement = Vector3.zero;
        if (Input.GetKey(KeyCode.W) || Input.GetKey(KeyCode.UpArrow)) movement.z = 1;
        if (Input.GetKey(KeyCode.A) || Input.GetKey(KeyCode.LeftArrow)) movement.x = -1;
        if (Input.GetKey(KeyCode.S) || Input.GetKey(KeyCode.DownArrow)) movement.z = -1;
        if (Input.GetKey(KeyCode.D) || Input.GetKey(KeyCode.RightArrow)) movement.x = 1;
        GetComponent<CharacterController>().Move(movement*speed*Time.deltaTime);
        GetComponent<CharacterController>().transform.LookAt(GetComponent<CharacterController>().transform.position + movement);

    }

}
