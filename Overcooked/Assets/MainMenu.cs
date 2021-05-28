using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class MainMenu : MonoBehaviour

{
    public GameObject levelsUI;

    public void PlayGame ()
    {
        FindObjectOfType<AudioManager>().Stop("Theme");
        FindObjectOfType<AudioManager>().Play("Restaurant");

        SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex + 1);
    }

    public void QuitGame ()
    {
        Application.Quit();
    }

    public void ChooseLevel ()
    {
        levelsUI.SetActive(!levelsUI.activeSelf);
    }

    public void Level1 ()
    {
        FindObjectOfType<AudioManager>().Stop("Theme");
        FindObjectOfType<AudioManager>().Play("Restaurant");
        SceneManager.LoadScene("EscenaInicial");

    }

    public void Level2()
    {
        FindObjectOfType<AudioManager>().Stop("Theme");
        FindObjectOfType<AudioManager>().Play("Restaurant");
        SceneManager.LoadScene("Escena2");

    }

    public void Level3 ()
    {
        FindObjectOfType<AudioManager>().Stop("Theme");
        FindObjectOfType<AudioManager>().Play("Restaurant");
        SceneManager.LoadScene("Escena3");

    }

    public void Level4 ()
    {
        FindObjectOfType<AudioManager>().Stop("Theme");
        FindObjectOfType<AudioManager>().Play("Restaurant");
        SceneManager.LoadScene("Escena4");

    }

    public void Level5 ()
    {
        FindObjectOfType<AudioManager>().Stop("Theme");
        FindObjectOfType<AudioManager>().Play("Restaurant");
        SceneManager.LoadScene("Escena5");
    }
}
