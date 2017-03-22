#pragma strict
var Bread : Transform;
var Spawn : Transform;
function Start () 
{

}

function Update () {
	if(Input.GetButtonDown("Fire2"))
			{ 
				ThrowBread(); 
			}
}

function ThrowBread()
	{
		var pel = Instantiate(Bread, Spawn.position, Spawn.rotation); pel.GetComponent.<Rigidbody>().AddForce(transform.forward * 500);
	}