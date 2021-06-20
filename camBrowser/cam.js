let video;

// video element
video = document.createElement('video');
video.id = 'video';
video.width = 600;//window.innerWidth;
video.height = 400;//window.innerHeight;
video.autoplay = true;
document.getElementById('videoView').appendChild(video)


const medias = {
  audio: false,
  video: {
    facingMode: {
      exact: "environment"
    }
  }
};

//const video = document.getElementById("video");
const promise = navigator.mediaDevices.getUserMedia(medias);

promise.then(successCallback)
       .catch(errorCallback);

function successCallback(stream) {
  video.srcObject = stream;
};

function errorCallback(err) {
  alert(err);
};