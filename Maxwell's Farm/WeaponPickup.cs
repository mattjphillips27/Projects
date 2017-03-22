using UnityEngine;
using System.Collections;

public class WeaponPickup : MonoBehaviour 
{
	public GameObject Pitchfork;
	public GameObject BaseballBat;
	public GameObject Shotgun;
	public GameObject Axe;
	public GameObject Machete;
	public GameObject Crowbar;
	public GameObject Knuckles;
	public GameObject Pipe;
	public GameObject Sledgehammer;
	

	// Use this for initialization
	void Start () 
	{
		
	}
	
	void OnTriggerEnter(Collider other) 
	{
		int rand = Random.Range(2, 9);
		print (rand);
		
		if (other.gameObject.tag == "Player")
		{
			if (rand == 1) 
			{
				Pitchfork.active = true;
				Shotgun.active = false;
				BaseballBat.active = false;
				Axe.active = false;
				Machete.active = false;
				Crowbar.active = false;
				Knuckles.active = false;
				Pipe.active = false;
				Sledgehammer.active = false;
				
				Destroy (gameObject);
			} 
			else if (rand == 2) 
			{
				Pitchfork.active = false;
				Shotgun.active = false;
				BaseballBat.active = true;
				Axe.active = false;
				Machete.active = false;
				Crowbar.active = false;
				Knuckles.active = false;
				Pipe.active = false;
				Sledgehammer.active = false;
				
				Destroy (gameObject);
			} 
			else if (rand == 3)
			{
				Pitchfork.active = false;
				Shotgun.active = false;
				BaseballBat.active = false;
				Axe.active = true;
				Machete.active = false;
				Crowbar.active = false;
				Knuckles.active = false;
				Pipe.active = false;
				Sledgehammer.active = false;
				
				Destroy (gameObject);
			}
			else if (rand == 4)
			{
				Pitchfork.active = false;
				Shotgun.active = false;
				BaseballBat.active = false;
				Axe.active = false;
				Machete.active = true;
				Crowbar.active = false;
				Knuckles.active = false;
				Pipe.active = false;
				Sledgehammer.active = false;
				
				Destroy (gameObject);
			}
			else if (rand == 5)
			{
				Pitchfork.active = false;
				Shotgun.active = false;
				BaseballBat.active = false;
				Axe.active = false;
				Machete.active = false;
				Crowbar.active = true;
				Knuckles.active = false;
				Pipe.active = false;
				Sledgehammer.active = false;
				
				Destroy (gameObject);
			}
			else if (rand == 6)
			{
				Pitchfork.active = false;
				Shotgun.active = false;
				BaseballBat.active = false;
				Axe.active = false;
				Machete.active = false;
				Crowbar.active = false;
				Knuckles.active = true;
				Pipe.active = false;
				Sledgehammer.active = false;
				
				Destroy (gameObject);
			}
			else if (rand == 7)
			{
				Pitchfork.active = false;
				Shotgun.active = false;
				BaseballBat.active = false;
				Axe.active = false;
				Machete.active = false;
				Crowbar.active = false;
				Knuckles.active = false;
				Pipe.active = true;
				Sledgehammer.active = false;
				
				Destroy (gameObject);
			}
			else if (rand == 8)
			{
				Pitchfork.active = false;
				Shotgun.active = false;
				BaseballBat.active = false;
				Axe.active = false;
				Machete.active = false;
				Crowbar.active = false;
				Knuckles.active = false;
				Pipe.active = false;
				Sledgehammer.active = true;
				
				Destroy (gameObject);
			}
			else if (rand == 9)
			{
				Pitchfork.active = false;
				Shotgun.active = true;
				BaseballBat.active = false;
				Axe.active = false;
				Machete.active = false;
				Crowbar.active = false;
				Knuckles.active = false;
				Pipe.active = false;
				Sledgehammer.active = false;
				
				Destroy (gameObject);
			}
		}
	}
}


