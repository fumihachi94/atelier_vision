// ページの読み込みを待つ
window.addEventListener('load', init);

// レンダラーを作成
const renderer = new THREE.WebGLRenderer({
   	canvas: document.querySelector('#myCanvas')
});

// シーンを作成
const scene = new THREE.Scene();


// カメラを作成
const camera = new THREE.PerspectiveCamera(45, 640 / 450);
camera.position.set(0, 0, +1000);


// オビジェクトの生成
const geometry = new THREE.BoxGeometry(400, 400, 400);
const material = new THREE.MeshNormalMaterial();
const box = new THREE.Mesh(geometry, material);

function init() {
	const width = 640;
   const height = 450;   
   renderer.setPixelRatio(window.devicePixelRatio);
   renderer.setSize(width, height);
}


var btn = document.getElementById('btn');

var playFlag = 0;
 
btn.addEventListener('click', function() {
   console.log('クリックされました！');
	if(playFlag) {
 		playFlag = 0;
	} else {
		playFlag = 1;
	}
   console.log(playFlag);
	scene.add(box);
   tickCamRot(); 
}, false);



// 毎フレーム時に実行されるループイベントです
function tick() {
   if(playFlag){
		box.rotation.y += 0.01;
		renderer.render(scene, camera); // レンダリング
		requestAnimationFrame(tick);
   }else{
		renderer.render(scene, camera);
	}
} 

let rot = 0;

function tickCamRot(){
	if(playFlag){
		rot += 0.5; // [deg]
		const radian = rot * Math.PI / 180; 
		camera.position.x = 1000 * Math.sin(radian);
		camera.position.z = 1000 * Math.cos(radian);
		camera.lookAt(new THREE.Vector3(0, 0, 0));
		renderer.render(scene, camera); // レンダリング
		requestAnimationFrame(tickCamRot);
   }else{
		renderer.render(scene, camera);
	}
}


//---------------------------
//   Touch event function
//---------------------------

var $eventState = $('#eventState');

let EVENTSTATE = ['touch', 'move', 'end'];

var touch = document.getElementById("myCanvas");

var dispPos = function(x,y){
	var str = "x: " + x + ",  y: " + y;
   document.getElementById("position").innerText = str;
}

var updatePos = function(event){
	var touchObject = event.changedTouches[0] ;
	var x = touchObject.pageX ;
	var y = touchObject.pageY ;

   dispPos(x,y);
}

var updateEventState = function(eventname) {
  $eventState.text(eventname);
};


var touchMove = function(event){
	event.preventDefault();
	updatePos(event);
   updateEventState(EVENTSTATE[1]);
	//draw();
};


touch.addEventListener("touchmove", touchMove)


function draw() {
	if (touch.getContext){
    var ctx = touch.getContext('2d');
    ctx.beginPath();
    ctx.arc(75, 75, 50, 0, Math.PI * 2, true); // 外の円
    ctx.moveTo(110, 75);
    ctx.arc(75, 75, 35, 0, Math.PI, false);  // 口 (時計回り)
    ctx.moveTo(65, 65);
    ctx.arc(60, 65, 5, 0, Math.PI * 2, true);  // 左目
    ctx.moveTo(95, 65);
    ctx.arc(90, 65, 5, 0, Math.PI * 2, true);  // 右目
    ctx.stroke();
	};
}






