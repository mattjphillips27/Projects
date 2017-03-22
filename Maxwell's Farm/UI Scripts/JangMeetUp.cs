using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class JangMeetUp : MonoBehaviour {

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
		GameObject manager = GameObject.Find ("_Manager"); 
		ObjectiveNumber num = manager.GetComponent<ObjectiveNumber> (); 
		
		if(Input.GetKeyDown("space"))
		{
			if(count == 1)
			{
				txt.text = "Maxwell: I forgot you were working today";
				count++;
			}
			else if(count == 2)
			{
				txt.text = "Jang: The animals are going cray cray";
				count++;
			}
			else if(count == 3)
			{
				txt.text = "Jang: What could have caused this?";
				count++;
			}
			else if(count == 4)
			{
				txt.text = "Jang: I haven't done this, if you were thinking that";
				count++;
			}
			else if(count == 5)
			{
				txt.text = "Maxwell: I wasn't, Jang";
				count++;
			}
			else if(count == 6)
			{
				txt.text = "Jang: Good, I didn't do this";
				count++;
			}
			else if(count == 7)
			{
				txt.text = "Maxwell: They killed my wife";
				count++;
			}
			else if(count == 8)
			{
				txt.text = "Jang: Again! I did not do this, I've been with the scarecrow all day!";
				count++;
			}
			else if(count == 9)
			{
				txt.text = "Maxwell: Jang, don't worry, I know";
				count++;
			}
			else if(count == 10)
			{
				txt.text = "Maxwell: How should we handle these? We can't let them escape";
				count++;
			}
			else if(count == 11)
			{
				txt.text = "Jang: Probably a bomb or something";
				count++;
			}
			else if(count == 12)
			{
				txt.text = "Jang: This could probably do, I found it...erm ";
				count++;
			}
			else if(count == 13)
			{
				txt.text = "Jang: With the scarecrow! Yes he had it";
				count++;
			}
			else if(count == 14)
			{
				txt.text = "Jang: Anyway, you take this";
				count++;
			}
			else if(count == 15)
			{
				txt.text = "Maxwell: Erm? Thanks? You'll have to escape if I use this";
				count++;
			}
			else if(count == 16)
			{
				txt.text = "Jang: Don't worry about me, I'll be fine. See you around";
				count++;
			}
			else if(count == 17)
			{
				
				num.Bomb = true;
				Destroy(cutscene);
			}
		}
	}
}