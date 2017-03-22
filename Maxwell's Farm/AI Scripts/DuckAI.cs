using UnityEngine;
using System.Collections;

public enum AIStates
{
	IDLE,
	WANDERING,
	CHASING,
	ATTACK
}

public class DuckAI : MonoBehaviour 
{
	public static DuckAI sDuckAI;
	public float health = 100;
	public int minAttackHealth = 20;
	public int attackDamage;
	public Transform moveTo;
	NavMeshAgent agent;
	public Transform enemy;
	public Timer attackTimer;
	public float minChaseDistance = 100.0f;
	public float minAttackDistance = 5.0f;
	public float healAmount = 0.05f;
	public Transform [] wanderPoints;
	private AIStates prevState;
	public AIStates state = AIStates.IDLE;


	private Transform player;
	
	void Start () 
	{
		state = AIStates.WANDERING;
		agent = GetComponent<NavMeshAgent> ();
		
		GameObject obj = GameObject.FindGameObjectWithTag("AlanHealth");
		Alan healthBar = obj.transform.GetComponent<Alan>();
		
		health = healthBar.health;
		
		
	}
	
	public void MakeDecision()
	{
		prevState = state;
		
		switch(state)
		{
		case AIStates.IDLE:
			state = Idle ();
			break;

		case AIStates.WANDERING:
			state = Wander();
			break;
			
		case AIStates.CHASING:
			state = Chase();
			break;
			
		case AIStates.ATTACK:
			state = Attack();
			break;  
		}
	}
	
	public AIStates Idle()
	{
		return AIStates.WANDERING;
	}
	
	public AIStates Wander()
	{
		//wander
		if (moveTo != null)
		{
			agent.SetDestination (moveTo.position);

		}
		
		if (enemy != null)
		{
			if (Vector3.Distance(transform.position, enemy.position) <= minChaseDistance)
			{
				
				return AIStates.CHASING;
			}
		}

		return AIStates.WANDERING;
	}
	
	public AIStates Chase()
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
				return AIStates.ATTACK;
			}
			
			return AIStates.CHASING;
		}
		return AIStates.WANDERING;
	}
	

	
	public AIStates Attack()
	{
		if (enemy != null)
		{
			moveTo = enemy;
			
			if (moveTo != null)
			{
				agent.SetDestination (moveTo.position);
			}
			
			if (Vector3.Distance(transform.position, enemy.position) > minAttackDistance)
			{
				GetComponent<Animation>().Play("Walk");
				return AIStates.CHASING;
			}
			
			if (state != prevState)
			{
				attackTimer.StartTimer();
			}
			
			if (attackTimer.running == false)
			{
				enemy.GetComponent<FSMAI>().TakeDamage(Random.Range (0, attackDamage));
				attackTimer.StartTimer();
			}
			
			return AIStates.ATTACK;
		}
		return AIStates.CHASING;
	}
	

	
	public void TakeDamage(int damage)
	{
		health -= damage;
	}

	void Update()
	{
		if (GameObject.FindWithTag ("Bread")) 
		{
			
			agent.stoppingDistance = 1;
			moveTo = GameObject.FindWithTag ("Bread").transform;
		}
		else if (GameObject.FindWithTag ("Player")) {
			
			agent.stoppingDistance = 5;
			moveTo = GameObject.FindWithTag ("Player").transform;
		}
		
		health += (int)(healAmount * Time.deltaTime);
		
		MakeDecision();
	}
}