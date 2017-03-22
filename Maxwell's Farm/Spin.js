#pragma strict


function Start () {
    
}

// rotate here
function Update() {
    
        transform.eulerAngles+=Vector3(0, Time.deltaTime*90, 0);
}