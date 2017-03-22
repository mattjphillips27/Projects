#pragma strict

function Start () 
{
	if(gameObject.tag == "Bullet")
	{
		yield WaitForSeconds (0.25);
		Destroy (gameObject);
	}
}

function Update ()
{
		
}

function OnControllerColliderHit(hit : ControllerColliderHit) 
{	
	if(hit.gameObject.tag == "Alan")
	{
		Destroy(gameObject);
	}
}

