using UnityEngine;
using System.Collections;

public class ChangeSpeed : MonoBehaviour {
	
	public GameObject cutscene;
	
	// Use this for initialization
	void Start () 
	{
		
	}
	
	// Update is called once per frame
	void Update () 
	{
		
	}
	
	void OnTriggerEnter(Collider other)
	{
		GameObject duckObj = GameObject.Find ("Alan"); 
		NavMeshAgent agent = duckObj.GetComponent<NavMeshAgent> ();
		
		Debug.Log("HELLLLLLLOO");
		
		cutscene.active = true;
		
		agent.speed = 6;
		Destroy (gameObject);
	}
}
