// Necessary variables
var oldX = 0, oldY = 0, oldSpeed = 0, newX = 0, newY = 0, newSpeed = 0;
var isRequestOnGoing = false;
var requestEnabled = true; // Enables / disables any http request to the bot.

const JOYSTICK_OFFSET = 5;
const JOYTSTICK_REQUEST_INTERVAL = 0.01; // 10ms
const JOYSTICK_MODULE_MAX = 100;

const log = document.getElementById('console');
const config = document.getElementById('config');

window.addEventListener('resize', showOrHidePage);
window.addEventListener('load', () => {
  showOrHidePage();
});
config.addEventListener('click', e => {
  if (isRequestOnGoing) {
    alert("There is an ongoing commmunication");
    return;
  }
  window.location.href = 'config';
});

/* ------------------- Joystick handling --------------------- */

const JoyLeft = new JoyStick('joystick-left', {}, (thumb) => newSpeed = thumb.y);
const JoyRight = new JoyStick('joystick-right', {}, (thumb) => {
  newX = thumb.x;
  newY = thumb.y;
});

function _sendXandYToDevice() {
  if (!requestEnabled || isRequestOnGoing) {
    return;
  }
  if (oldSpeed == 0 && newSpeed == 0) {
    return;
  }

  if ((Math.abs(oldX - newX) > JOYSTICK_OFFSET) ||
    (Math.abs(oldY - newY) > JOYSTICK_OFFSET) ||
    (Math.abs(oldSpeed - newSpeed) > JOYSTICK_OFFSET)) {

    // The Joystick might send values over +-100 sometimes. Don't know the reason.
    newSpeed = newSpeed > 0 ? Math.min(newSpeed, JOYSTICK_MODULE_MAX) : Math.max(newSpeed, -JOYSTICK_MODULE_MAX);
    newY = newY > 0 ? Math.min(newY, JOYSTICK_MODULE_MAX) : Math.max(newY, -JOYSTICK_MODULE_MAX);
    newX = newX > 0 ? Math.min(newX, JOYSTICK_MODULE_MAX) : Math.max(newX, -JOYSTICK_MODULE_MAX);

    oldSpeed = newSpeed;
    oldX = newX;
    oldY = newY;

    _request("GET", "/update?speed=" + newSpeed + "&y=" + newY + "&x=" + newX, isRequestOnGoing, log, null);
  }
}

// Attempt to send the speed and the direction every 10ms
setInterval(_sendXandYToDevice, JOYTSTICK_REQUEST_INTERVAL);
