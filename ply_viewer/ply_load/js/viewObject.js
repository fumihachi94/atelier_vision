var container, status;
var scene, camera, cameraTarget, renderer;
var controls;

function init(){
	
	//container = document.createElement('div');
	//document.body.appendChild(container);
	
	camera = new THREE.PerspectiveCamera(35, window.innerHeight/window.innerWidth, 1, 15);
	camera.position.set(3, 0.15, 3);
	
	cameraTarget = new THREE.Vector3( 0, 0, 0);
	
	scene = new THREE.Scene();
	scene.background = new THREE.Color( 0x72645b );
	
	// new THREE.Fog(色, 開始距離, 終点距離);
	scene.fog = new THREE.Fog(0x72645b, 2, 15);
	
	//Ground
	var plane = new THREE.Mesh(new THREE.PlaneBufferGeometry(40, 40), new THREE.MeshPhongMaterial({color: 0x999999, specular: 0x101010}));
	plane.rotation.x = - Math.PI / 2;
	plane.position.y = - 0.5;
	scene.add( plane );
	plane.receiveShadow = true;
	
	// PLY file
	var loader = new THREE.PLYLoader();
	loader.load('Lucy100k.ply', function (geometry) {
	//loader.load('../model/scene_dense.ply', function (geometry) {
		
		console.log("ply load");
		geometry.computeVertexNormals();

		var material = new THREE.MeshStandardMaterial( { color: 0x0055ff, flatShading: true } );
		var mesh = new THREE.Mesh( geometry, material );
		
		mesh.position.x = - 0.0;
		mesh.position.y = - 0.0;
		mesh.position.z = - 0.0;
		mesh.scale.multiplyScalar( 0.0006 );
		//mesh.scale.set(1, 1, 1);

		mesh.castShadow = true;
		mesh.receiveShadow = true;
		
		scene.add( mesh );
		
	});
	

	// Lights
	scene.add( new THREE.HemisphereLight( 0x443333, 0x111122 ) );
	addShadowedLight( 1, 1, 1, 0xffffff, 1.35 );
	addShadowedLight( 0.5, 1, - 1, 0xffaa00, 1 );
	
	// renderer
	renderer = new THREE.WebGLRenderer({
   	canvas: document.querySelector('#viewer')
	});
	renderer.setPixelRatio( window.devicePixelRatio );
	renderer.setSize( window.innerWidth, window.innerHeight );
	renderer.outputEncoding = THREE.sRGBEncoding;
	renderer.shadowMap.enabled = true;
	
	const geometry = new THREE.BoxGeometry(20, 1, 20);
	const material = new THREE.MeshNormalMaterial();
	const box = new THREE.Mesh(geometry, material);
	//scene.add(box);
	
	render();
	
};

function animate() {
	requestAnimationFrame( animate );
	render();
	//stats.update();
}

function render() {
	var timer = Date.now() * 0.0005;
	camera.position.x = Math.sin( timer ) * 2.5;
	camera.position.z = Math.cos( timer ) * 2.5;
	camera.lookAt( cameraTarget );
	//controls.update();
	renderer.render( scene, camera );
}


function addShadowedLight( x, y, z, color, intensity )
{
	var directionalLight = new THREE.DirectionalLight( color, intensity );
	directionalLight.position.set( x, y, z );
	scene.add( directionalLight );

	directionalLight.castShadow = true;

	var d = 1;
	directionalLight.shadow.camera.left = - d;
	directionalLight.shadow.camera.right = d;
	directionalLight.shadow.camera.top = d;
	directionalLight.shadow.camera.bottom = - d;

	directionalLight.shadow.camera.near = 1;
	directionalLight.shadow.camera.far = 4;

	directionalLight.shadow.mapSize.width = 1024;
	directionalLight.shadow.mapSize.height = 1024;

	directionalLight.shadow.bias = - 0.001;
}


window.addEventListener('load', init);
animate();