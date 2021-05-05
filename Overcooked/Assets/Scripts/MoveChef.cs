using System.Collections;
using System.Collections.Generic;
using UnityEngine;



public class MoveChef : MonoBehaviour
{
    enum Dir
    {
        LEFT, RIGHT, UP, DOWN
    };

    public float speed = 50.0f;
    Dir direction = Dir.DOWN;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKey(KeyCode.LeftArrow))
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
    }
}
