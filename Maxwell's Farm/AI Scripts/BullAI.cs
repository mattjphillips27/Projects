using UnityEngine;
using System.Collections;

public enum BullAIState
{
	IDLE,HIDING,CHASING,HORNY
}

public class BullAI : MonoBehaviour 
{
	public int health = 100;
	public int minAttackHealth = 20;
	public int attackDamage;
	public Transform moveTo;
	NavMeshAgent agent;
	public Transform cow;
	public Timer attackTimer;
	public float minChaseDistance = 100.0f;
	public float minMountDistance = 5.0f;
	public float healAmount = 0.05f;
	public Transform [] wanderPoints;
	private BullAIState prevState;
	public BullAIState state = BullAIState.IDLE;
	public GameObject babyCow;
	public GameObject explosion;
	public GameObject obj;
	private bool fuck = true;
	public Transform po;
	
	void Start () 
	{
		state = BullAIState.HIDING;
		agent = GetComponent<NavMeshAgent> ();
		cow = FindClosestCow().transform;
		if (moveTo == null)
		{
			moveTo = getRandomMoveTo ();
		}
	}
	
	GameObject FindClosestCow() 
	{
		GameObject[] gos;
		gos = GameObject.FindGameObjectsWithTag("cow");
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
		case BullAIState.IDLE:
			state = Idle ();
			break;
			
		case BullAIState.HIDING:
			state = Hide();
			break;
			
		case BullAIState.CHASING:
			state = Chase();
			break;
			
		case BullAIState.HORNY:
			state = Horny();
			break;
		}
	}
	
	public BullAIState Idle()
	{
		return BullAIState.HIDING;
	}
	
	public BullAIState Hide()
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
		
		if (cow != null)
		{
			if (Vector3.Distance(transform.position, cow.position) <= minChaseDistance)
			{
				return BullAIState.CHASING;
			}
		}
		
		return BullAIState.HIDING;
	}
	
	IEnumerator Wait(float waitTime) 
	{
		yield return new WaitForSeconds(waitTime);
		cow = FindClosestCow().transform;
	}
	
	public BullAIState Chase()
	{
		if (cow != null)
		{
			moveTo = cow;
			
			if (moveTo != null)
			{
				agent.SetDestination (moveTo.position);
			}
			
			if (Vector3.Distance(moveTo.position, transform.position) <= minMountDistance)
			{
				return BullAIState.HORNY;
			}
			
			if (Vector3.Distance(moveTo.position, transform.position) > minChaseDistance)
			{
				moveTo = getRandomMoveTo ();
				return BullAIState.HIDING;
			}
			
			return BullAIState.CHASING;
		}
		else
		{
			moveTo = getRandomMoveTo ();
			return BullAIState.HIDING;
		}
	}
	
	public BullAIState Horny()
	{
		Debug.Log("I am Fucking");
		
		
		if(fuck)
		{
			obj = (GameObject)Instantiate(babyCow, gameObject.transform.position, gameObject.transform.rotation);
			obj.transform.parent = po;
			obj = (GameObject)Instantiate(explosion, gameObject.transform.position, gameObject.transform.rotation);
			fuck = false;
		}
		
		cow = null;
		moveTo = getRandomMoveTo ();
		return BullAIState.HIDING;
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
