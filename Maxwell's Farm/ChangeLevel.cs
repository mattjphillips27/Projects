using UnityEngine;
using System.Collections;

public class ChangeLevel : MonoBehaviour 
{
	
	public GameObject cutscene;
	public GameObject JamesBomb;
	public GameObject AlanBomb;

	public void ChangeToLevel (string levelToChangeTo) 
	{
		Application.LoadLevel (levelToChangeTo);
	}

	public void ExitApplication()
	{
		Application.Quit();
	}
	
	public void BreadButton()
	{
		AlanBomb.active = true;
		Cursor.visible = false;
		GameObject duckObj = GameObject.Find ("Alan"); 
		NavMeshAgent agent = duckObj.GetComponent<NavMeshAgent> ();
		agent.speed = 0;
		Time.timeScale = 1;
		Destroy(cutscene);
	}
	
	public void BNButton()
	{
		JamesBomb.active = true;
		Cursor.visible = false;
		GameObject jamesObj = GameObject.Find ("James"); 
		NavMeshAgent JamesAgent = jamesObj.GetComponent<NavMeshAgent> ();
		JamesAgent.speed = 0;
		Time.timeScale = 1;
		Destroy(cutscene);
	}
	
	IEnumerator OnTriggerEnter(Collider other) 
	{
		float fadeTime = GameObject.Find("_Manager").GetComponent<Fading>().BeginFade(1);
		yield return new WaitForSeconds(fadeTime);
		ChangeToLevel("Level2");
	}
	
}
