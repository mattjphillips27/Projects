using UnityEngine;
using System.Collections;

public class ChangeJamesSpeed1 : MonoBehaviour {

	public GameObject cutscene;
	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}
	
	void OnTriggerEnter(Collider other)
	{
		if (other.gameObject.tag == "Player") 
		{
		
			GameObject jamesObj = GameObject.Find ("James"); 
			NavMeshAgent JamesAgent = jamesObj.GetComponent<NavMeshAgent> ();
			
			Debug.Log("HELLLLLLLOO");
			
			cutscene.active = true;
		
			JamesAgent.speed = 6;
			Destroy (gameObject);
		}
				
	}
}
