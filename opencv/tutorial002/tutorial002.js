let loadOpencv = document.getElementById('opencv');
let video      = document.getElementById('videoInput');

const FPS = 30;
let streaming = false;

let src, dst, cap ;


function onOpenCvReady() {
    console.log("status ready");
    document.getElementById('status').innerHTML = 'OpenCV.js is ready.';
}
  
function onVideoReady(){
    src = new cv.Mat(video.height, video.width, cv.CV_8UC4);
    dst = new cv.Mat(video.height, video.width, cv.CV_8UC1);
    cap = new cv.VideoCapture(video);

    navigator.mediaDevices.getUserMedia({ video: true, audio: false }).then(function(_stream) {
        streaming = video.srcObject = _stream;
        video.play();
        // schedule the first one.
        setTimeout(processVideo, 0);
    }).catch(function(_err) {
        console.log("An error occurred! " + _err);
    });
}

function processVideo() {
    try {
        if (!streaming) {
            // clean and stop.
            console.log("end");
            src.delete();
            dst.delete();
            return;
        }
        let begin = Date.now();
        // start processing.
        cap.read(src);
        cv.cvtColor(src, dst, cv.COLOR_RGBA2GRAY);
        cv.imshow('canvasOutput', dst);
        // schedule the next one.
        let delay = 1000/FPS - (Date.now() - begin);
        console.log("ok2");
        setTimeout(processVideo, delay);
    } catch (err) {
        cv.utils.printError(err);
    }
};


loadOpencv.onload = function(){
    onOpenCvReady();
    onVideoReady();
}