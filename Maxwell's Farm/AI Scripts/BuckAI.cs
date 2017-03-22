using UnityEngine;
using System.Collections;

public enum BuckAIState
{
	IDLE,
	HIDING,
	CHASING,
	HORNY
}

public class BuckAI : MonoBehaviour 
{
	public int health = 100;
	public int minAttackHealth = 20;
	public int attackDamage;
	public Transform moveTo;
	NavMeshAgent agent;
	public Transform Goat;
	public Timer attackTimer;
	public float minChaseDistance = 100.0f;
	public float minMountDistance = 5.0f;
	public float healAmount = 0.05f;
	public Transform [] wanderPoints;
	private BuckAIState prevState;
	public BuckAIState state = BuckAIState.IDLE;
	private bool bored;
	public GameObject babyGoat;
	public GameObject explosion;
	public GameObject obj;
	private bool fuck = true;
	public Transform po;
	
	void Start () 
	{
		state = BuckAIState.HIDING;
		agent = GetComponent<NavMeshAgent> ();
		Goat = FindClosestGoat().transform;
		if (moveTo == null)
		{
			moveTo = getRandomMoveTo ();
		}
	}
	
	GameObject FindClosestGoat() 
	{
		GameObject[] gos;
		gos = GameObject.FindGameObjectsWithTag("goat");
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
		case BuckAIState.IDLE:
			state = Idle ();
			break;
			
		case BuckAIState.HIDING:
			state = Hide();
			break;
			
		case BuckAIState.CHASING:
			state = Chase();
			break;
			
		case BuckAIState.HORNY:
			state = Horny();
			break;
		}
	}
	
	public BuckAIState Idle()
	{
		return BuckAIState.HIDING;
	}
	
	public BuckAIState Hide()
	{
		//wander
		if (moveTo != null)
		{
			agent.SetDestination (moveTo.position);
			
			if (Vector3.Distance(moveTo.position, transform.position) < 5)
			{
				moveTo = getRandomMoveTo ();
				StartCoroutine(Wait(1.0f));
				fuck = true;
			}
		}
		
		if (Goat != null)
		{
			if (Vector3.Distance(transform.position, Goat.position) <= minChaseDistance)
			{
				return BuckAIState.CHASING;
			}
		}
		
		return BuckAIState.HIDING;
	}
	
	IEnumerator Wait(float waitTime) 
	{
		yield return new WaitForSeconds(waitTime);
		Goat = FindClosestGoat().transform;
	}
	
	public BuckAIState Chase()
	{
		if (Goat != null)
		{
			moveTo = Goat;
			
			if (moveTo != null)
			{
				agent.SetDestination (moveTo.position);
			}
			
			if (Vector3.Distance(moveTo.position, transform.position) <= minMountDistance)
			{
				return BuckAIState.HORNY;
			}
			
			if (Vector3.Distance(moveTo.position, transform.position) > minChaseDistance)
			{
				moveTo = getRandomMoveTo ();
				return BuckAIState.HIDING;
			}
			
			return BuckAIState.CHASING;
		}
		else
		{
			moveTo = getRandomMoveTo ();
			return BuckAIState.HIDING;
		}
	}
	
	public BuckAIState Horny()
	{
		Debug.Log("I am Fucking");
		
		
		if(fuck)
		{
			obj = (GameObject)Instantiate(babyGoat, gameObject.transform.position, gameObject.transform.rotation);
			obj.transform.parent = po;
			obj = (GameObject)Instantiate(explosion, gameObject.transform.position, gameObject.transform.rotation);
			fuck = false;
		}
		
		Goat = null;
		moveTo = getRandomMoveTo ();
		return BuckAIState.HIDING;
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
