using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class PauseMenu : MonoBehaviour
{ 
    public static bool GameIsPaused = false;

    public GameObject pauseMenuUI;
    public GameObject afterSceneUI;

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Escape))
        {
            if (GameIsPaused)
            {
                Resume();
            } else
            {
                if (!afterSceneUI.GetComponent<NextLevelScreen>().up)
                    Pause();
            }
        }
    
    }

    public void Resume ()
    {
        pauseMenuUI.SetActive(false);
        Time.timeScale = 1f;

        GameIsPaused = false;

    }

    public void LoadMenu()
    {
        Time.timeScale = 1f;
        GameIsPaused = false;
        SceneManager.LoadScene(0);
        FindObjectOfType<AudioManager>().Stop("Restaurant");
        FindObjectOfType<AudioManager>().Play("Theme");

    }

    public void QuitGame()
    {
        Application.Quit();
    }

    void Pause ()
    {
        pauseMenuUI.SetActive(true);
        Time.timeScale = 0f;

        GameIsPaused = true;

    }
}
