using UnityEngine;
using System.Collections;

public class AIGUI : MonoBehaviour
{
	public FSMAI agent1, agent2;
	Rect agentGUI1, agentGUI2;
	Rect statePos, healthPos;
	
	// Use this for initialization
	void Start () 
	{
		agentGUI1 = new Rect(10,10,150,200);
		agentGUI2 = new Rect(Screen.width - 150,10,150,200);

		statePos = new Rect(0,0,150,20);
		healthPos = new Rect(0,20,150,20);

		agent1 = GameObject.Find("Agent Smith").GetComponent<FSMAI>();
		agent2 = GameObject.Find("Agent Jones").GetComponent<FSMAI>();
	}

	void OnGUI()
	{
		GUI.BeginGroup(agentGUI1);
			GUI.Label(statePos, getStateLabel(agent1));
			GUI.Label(healthPos, agent1.health.ToString());
		GUI.EndGroup();

		GUI.BeginGroup(agentGUI2);
			GUI.Label(statePos, getStateLabel(agent2));
			GUI.Label(healthPos, agent2.health.ToString());
		GUI.EndGroup();
	}

	private string getStateLabel(FSMAI aiScript)
	{
		string curState;
		
		switch(aiScript.state)
		{
			case AIState.IDLE:
				curState = "IDLE";
				break;
				
			case AIState.CHASING:
				curState = "CHASING";
				break;
				
			case AIState.ATTACK:
				curState = "ATTACK";
				break;
				
			case AIState.WANDERING:
				curState = "WANDERING";
				break;
				
			default:
				curState = "UNDEFINED";
				break;
		}

		return curState;
	}
}
