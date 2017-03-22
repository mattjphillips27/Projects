using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class AlanBomb : MonoBehaviour {

	
	Text txt;
	int count;
	public GameObject cutscene;
	
	// Use this for initialization
	void Start () 
	{
		txt = GetComponent<Text>();
		count = 1;
		Time.timeScale = 0;
	}
	
	void OnDestroy() {
		Time.timeScale = 1;
	}
	
	// Update is called once per frame
	void Update () 
	{
		
		
		if(Input.GetKeyDown("space"))
		{
			if(count == 1)
			{
				txt.text = "Alan: QUACK!";
				count++;
			}
			else if(count == 2)
			{
				txt.text = "Maxwell: You always know what to say";
				count++;
			}
			else if(count == 3)
			{
				txt.text = "Maxwell: Alan, me and Jane always loved you";
				count++;
			}
			else if(count == 4)
			{	
				txt.text = "Maxwell: You were like a son to us. We couldn't have asked for better";
				count++;
			}
			else if(count == 5)
			{
				txt.text = "Alan: Quack?";
				count++;
			}
			else if(count == 6)
			{
				txt.text = "James: ...";
				count++;
			}
			else if(count == 7)
			{
				txt.text = "Maxwell: Alan, Farewell!";
				count++;
			}
			else if(count == 8)
			{
				txt.text = "Alan: QUACK!";
				count++;
			}
			else if(count == 9)
			{
				
				Destroy(cutscene);
			}
		}
	}
}