using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class NextLevelScreen : MonoBehaviour
{

    public Text pointsText;
    public bool up;

    public void Setup(int score)
    {
        Time.timeScale = 0f;
        gameObject.SetActive(true);
        up = true;
        pointsText.text = score.ToString() + " points";
    }

    public void NextLevel()
    {
        up = false;
        SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex + 1);
    }

    public void Restart ()
    {
        up = false;
        SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex);
        gameObject.SetActive(false);
    }

    public void Menu()
    {
        up = false;
        SceneManager.LoadScene(0);
        FindObjectOfType<AudioManager>().Stop("Restaurant");
        FindObjectOfType<AudioManager>().Play("Theme");
    }

    public void End()
    {
        SceneManager.LoadScene("CredsScene");
        FindObjectOfType<AudioManager>().Stop("Restaurant");
        FindObjectOfType<AudioManager>().Play("Creds");
    }


}