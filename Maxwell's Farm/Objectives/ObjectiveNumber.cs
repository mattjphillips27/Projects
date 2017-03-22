using UnityEngine;
using System.Collections;

public class ObjectiveNumber : MonoBehaviour 
{
	public static ObjectiveNumber sObjectiveNumber;


	public int objectivenumber;
	public bool DrivingBoots;
	public bool Bomb;
	

	// Use this for initialization
	void Start () 
	{
		sObjectiveNumber = this;
		objectivenumber = 1;
		
	}
	
	// Update is called once per frame
	void Update () 
	{

	}
}
