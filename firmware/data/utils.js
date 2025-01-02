/* ------------------- Network / HTTP --------------------- */

function _request(method, path, request, log, callback) {
  request.onGoing = true;
  request.timestamp = performance.now();
  const xhr = new XMLHttpRequest();
  xhr.onload = () => {
    request.onGoing = false;
    log.innerText = xhr.status == 200 ? 'OK' : "404";
    callback && callback(xhr.response);
  };
  xhr.ontimeout = () => {
    request.onGoing = false;
    log.innerText = "Timeout on XML request!";
    callback && callback(null);
  };
  xhr.onerror = () => {
    request.onGoing = false;
    log.innerText = "Error on XML request!";
    callback && callback(null);
  };
  xhr.open(method, path, true);
  xhr.send();
}

/* ------------------- Page orientation --------------------- */

function showOrHidePage() {
  const elements = document.getElementById("main-background").children;
  if (window.matchMedia("(orientation: portrait)").matches) {
    // Portrait
    for (let element of elements) {
      element.style.visibility = 'hidden';
    }
    alert("Please turn your phone horizontally!");
  } else if (window.matchMedia("(orientation: landscape)").matches) {
    for (let element of elements) {
      element.style.visibility = 'visible';
    }
  }
};
