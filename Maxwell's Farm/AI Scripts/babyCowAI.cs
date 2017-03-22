using UnityEngine;
using System.Collections;

public enum babyCowAIState
{
	IDLE,
	WANDERING,
	CHASING,
	ATTACK
}

public class babyCowAI : MonoBehaviour 
{
	public int health = 100;
	public int minAttackHealth = 20;
	public int attackDamage;
	public Transform moveTo;
	NavMeshAgent agent;
	public Transform enemy;
	public Timer attackTimer;
	public float minChaseDistance = 100.0f;
	public float minAttackDistance = 5.0f;
	public float healAmount = 0.05f;
	public GameObject [] wanderPoints;
	private babyCowAIState prevState;
	public babyCowAIState state = babyCowAIState.IDLE;
	private bool bored;
	int i;
	
	public GameObject Cow;
	
	IEnumerator Start () 
	{
		state = babyCowAIState.WANDERING;
		agent = GetComponent<NavMeshAgent> ();
		enemy = GameObject.FindGameObjectWithTag ("Alan").transform;

		wanderPoints = GameObject.FindGameObjectsWithTag("BabyCowPoints");
		
		if (moveTo == null)
		{
			moveTo = getRandomMoveTo ();
		}
		
		yield return new WaitForSeconds(Random.Range(30, 45));
		GameObject obj = Instantiate(Cow, gameObject.transform.position, gameObject.transform.rotation) as GameObject;
		Debug.Log("new cow1");
		Destroy(gameObject);
	}
	
	
	public void MakeDecision()
	{
		prevState = state;
		
		switch(state)
		{
		case babyCowAIState.IDLE:
			state = Idle ();
			break;
			
		case babyCowAIState.WANDERING:
			state = Wander();
			break;
			
		case babyCowAIState.CHASING:
			state = Chase();
			break;
			
		case babyCowAIState.ATTACK:
			state = Attack();
			break;  
		}
	}
	
	public babyCowAIState Idle()
	{
		return babyCowAIState.WANDERING;
	}
	
	public babyCowAIState Wander()
	{
		//wander
		if (moveTo != null)
		{
			agent.SetDestination (moveTo.position);
			
			if (Vector3.Distance(moveTo.position, transform.position) < 5)
			{
				moveTo = getRandomMoveTo ();
			}
		}
		
		if (enemy != null)
		{
			if (Vector3.Distance(transform.position, enemy.position) <= minChaseDistance)
			{
				return babyCowAIState.CHASING;
			}
		}
		
		return babyCowAIState.WANDERING;
	}
	
	public babyCowAIState Chase()
	{
		if (enemy != null)
		{
			moveTo = enemy;
			
			if (moveTo != null)
			{
				agent.SetDestination (moveTo.position);
			}
			
			if (Vector3.Distance(moveTo.position, transform.position) <= minAttackDistance)
			{
				return babyCowAIState.ATTACK;
			}
			
			if (Vector3.Distance(moveTo.position, transform.position) > minChaseDistance)
			{
				moveTo = getRandomMoveTo ();
				return babyCowAIState.WANDERING;
			}
			
			return babyCowAIState.CHASING;
		}
		else
		{
			moveTo = getRandomMoveTo ();
			return babyCowAIState.WANDERING;
		}
	}
	
	public babyCowAIState Attack()
	{
		if (enemy != null)
		{
			if (health < minAttackHealth)
			{
				moveTo = getRandomMoveTo();
				return babyCowAIState.WANDERING;
			}
			
			moveTo = enemy;
			
			if (moveTo != null)
			{
				agent.SetDestination (moveTo.position);
			}
			
			if (Vector3.Distance(transform.position, enemy.position) > minAttackDistance)
			{
				return babyCowAIState.CHASING;
			}
			
			if (state != prevState)
			{
				attackTimer.StartTimer();
			}
			
			if (attackTimer.running == false)
			{
				enemy.GetComponent<DuckAI>().TakeDamage(Random.Range (0, attackDamage));
				attackTimer.StartTimer();
			}
			
			return babyCowAIState.ATTACK;
		}
		else
		{
			moveTo = getRandomMoveTo ();
			
			return babyCowAIState.WANDERING;
		}
	}
	
	public void growUp()
	{
		
	}
	
	public Transform getRandomMoveTo()
	{
		Transform point = wanderPoints[Random.Range(0, wanderPoints.Length)].transform;
		//Debug.Log ("Moving to: " + point.position);
		return point;
	}
	
	public void TakeDamage(int damage)
	{
		health -= damage;
		
		if (health <= 0)
		{
			GameObject spawnerObj = GameObject.Find("Spawner");
			EnemySpawner spawner = spawnerObj.GetComponent<EnemySpawner>();
			
			if (gameObject.tag == "babyCow")
			{
				spawner.cowCount = spawner.cowCount - 1;
			}
			
			
			Destroy (gameObject);
		}
	}
	
	void Update()
	{
		health += (int)(healAmount * Time.deltaTime);
				
		MakeDecision();
	}
}