using UnityEngine;
using System.Collections;

public class Alan : MonoBehaviour {

	public float health;

	// Use this for initialization
	void Awake () 
	{
		DontDestroyOnLoad(this);
	}
		
	// Update is called once per frame
	void Update () 
	{
		if (Input.GetKeyDown(KeyCode.Escape))
		{
			Destroy(gameObject);
		}
	}
	
	public void AdjustHealth(float newHealth)
	{
		health = newHealth;
	}
}
