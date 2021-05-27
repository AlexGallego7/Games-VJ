using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class NextLevelScreen : MonoBehaviour
{

    public Text pointsText;

    public void Setup(int score)
    {
        Time.timeScale = 0f;
        gameObject.SetActive(true);
        pointsText.text = score.ToString() + " points";
    }

    public void NextLevel ()
    {
        SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex + 1);
    }

    public void Menu ()
    {
        SceneManager.LoadScene(0);
        FindObjectOfType<AudioManager>().Stop("Restaurant");
        FindObjectOfType<AudioManager>().Play("Theme");
    }


}
