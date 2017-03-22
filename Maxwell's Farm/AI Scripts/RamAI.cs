using UnityEngine;
using System.Collections;

public enum RamAIState
{
	IDLE,
	HIDING,
	CHASING,
	HORNY
}

public class RamAI : MonoBehaviour 
{
	public int health = 100;
	public int minAttackHealth = 20;
	public int attackDamage;
	public Transform moveTo;
	NavMeshAgent agent;
	public Transform Sheep;
	public Timer attackTimer;
	public float minChaseDistance = 100.0f;
	public float minMountDistance = 5.0f;
	public float healAmount = 0.05f;
	public Transform [] wanderPoints;
	private RamAIState prevState;
	public RamAIState state = RamAIState.IDLE;
	private bool bored;
	public GameObject lamb;
	public GameObject explosion;
	public GameObject obj;
	private bool fuck = true;
	public Transform po;
	
	void Start () 
	{
		state = RamAIState.HIDING;
		agent = GetComponent<NavMeshAgent> ();
		Sheep = FindClosestSheep().transform;
		if (moveTo == null)
		{
			moveTo = getRandomMoveTo ();
		}
	}
	
	GameObject FindClosestSheep() 
	{
		GameObject[] gos;
		gos = GameObject.FindGameObjectsWithTag("sheep");
		GameObject closest = null;
		float distance = Mathf.Infinity;
		Vector3 position = transform.position;
		foreach (GameObject go in gos) 
		{
			Vector3 diff = go.transform.position - position;
			float curDistance = diff.sqrMagnitude;
			if (curDistance < distance) 
			{
				closest = go;
				distance = curDistance;
			}
		}
		
		
		return closest;
	}
	
	public void MakeDecision()
	{
		prevState = state;
		
		switch(state)
		{
		case RamAIState.IDLE:
			state = Idle ();
			break;
			
		case RamAIState.HIDING:
			state = Hide();
			break;
			
		case RamAIState.CHASING:
			state = Chase();
			break;
			
		case RamAIState.HORNY:
			state = Horny();
			break;
		}
	}
	
	public RamAIState Idle()
	{
		return RamAIState.HIDING;
	}
	
	public RamAIState Hide()
	{
		//wander
		if (moveTo != null)
		{
			agent.SetDestination (moveTo.position);
			
			if (Vector3.Distance(moveTo.position, transform.position) < 5)
			{
				moveTo = getRandomMoveTo ();
				StartCoroutine(Wait(10.0f));
				fuck = true;
			}
		}
		
		if (Sheep != null)
		{
			if (Vector3.Distance(transform.position, Sheep.position) <= minChaseDistance)
			{
				return RamAIState.CHASING;
			}
		}
		
		return RamAIState.HIDING;
	}
	
	public RamAIState Chase()
	{
		if (Sheep != null)
		{
			moveTo = Sheep;
			
			if (moveTo != null)
			{
				agent.SetDestination (moveTo.position);
			}
			
			if (Vector3.Distance(moveTo.position, transform.position) <= minMountDistance)
			{
				return RamAIState.HORNY;
			}
			
			if (Vector3.Distance(moveTo.position, transform.position) > minChaseDistance)
			{
				moveTo = getRandomMoveTo ();
				return RamAIState.HIDING;
			}
			
			return RamAIState.CHASING;
		}
		else
		{
			moveTo = getRandomMoveTo ();
			return RamAIState.HIDING;
		}
	}
	
	public RamAIState Horny()
	{		
		if(fuck)
		{
			obj = (GameObject)Instantiate(lamb, gameObject.transform.position, gameObject.transform.rotation);
			obj.transform.parent = po;
			obj = (GameObject)Instantiate(explosion, gameObject.transform.position, gameObject.transform.rotation);
			fuck = false;
		}
		
		Sheep = null;
		moveTo = getRandomMoveTo ();
		return RamAIState.HIDING;
	}
	
	public Transform getRandomMoveTo()
	{
		Transform point = wanderPoints[Random.Range(0, wanderPoints.Length-1)];
		//Debug.Log ("Moving to: " + point.position);
		return point;
	}
	
	IEnumerator Wait(float waitTime) 
	{
		yield return new WaitForSeconds(waitTime);
		Sheep = FindClosestSheep().transform;
	}
	
	public void TakeDamage(int damage)
	{
		health -= damage;
		
		if (health <= 0)
		{
			Destroy (gameObject);
		}
	}
	
	void Update()
	{
		//health += (int)(healAmount * Time.deltaTime);
		MakeDecision();
	}
}
