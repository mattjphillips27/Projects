using UnityEngine;
using System.Collections;

public enum CockrilAIState
{
	IDLE,
	HIDING,
	CHASING,
	HORNY
}

public class CockrilAI : MonoBehaviour 
{
	public int health = 100;
	public int minAttackHealth = 20;
	public int attackDamage;
	public Transform moveTo;
	NavMeshAgent agent;
	public Transform chicken;
	public Timer attackTimer;
	public float minChaseDistance = 100.0f;
	public float minMountDistance = 5.0f;
	public float healAmount = 0.05f;
	public Transform [] wanderPoints;
	private CockrilAIState prevState;
	public CockrilAIState state = CockrilAIState.IDLE;
	private bool bored;
	public GameObject babychicken;
	public GameObject explosion;
	public GameObject obj;
	private bool fuck = true;
	public Transform po;
	
	void Start () 
	{
		state = CockrilAIState.HIDING;
		agent = GetComponent<NavMeshAgent> ();
		chicken = FindClosestchicken().transform;
		if (moveTo == null)
		{
			moveTo = getRandomMoveTo ();
		}
	}
	
	GameObject FindClosestchicken() 
	{
		GameObject[] gos;
		gos = GameObject.FindGameObjectsWithTag("chicken");
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
		case CockrilAIState.IDLE:
			state = Idle ();
			break;
			
		case CockrilAIState.HIDING:
			state = Hide();
			break;
			
		case CockrilAIState.CHASING:
			state = Chase();
			break;
			
		case CockrilAIState.HORNY:
			state = Horny();
			break;
		}
	}
	
	public CockrilAIState Idle()
	{
		return CockrilAIState.HIDING;
	}
	
	public CockrilAIState Hide()
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
		
		if (chicken != null)
		{
			if (Vector3.Distance(transform.position, chicken.position) <= minChaseDistance)
			{
				return CockrilAIState.CHASING;
			}
		}
		
		return CockrilAIState.HIDING;
	}
	
	IEnumerator Wait(float waitTime) 
	{
		yield return new WaitForSeconds(waitTime);
		chicken = FindClosestchicken().transform;
	}
	
	public CockrilAIState Chase()
	{
		if (chicken != null)
		{
			moveTo = chicken;
			
			if (moveTo != null)
			{
				agent.SetDestination (moveTo.position);
			}
			
			if (Vector3.Distance(moveTo.position, transform.position) <= minMountDistance)
			{
				return CockrilAIState.HORNY;
			}
			
			if (Vector3.Distance(moveTo.position, transform.position) > minChaseDistance)
			{
				moveTo = getRandomMoveTo ();
				return CockrilAIState.HIDING;
			}
			
			return CockrilAIState.CHASING;
		}
		else
		{
			moveTo = getRandomMoveTo ();
			return CockrilAIState.HIDING;
		}
	}
	
	public CockrilAIState Horny()
	{
		Debug.Log("I am Fucking");
		
		
		if(fuck)
		{
			obj = (GameObject)Instantiate(babychicken, gameObject.transform.position, gameObject.transform.rotation);
			obj.transform.parent = po;
			obj = (GameObject)Instantiate(explosion, gameObject.transform.position, gameObject.transform.rotation);
			fuck = false;
		}
		
		chicken = null;
		moveTo = getRandomMoveTo ();
		return CockrilAIState.HIDING;
	}
	
	public Transform getRandomMoveTo()
	{
		Transform point = wanderPoints[Random.Range(0, wanderPoints.Length-1)];
		//Debug.Log ("Moving to: " + point.position);
		return point;
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
