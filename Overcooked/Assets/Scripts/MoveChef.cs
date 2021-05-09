using System.Collections;
using System.Collections.Generic;
using UnityEngine;



public class MoveChef : MonoBehaviour
{
    enum Dir
    {
        LEFT, RIGHT, UP, DOWN
    };

    public float speed;
    Dir direction = Dir.DOWN;

    private float horizontalMove;
    private float verticalMove;
    public CharacterController player;

    public Camera mainCamera;
    private Vector3 camForward;
    private Vector3 camRight;
    private Vector3 movePlayer;
    private Vector3 playerInput;

    // Start is called before the first frame update
    void Start()
    {
        player = GetComponent<CharacterController>();
    }

    // Update is called once per frame
    void Update()
    {
        horizontalMove = Input.GetAxis("Horizontal");
        verticalMove = Input.GetAxis("Vertical");
        playerInput = new Vector3(horizontalMove, 0, verticalMove);
        playerInput = Vector3.ClampMagnitude(playerInput,1);
        camDirection();

        movePlayer = playerInput.x * camRight + playerInput.z * camForward;
        player.transform.LookAt(player.transform.position + movePlayer);
        player.Move(movePlayer *speed*Time.deltaTime);
        /*   if (Input.GetKey(KeyCode.LeftArrow))
           {
               transform.Translate(speed * Time.deltaTime, 0.0f, 0.0f);
               if (direction != Dir.LEFT)
               {
                   switch(direction)
                   {
                       case Dir.RIGHT:
                           transform.Rotate(0.0f, 180, 0.0f);
                           break;
                       case Dir.UP:
                           transform.Rotate(0.0f, -90, 0.0f);
                           break;
                       case Dir.DOWN:
                           transform.Rotate(0.0f, 90, 0.0f);
                           break;
                       default:
                           break;
                   }
                   direction = Dir.LEFT;
               }
           }
           if (Input.GetKey(KeyCode.RightArrow))
               transform.Translate(-speed * Time.deltaTime, 0.0f, 0.0f);
           if (Input.GetKey(KeyCode.DownArrow))
               transform.Translate(0.0f, 0.0f, speed * Time.deltaTime);
           if (Input.GetKey(KeyCode.UpArrow))
               transform.Translate(0.0f, 0.0f, -speed * Time.deltaTime);
        */



    }

    void camDirection() {
        camForward = mainCamera.transform.forward;
        camRight = mainCamera.transform.right;

        camForward.y = 0;
        camRight.y = 0;

        camForward = camForward.normalized;
        camRight = camRight.normalized;
    }

}
